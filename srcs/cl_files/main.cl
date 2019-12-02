#include "kernel.hl"
#include "random.cl"
#include "intersect.cl"
#include "math.cl"
#include "normals.cl"
#include "debug.cl"
#include "textures.cl"
#include "normale_zuordnung.cl"
#include "interpolate_uv.cl"

#define SAMPLES 5
#define BOUNCES 6
#define LIGHTSAMPLING 0


static void intersection_reset(t_intersection * intersection)
{
	intersection->ray.t = INFINITY;
}

float3 reflect(float3 vector, float3 n)
{
    return vector - 2 * dot(vector, n) * n;
}

static void createCamRay(t_scene *scene, t_ray *ray)
{

	float fx = (float)scene->x_coord / (float)scene->width;
	float fy = (float)scene->y_coord / (float)scene->height;

	fx = (fx  - 0.5f) + rng(scene->random) / (float)scene->width;
	fy = (fy  - 0.5f) + rng(scene->random) / (float)scene->height;
	float3 pixel_pos = scene->camera.direction - fy * (scene->camera.border_x) - fx * (scene->camera.border_y);
	ray->origin = scene->camera.position;
	ray->dir = normalize(pixel_pos);
}

static bool intersect_scene(t_scene *scene, t_intersection *intersection, t_ray *ray)
{
	ray->t = INFINITY;
	/* check if the ray intersects each object in the scene */
	for (int i = 0; i < scene->n_objects; i++)
	{
		__global t_obj *object = &(scene->objects[i]); /* create local copy of object */
		float hitdistance = 0;
		if (object->is_visible)
		{
			if (object->type == SPHERE)
				hitdistance = intersect_sphere(object, ray);
			else if (object->type == CYLINDER)
				hitdistance = intersect_cylinder(object, ray);
			else if (object->type == CONE)
				hitdistance = intersect_cone(object, ray);
			else if (object->type == PLANE)
				hitdistance = intersect_plane(object, ray);
			else if (object->type == TRIANGLE)
				hitdistance = intersect_triangle(object, ray);
			else if (object->type == HYPERBOLOID)
				hitdistance = intersect_hyper(object, ray);
			/* keep track of the closest intersection and hitobject found so far */
			if (hitdistance != 0.0f && hitdistance < ray->t)
			{
				ray->t = hitdistance;
				intersection->object_id = i;
			}
		}
	}
	return ray->t < INFINITY; /* true when ray interesects the scene */
}


static float3		radiance_explicit(t_scene *scene,
					t_intersection *intersection_object
					)
{
	t_intersection	intersection_light;
	float3			radiance;
	float3			light_position;
	float3			light_direction;
	float			emission_intensity;
	float			cos_a_max;
	float			omega;
	float			sphere_radius;
	float 			pdf;
	radiance = 0;
	t_ray lightray;
	for (int i = 0; i < scene->n_objects; i++)
	{
		if (i == intersection_object->object_id)
			continue ;
		if (scene->objects[i].type != SPHERE)
			continue ;
		if (cl_float3_max(scene->objects[i].emission) == 0.f)
			continue ;
		light_position = sphere_random(scene->objects + i, scene->random);
		light_direction = normalize(light_position - intersection_object->hitpoint);
		lightray.origin = intersection_object->hitpoint; //- light_direction * EPSILON;
		lightray.dir = light_direction;
		intersection_reset(&intersection_light);

		if (!intersect_scene(scene, &intersection_light, &lightray))
			continue ;
		if (intersection_light.object_id != i)
			continue ;
		intersection_light.material.color = scene->objects[i].emission;
		emission_intensity = dot(intersection_object->normal, lightray.dir);
		if (emission_intensity < EPSILON)
			continue ;
		pdf = 0.3f;

		sphere_radius = scene->objects[intersection_light.object_id].radius;
		cos_a_max = sqrt(1.f - (sphere_radius * sphere_radius) / length(intersection_object->hitpoint - light_position));
		omega = 2 * PI * (1.f - cos_a_max);
		radiance += scene->objects[i].emission * emission_intensity * omega * _1_PI;
	}
	return (radiance * pdf);
}

