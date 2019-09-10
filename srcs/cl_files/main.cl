#include "kernel.hl"
#include "random.cl"
#include "intersect.cl"
#include "math.cl"
#include "normals.cl"
#include "debug.cl"
#include "textures.cl"

#define SAMPLES 5



static float get_random( int * seed0, int * seed1);
float3 reflect(float3 vector, float3 n);
float3 refract(float3 vector, float3 n, float refrIndex);
float	intersect_plane(const t_obj* plane, const t_ray * ray);
#define PIX_X 500
#define PIX_Y 500


#ifdef CMD_DEBUG
#define cmdlog(x, ...) if( PIX_X == get_global_id(0) % 700 && PIX_Y == get_global_id(0) / 700 ) printf(x, __VA_ARGS__);
#else
#define cmdlog(x, ...) ;
#endif


static void intersection_reset(t_intersection * intersection)
{
	intersection->ray.t = INFINITY;	
}

float3 reflect(float3 vector, float3 n) 
{ 
    return vector - 2 * dot(vector, n) * n; 
} 

float3 refract(float3 vector, float3 n, float refrIndex)
{
	float cosI = -dot(n, vector);
	float cosT2 = 1.0f - refrIndex * refrIndex * (1.0f - cosI * cosI);
	return (refrIndex * vector) + (refrIndex * cosI - sqrt( cosT2 )) * n;
}

static t_ray createCamRay(const int x_coord, const int y_coord, const int width, const int height, t_scene *scene)
{

	float fx = (float)x_coord / (float)width;  /* convert int in range [0 - width] to float in range [0-1] */
	float fy = (float)y_coord / (float)height; /* convert int in range [0 - height] to float in range [0-1] */

	// /* calculate aspect ratio */
	// float aspect_ratio = (float)(width) / (float)(height);
	float fx2 = (fx - 0.5f);
	float fy2 = (fy - 0.5f);

	/* determine position of pixel on screen */
	float3 pixel_pos = scene->camera.direction - fy2 * (scene->camera.border_x) - fx2 * (scene->camera.border_y);

	/* create camera ray*/
	t_ray ray;
	ray.origin = scene->camera.position; /* fixed camera position */
	ray.dir = normalize(pixel_pos); /* vector from camera to pixel on screen */
	if (get_global_id(0) == 0)
	{
		printf("%f %f %f %f\n", scene->camera.direction.x, scene->camera.direction.y, scene->camera.direction.z, length(scene->camera.direction));
		printf("%f %f %f %f\n", scene->camera.position.x, scene->camera.position.y, scene->camera.position.z, length(scene->camera.position));
	}
    return ray;
}

