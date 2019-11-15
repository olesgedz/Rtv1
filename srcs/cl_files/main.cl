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
#define BOUNCES 4
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
	/* check if the ray intersects each sphere in the scene */
	for (int i = 0; i < scene->n_objects; i++)
	{
		__global t_obj *object = &(scene->objects[i]); /* create local copy of sphere */
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

static float3 trace(t_scene * scene, t_intersection * intersection)
{
	t_ray ray = intersection->ray;
	float2		img_coord;

	float3 accum_color = 0.0f;
	float3 mask = 1.0f;
	float3 explicit;
	for (int bounces = 0; bounces < (scene->lightsampling ? 1 : BOUNCES); bounces++)
	{
		/* if ray misses scene, return background colour */
		if (!intersect_scene(scene, intersection, &ray))
			return accum_color + mask * global_texture(&ray, scene);
		/* Russian roulette*/
		// if (bounces > 4 && cl_float3_max(scene->objects[intersection->object_id].color) < rng(scene->random))
		// 	break;

		t_obj objecthit = scene->objects[intersection->object_id]; /* version with local copy of sphere */
		/* compute the hitpoint using the ray equation */
		intersection->hitpoint =  ray.origin + ray.dir * ray.t;
		if (objecthit.normal || objecthit.texture)
			interpolate_uv(&objecthit, intersection->hitpoint, scene, &img_coord);
		objecthit.color = get_color(&objecthit, intersection->hitpoint, scene, &img_coord);
		if (length(objecthit.emission) != 0.0f && bounces == 0)
			return (objecthit.color);
		/* compute the surface normal and flip it if necessary to face the incoming ray */
		intersection->normal = get_normal(&objecthit, intersection, &img_coord, scene);
		intersection->normal = dot(intersection->normal, ray.dir) < 0.0f ? intersection->normal : intersection->normal * (-1.0f);
		/* create a local orthogonal coordinate frame centered at the hitpoint */
		float cosine;
		float3 newdir = sample_uniform(&intersection->normal, &cosine, scene);
		/* add a very small offset to the hitpoint to prevent self intersection */
		float pdf = 1.f;
		if (scene->lightsampling)
			pdf = 0.3f;
		if (objecthit.reflection > 0)
		{
			accum_color += mask * objecthit.emission * pdf;
			if (scene->lightsampling)
			{
				explicit = radiance_explicit(scene, intersection);
				accum_color += explicit * mask  * objecthit.color;//* intersection->material.color;
			}
			/* add the colour and light contributions to the accumulated colour */
			mask *= objecthit.color  * objecthit.reflection;	/* the mask colour picks up surface colours at each bounce */
			ray.dir = reflect(ray.dir, intersection->normal);
			ray.origin = intersection->hitpoint + ray.dir * EPSILON;
		}
		else
		{
			accum_color += mask * objecthit.emission * pdf;
			if (scene->lightsampling)
			{
				explicit = radiance_explicit(scene, intersection);
				accum_color += explicit * mask *  objecthit.color;//intersection->material.color;
			}
			mask *= objecthit.color * cosine;

			ray.dir = newdir;
			ray.origin = intersection->hitpoint + ray.dir * EPSILON;
		}
	}
	return accum_color;
}


static void scene_new(__global t_obj* objects, int n_objects,\
 int samples, __global ulong * random, __global t_txture *textures, t_cam camera, t_scene *scene, __global t_txture *normals, int lightsampling)
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
}

__kernel void render_kernel(__global int *output, __global t_obj *objects,
__global float3 *vect_temp,  __global ulong * random,  __global t_txture *textures,\
 __global t_txture *normals, int n_objects, int samples, t_cam camera, int lightsampling)
{

	t_scene scene;
	t_intersection  intersection;
	float3 finalcolor;
	scene_new(objects, n_objects, samples, random, textures, camera, &scene, normals, lightsampling);
	finalcolor = vect_temp[scene.x_coord + scene.y_coord * scene.width];
	//output[scene.x_coord + scene.y_coord * width] = 0xFF0000;      /* uncomment to test if opencl runs */
	for (int i = 0; i < SAMPLES; i++)
	{
		createCamRay(&scene, &(intersection.ray));
		intersection_reset(&intersection);
		finalcolor += trace(&scene,  &intersection);
	}
	vect_temp[scene.x_coord + scene.y_coord * scene.width] = finalcolor;
	output[scene.x_coord + scene.y_coord * scene.width] = ft_rgb_to_hex(toInt(finalcolor.x  / (float)samples),
	 toInt(finalcolor.y  / (float)samples), toInt(finalcolor.z  / (float)samples)); /* simple interpolated colour gradient based on pixel coordinates */
}