static float3 convert_normal(t_obj *object, float3 normal, float3 dir, t_scene *scene)
{
	if (object->transparency > rng(scene->random))
	{
		object->metalness = 1.f;
		normal = dir;
	}
	else
		normal = object->metalness > 0.0 ? normalize(reflect(dir, normal)) : normal;
	return (normal);
}

static float3 trace(t_scene * scene, t_intersection * intersection)
{
	t_ray ray = intersection->ray;
	float2		img_coord;

	float3 accum_color = 0.0f;
	float3 mask = 1.0f;
	int bncs = scene->lightsampling ? 1 : BOUNCES;
	float3 explicit;
	for (int bounces = 0; bounces < bncs; bounces++)
	{
		/* if ray misses scene, return background colour */
		if (!intersect_scene(scene, intersection, &ray))
			return accum_color + mask * global_texture(&ray, scene);

		/* Russian roulette*/
		// if (bounces > 4 && cl_float3_max(scene->objects[intersection->object_id].color) < rng(scene->random))
		// 	break;

		t_obj objecthit = scene->objects[intersection->object_id];

		/* compute the hitpoint using the ray equation */
		intersection->hitpoint =  ray.origin + ray.dir * ray.t;

		if (objecthit.normal || objecthit.texture)
			interpolate_uv(&objecthit, intersection->hitpoint, scene, &img_coord);
		objecthit.color = get_color(&objecthit, intersection->hitpoint, scene, &img_coord);
		if (length(objecthit.emission) != 0.0f && bounces == 0)
			return (objecthit.color);
		/* compute the surface normal and flip it if necessary to face the incoming ray */
		intersection->normal = get_normal(&objecthit, intersection, &img_coord, scene);
		intersection->normal *= -sign(dot(intersection->normal, ray.dir));
		float cosine;
		float3 normal = convert_normal(&objecthit, intersection->normal, ray.dir, scene);//;objecthit.metalness > 0.0 ? normalize(reflect(ray.dir, intersection->normal)) : intersection->normal;
		float3 newdir = sample_uniform(&normal, scene, objecthit.metalness);
		cosine = fabs(dot(normal, newdir));
		/* add a very small offset to the hitpoint to prevent self intersection */
		float pdf = 1.f - scene->lightsampling * 0.7f;
		accum_color += mask * objecthit.emission * pdf /** cosine*/ + mask * (scene->camera.ambience);
		if (scene->lightsampling)
		{
			explicit = radiance_explicit(scene, intersection);
			accum_color += explicit * mask * objecthit.color;
		}
		mask *= objecthit.color ;//* cosine;
		ray.dir = newdir;
		ray.origin = intersection->hitpoint + ray.dir * EPSILON;
	}
	return accum_color;
}


static void scene_new(__global t_obj* objects, int n_objects,\
 int samples, __global ulong * random, __global t_txture *textures, t_cam camera, t_scene *scene, __global t_txture *normals, int lightsampling, int global_texture_id)
{
	scene->objects = objects;
	scene->n_objects = n_objects;
	scene->width = get_global_size(0);
	scene->height = get_global_size(1);
	scene->x_coord = get_global_id(0);
	scene->y_coord = get_global_id(1);
	scene->samples = samples;
	scene->random = random;
	scene->textures = textures;
	scene->normals = normals;
	scene->camera = camera;
	scene->lightsampling = !lightsampling;
	scene->global_texture_id = global_texture_id;
}

static int filter_mode(float3 finalcolor, t_cam camera, int samples)
{
	int red;
	int green;
	int blue;
	int color;

	color = ft_rgb_to_hex(toInt(finalcolor.x  / (float)samples), toInt(finalcolor.y  / (float)samples), toInt(finalcolor.z  / (float)samples));
	if (camera.sepia == 1)
	{
		finalcolor.x = (finalcolor.x + finalcolor.y + finalcolor.z) / 3;
		finalcolor.z = (finalcolor.x + finalcolor.y + finalcolor.z) / 3;
		finalcolor.y = (finalcolor.x + finalcolor.y + finalcolor.z) / 3;
		color = ft_rgb_to_hex(toInt(finalcolor.x  / (float)samples), toInt(finalcolor.y  / (float)samples), toInt(finalcolor.z  / (float)samples));
		red = (int)(((color >> 16) & 0xFF) + ((SEPIA >> 16) & 0xFF));
		green = (int)(((color >> 8) & 0xFF) + ((SEPIA >> 8) & 0xFF));
		blue = (int)(((color) & 0xFF) + ((SEPIA) & 0xFF));
		color =  ft_rgb_to_hex(c_floor(red), c_floor(green), c_floor(blue));
	}
	return (color);
}