static bool intersect_scene(t_scene * scene, t_intersection * intersection, t_ray * ray)
{
	/* initialise t to a very large number, 
	so t will be guaranteed to be smaller
	when a hit with the scene occurs */

	ray->t = INFINITY;

	/* check if the ray intersects each sphere in the scene */
	for (int i = 0; i < scene->n_objects; i++)  {
		
		t_obj object = scene->objects[i]; /* create local copy of sphere */
		float hitdistance = 0; 
		if (object.type == SPHERE)
			hitdistance = intersect_sphere(&object, ray);
		else if (object.type == CYLINDER)
			hitdistance = intersect_cylinder(&object, ray);
		else if (object.type == CONE)
			hitdistance = intersect_cone(&object, ray);
		else if (object.type == PLANE)
			hitdistance = intersect_plane(&object, ray);
		else if (object.type == TRIANGLE)
			hitdistance = intersect_triangle(&object, ray);
		/* keep track of the closest intersection and hitobject found so far */
		if (hitdistance != 0.0f && hitdistance < ray->t) {
			ray->t = hitdistance;
			intersection->object_id = i;
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
	float pdf;
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
		light_position = sphere_random_on_sphere(scene->objects + i, scene->random);
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
		if (emission_intensity < 0.00001f)
			continue ;
		pdf = 0.5;

		sphere_radius = scene->objects[intersection_light.object_id].radius;
		cos_a_max = sqrt(1.f - (sphere_radius * sphere_radius) / length(intersection_object->hitpoint - light_position));
		omega = 2 * PI * (1.f - cos_a_max);
		radiance += scene->objects[i].emission * emission_intensity * omega * _1_PI;
	}
	return (radiance);
}

static float3 trace(t_scene * scene, t_intersection * intersection, int *seed0, int * seed1)
{
	t_ray ray = intersection->ray;

	float3 accum_color = (float3)(0.0f, 0.0f, 0.0f);
	float3 mask = (float3)(1.0f, 1.0f, 1.0f);
	unsigned int max_trace_depth = 5;
	float3 explicit;
	for (int bounces = 0; bounces < max_trace_depth; bounces++)
	{
		/* if ray misses scene, return background colour */
		if (!intersect_scene(scene, intersection, &ray))
			return mask * global_texture(&ray, scene);
		/* Russian roulette*/
		if (bounces > 4 && cl_float3_max(scene->objects[intersection->object_id].color) < rng(scene->random))
			break;
		
		t_obj objecthit = scene->objects[intersection->object_id]; /* version with local copy of sphere */
		/* compute the hitpoint using the ray equation */
		intersection->hitpoint =  ray.origin + ray.dir * ray.t;
		objecthit.color = get_color(&objecthit, intersection->hitpoint, scene);
		if (length(objecthit.emission) != 0.0f && bounces == 0)
			return (objecthit.color);
		/* compute the surface normal and flip it if necessary to face the incoming ray */
		intersection->normal = get_normal(&objecthit, intersection);
		intersection->normal = dot(intersection->normal, ray.dir) < 0.0f ? intersection->normal : intersection->normal * (-1.0f);
		/* create a local orthogonal coordinate frame centered at the hitpoint */
		float cosine;
		float3 newdir = sample_uniform(&intersection->normal, &cosine, scene);
		/* add a very small offset to the hitpoint to prevent self intersection */
		cmdlog("haha\n");

		if (objecthit.reflection > 0)
		{
			accum_color += mask * objecthit.emission; 
			if (1)
			{
				explicit = radiance_explicit(scene, intersection);
				accum_color += explicit * mask  * objecthit.color;//* intersection->material.color;
			}				
			/* add the colour and light contributions to the accumulated colour */ 
			mask *= objecthit.color  * objecthit.reflection * cosine;	/* the mask colour picks up surface colours at each bounce */
		
			ray.dir = reflect(ray.dir, intersection->normal);
			ray.origin = intersection->hitpoint + ray.dir * EPSILON;
		
		} else
		{
			
			accum_color += mask * objecthit.emission; 
			if (1)
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


static t_scene scene_new(__global t_obj* objects, int n_objects, int width, int height,\
 int samples, __global ulong * random, __global t_txture *textures, t_cam camera)
{
	t_scene new_scene;

	new_scene.objects = objects;
	new_scene.n_objects = n_objects;
	new_scene.width = width;
	new_scene.height = height;
	new_scene.global_id = get_global_id(0);
	new_scene.x_coord = new_scene.global_id % new_scene.width;
	new_scene.y_coord = new_scene.global_id / new_scene.width;
	new_scene.samples = samples;
	new_scene.seed0 = new_scene.x_coord + rand_noise(new_scene.samples) * 12312;
	new_scene.seed1 = new_scene.y_coord + rand_noise(new_scene.samples + 3) * 12312;
	new_scene.random = random;
	new_scene.textures = textures;
	new_scene.camera = camera;
	return (new_scene);
}

__kernel void render_kernel(__global int* output, __global t_obj* objects,
__global float3 * vect_temp,  __global ulong * random,  __global t_txture *textures, int width, int height,  int n_objects, int samples, t_cam camera)
{
	
	t_scene scene;
	t_intersection  intersection;
	float3 finalcolor;
	unsigned int work_item_id = get_global_id(0);	/* the unique global id of the work item for the current pixel */
	unsigned int x_coord = work_item_id % width;			/* x-coordinate of the pixel */
	unsigned int y_coord = work_item_id / width;			/* y-coordinate of the pixel */
	/* seeds for random number generator */
	 unsigned int seed0 = x_coord + rng(random);
	 unsigned int seed1 = y_coord + rng(random);
	finalcolor = vect_temp[x_coord + y_coord * width];
	
	scene = scene_new(objects, n_objects, width, height, samples, random, textures, camera);
	intersection.ray = createCamRay(scene.x_coord, scene.y_coord, width, height, &scene);
	intersection_reset(&intersection.ray);
	print_debug(scene.samples, scene.width, &scene);
	for (int i = 0; i < SAMPLES; i++)
	{	
		finalcolor += trace(&scene,  &intersection, &seed0, &seed1);
	}
	vect_temp[scene.x_coord + scene.y_coord * width] = finalcolor;
	
	output[scene.x_coord + scene.y_coord * width] = ft_rgb_to_hex(toInt(finalcolor.x  / samples),
	 toInt(finalcolor.y  / samples), toInt(finalcolor.z  / samples)); /* simple interpolated colour gradient based on pixel coordinates */
}