static int stereo_mode(int color0, int color1)
{
	int red;
	int green;
	int blue;

	red = (int)(((color0 >> 16) & 0xFF) + ((color1 >> 16) & 0xFF));
	green = (int)(((color0 >> 8) & 0xFF) + ((color1 >> 8) & 0xFF));
	blue = (int)(((color0) & 0xFF) + ((color1) & 0xFF));
	return (ft_rgb_to_hex(c_floor(red), c_floor(green), c_floor(blue)));
}

__kernel void render_kernel(__global int *output, __global t_obj *objects,
__global float3 *vect_temp,  __global ulong * random,  __global t_txture *textures,\
 __global t_txture *normals, int n_objects, int samples, t_cam camera, int lightsampling, int global_texture_id, __global float3 *vect_temp1)
{

	t_scene scene;
	t_intersection  intersection;
	float3 finalcolor;
	int hex_finalcolor;
	float3 finalcolor1;
	int	hex_finalcolor1;
	scene_new(objects, n_objects, samples, random, textures, camera, &scene, normals, lightsampling, global_texture_id);
	finalcolor = vect_temp[scene.x_coord + scene.y_coord * scene.width];
	//output[scene.x_coord + scene.y_coord * width] = 0xFF0000;      /* uncomment to test if opencl runs */
	for (int i = 0; i < SAMPLES; i++)
	{
		createCamRay(&scene, &(intersection.ray));
		intersection_reset(&intersection);
		finalcolor += trace(&scene,  &intersection);
	}

	// hex_finalcolor = ft_rgb_to_hex(toInt(finalcolor.x  / (float)samples), toInt(finalcolor.y  / (float)samples), toInt(finalcolor.z  / (float)samples));

	vect_temp[scene.x_coord + scene.y_coord * scene.width] = finalcolor;

	if (camera.stereo == 1)
	{
		finalcolor = (float3)((finalcolor.x + finalcolor.y + finalcolor.z) / 3, 0.f, 0.f);
		float3 cross_dir = normalize(cross(camera.normal, camera.direction));
		hex_finalcolor = ft_rgb_to_hex(toInt(finalcolor.x  / (float)samples), toInt(finalcolor.y  / (float)samples), toInt(finalcolor.z  / (float)samples));
		scene.camera.position += cross_dir * (float3)0.05;
		finalcolor1 = vect_temp1[scene.x_coord + scene.y_coord * scene.width];
		for (int i = 0; i < SAMPLES; i++)
		{
			createCamRay(&scene, &(intersection.ray));
			intersection_reset(&intersection);
			finalcolor1 += trace(&scene,  &intersection);
		}
		vect_temp1[scene.x_coord + scene.y_coord * scene.width] = finalcolor1;
		scene.camera.position -= cross_dir * (float3)0.05;
		finalcolor1 = (float3)(0.f, 0.f, (finalcolor1.x + finalcolor1.y + finalcolor1.z) / 3);
		hex_finalcolor1 = ft_rgb_to_hex(toInt(finalcolor1.x  / (float)samples), toInt(finalcolor1.y  / (float)samples), toInt(finalcolor1.z  / (float)samples));
		output[scene.x_coord + scene.y_coord * scene.width] = stereo_mode(hex_finalcolor, hex_finalcolor1);
	}
	else
		output[scene.x_coord + scene.y_coord * scene.width] = filter_mode(finalcolor, camera, samples);
	 /* simple interpolated colour gradient based on pixel coordinates */
}
