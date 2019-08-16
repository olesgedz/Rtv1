 #include "kernel.h"
 #include "random.cl"
 #include "intersect.cl"

static float get_random( int * seed0, int * seed1);
float3 reflect(float3 vector, float3 n);
float3 refract(float3 vector, float3 n, float refrIndex);
double          intersect_plane(const t_obj* plane, const t_ray * ray);
typedef struct s_scene{

	__global t_obj * objects;
	int n_objects;
	unsigned int global_id;
	unsigned int x_coord;
	unsigned int y_coord;
	int width;
	int height;
	int samples;
	unsigned int seed0;
	unsigned int seed1;
} t_scene;
// t_ray get_camera_ray(int x, int y, t_cam *cam, int *seed0, int *seed1)
// {
// 	t_ray ray;

// 	float a = get_random(seed0, seed1) * 2 * PI; //random angle
// 	float r = sqrt(get_random(seed0, seed1) * cam->aperture); //random radius
// 	float ax = r * cos(a); //random x
// 	float ay = r * sin(a); // random y

// 	ray.origin = (float3)(ax,ay,0);

// 	ray.dir = (float3)(x - cam->pr_pl_w / 2, -y + cam->pr_pl_h / 2,
// 		-cam->f_length);
// 	ray.dir.x = (ray.dir.x + get_random(seed0, seed1) - 0.5f) * cam->ratio;
// 	ray.dir.y = (ray.dir.y + get_random(seed0, seed1) - 0.5f) * cam->ratio;
// 	ray.dir -= ray.origin;
// 	ray.dir = normalize(ray.dir);
// 	return(ray);
//}

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

static t_ray createCamRay(const int x_coord, const int y_coord, const int width, const int height){

	float fx = (float)x_coord / (float)width;  /* convert int in range [0 - width] to float in range [0-1] */
	float fy = (float)y_coord / (float)height; /* convert int in range [0 - height] to float in range [0-1] */

	/* calculate aspect ratio */
	float aspect_ratio = (float)(width) / (float)(height);
	float fx2 = (fx - 0.5f) * aspect_ratio;
	float fy2 = fy - 0.5f;

	/* determine position of pixel on screen */
	float3 pixel_pos = (float3)(fx2, -fy2, 0.0f);

	/* create camera ray*/
	t_ray ray;
	ray.origin = (float3)(0.0f, 0.1f, 2.f); /* fixed camera position */
	ray.dir = normalize(pixel_pos - ray.origin); /* vector from camera to pixel on screen */
    return ray;
}
 




// static bool intersect_scene(__constant t_obj* objects, t_scene * scene, t_intersection * intersection)
// {
// 	/* initialise t to a very large number, 
// 	so t will be guaranteed to be smaller
// 	when a hit with the scene occurs */
// 	intersection->ray.t = INFINITY;

// 	/* check if the t_ray intersects each sphere in the scene */
// 	for (int i = 0; i < scene->n_objects; i++)  {
		
// 		t_obj object = objects[i]; /* create local copy of sphere */
		
// 		/* float hitdistance = intersect_sphere(&spheres[i], ray); */
// 		float hitdistance = 0; 
// 		if (object.type == SPHERE)
// 			hitdistance = intersect_sphere(&object, &intersection->ray);
// 		else if (object.type == CYLINDER)
// 			hitdistance = intersect_cylinder(&object, &intersection->ray);
// 		else if (object.type == CONE)
// 			hitdistance = intersect_cone(&object, &intersection->ray);
// 		else if (object.type == PLANE)
// 			hitdistance = intersect_plane(&object, &intersection->ray);
// 		/* keep track of the closest intersection and hitobject found so far */
// 		if (hitdistance != 0.0f && hitdistance < intersection->ray.t) {
// 			intersection->ray.t = hitdistance;
// 			intersection->object_id = i;
// 		}
// 	}
// 	return intersection->ray.t < INFINITY; /* true when t_ray interesects the scene */
// }

static bool intersect_scene(__global t_obj* spheres, const t_ray * ray, float* t, int* sphere_id, const int sphere_count)
{
	/* initialise t to a very large number, 
	so t will be guaranteed to be smaller
	when a hit with the scene occurs */

	float inf = 1e20f;
	*t = inf;

	/* check if the ray intersects each sphere in the scene */
	for (int i = 0; i < sphere_count; i++)  {
		
		t_obj sphere = spheres[i]; /* create local copy of sphere */
		
		/* float hitdistance = intersect_sphere(&spheres[i], ray); */
		float hitdistance = 0; 
		if (sphere.type == SPHERE)
			hitdistance = intersect_sphere(&sphere, ray);
		else if (sphere.type == CYLINDER)
			hitdistance = intersect_cylinder(&sphere, ray);
		else if (sphere.type == CONE)
			hitdistance = intersect_cone(&sphere, ray);
		else if (sphere.type == PLANE)
			hitdistance = intersect_plane(&sphere, ray);
		/* keep track of the closest intersection and hitobject found so far */
		if (hitdistance != 0.0f && hitdistance < *t) {
			*t = hitdistance;
			*sphere_id = i;
		}
	}
	return *t < inf; /* true when ray interesects the scene */
}

float cl_float3_max(float3 v)
{
	return (fmax(fmax(v.x, v.y), v.z));
} 
float cl_float3_min(float3 v)
{
	return (fmin(fmin(v.x, v.y), v.z));
} 

// static float3 trace(__constant t_obj* objects,t_scene * scene, t_intersection * intersection)
// {
// 	float3 accum_color = (float3)(0.0f, 0.0f, 0.0f);
// 	float3 mask = (float3)(1.0f, 1.0f, 1.0f);
// 	unsigned int max_trace_depth = 16;

// 	for (int bounces = 0; bounces < max_trace_depth; bounces++)
// 	{
// 		intersection->object_id = 0;

// 		/* if t_ray misses scene, return background colour */
// 		if (!intersect_scene(objects, scene, intersection))
// 			return mask * (float3)(0.7f, 0.7f, 0.7f);

// 		/* else, we've got a hit! Fetch the closest hit sphere */
// 		t_obj obj_hit = objects[intersection->object_id]; /* version with local copy of sphere */

// 		/* compute the hitpoint using the t_ray equation */
// 		float3 hitpoint = intersection->ray.origin + intersection->ray.dir * intersection->ray.t;
		
// 		/* compute the surface normal and flip it if necessary to face the incoming t_ray */
// 		intersection->normal = normalize(intersection->hitpoint - obj_hit.position);  //get normal
// 		float3 normal_facing = dot(intersection->normal, intersection->ray.dir) < 0.0f ? intersection->normal : intersection->normal * (-1.0f);

// 		/* compute two random numbers to pick a random point on the hemisphere above the hitpoint*/
// 		float rand1 = 2.0f * PI * get_random(scene->seed0, scene->seed1);
// 		float rand2 = get_random(scene->seed0, scene->seed1);
// 		float rand2s = sqrt(rand2);

// 		/* create a local orthogonal coordinate frame centered at the hitpoint */
// 		float3 w = normal_facing;
// 		float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) : (float3)(1.0f, 0.0f, 0.0f);
// 		float3 u = normalize(cross(axis, w));
// 		float3 v = cross(w, u);
// 		float3 newdir;
// 		/* use the coordinte frame and random numbers to compute the next t_ray direction */
// 		newdir = normalize(u * cos(rand1)*rand2s + v*sin(rand1)*rand2s + w*sqrt(1.0f - rand2));
		
// 		newdir = sample_hemisphere(w, 1, scene->seed0, scene->seed1);
// 		//  else
// 		// 	newdir = normalize((float3)(0.7f, 0.7f, 0.0f) - hitpoint);
// 		/* add a very small offset to the hitpoint to prevent self intersection */
// 		if (obj_hit.reflection > 0) {
// 			intersection->ray.dir = reflect(intersection->ray.dir, normal_facing);
// 			intersection->ray.origin = hitpoint + intersection->ray.dir * EPSILON;

// 			accum_color += mask * obj_hit.emission; 	/* add the colour and light contributions to the accumulated colour */ 
// 			mask *= obj_hit.color * obj_hit.reflection;	/* the mask colour picks up surface colours at each bounce */
// 		} else {
// 			intersection->ray.dir = newdir;
// 			intersection->ray.origin = hitpoint + intersection->ray.dir * EPSILON;
// 			accum_color += mask * obj_hit.emission; 
// 			mask *= obj_hit.color;
// 		}
// 		mask *= dot(newdir, normal_facing);
// 	}
// 	//color = INTEGRAL A * s(direction) * color(direction)
// 	//Color = (A * s(direction) * color(direction)) / p(direction)
// 	return accum_color;
// }

static float3 trace(__global t_obj* spheres, const t_ray * camray, const int sphere_count, const int* seed0, const int* seed1)
{
	t_ray ray = *camray;

	float3 accum_color = (float3)(0.0f, 0.0f, 0.0f);
	float3 mask = (float3)(1.0f, 1.0f, 1.0f);
	unsigned int max_trace_depth = 16;

	for (int bounces = 0; bounces < max_trace_depth; bounces++)
	{
		float t;   /* distance to intersection */
		int hitsphere_id = 0; /* index of intersected sphere */

		/* if ray misses scene, return background colour */
		if (!intersect_scene(spheres, &ray, &t, &hitsphere_id, sphere_count))
			return mask * (float3)(0.7f, 0.7f, 0.7f);

		/* else, we've got a hit! Fetch the closest hit sphere */
		t_obj hitsphere = spheres[hitsphere_id]; /* version with local copy of sphere */

		/* compute the hitpoint using the ray equation */
		float3 hitpoint = ray.origin + ray.dir * t;
		
		/* compute the surface normal and flip it if necessary to face the incoming ray */
		float3 normal = normalize(hitpoint - hitsphere.position); 
		float3 normal_facing = dot(normal, ray.dir) < 0.0f ? normal : normal * (-1.0f);

		/* compute two random numbers to pick a random point on the hemisphere above the hitpoint*/
		float rand1 = 2.0f * PI * get_random(seed0, seed1);
		float rand2 = get_random(seed0, seed1);
		float rand2s = sqrt(rand2);

		/* create a local orthogonal coordinate frame centered at the hitpoint */
		float3 w = normal_facing;
		float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) : (float3)(1.0f, 0.0f, 0.0f);
		float3 u = normalize(cross(axis, w));
		float3 v = cross(w, u);
		float3 newdir;
		/* use the coordinte frame and random numbers to compute the next ray direction */
		newdir = normalize(u * cos(rand1)*rand2s + v*sin(rand1)*rand2s + w*sqrt(1.0f - rand2));
		
		newdir = sample_hemisphere(w, 1, seed0, seed1);
		//  else
		// 	newdir = normalize((float3)(0.7f, 0.7f, 0.0f) - hitpoint);
		/* add a very small offset to the hitpoint to prevent self intersection */
		if (hitsphere.reflection > 0) {
			ray.dir = reflect(ray.dir, normal_facing);
			ray.origin = hitpoint + ray.dir * EPSILON;

			accum_color += mask * hitsphere.emission; 	/* add the colour and light contributions to the accumulated colour */ 
			mask *= hitsphere.color * hitsphere.reflection;	/* the mask colour picks up surface colours at each bounce */
		} else {
			ray.dir = newdir;
			ray.origin = hitpoint + ray.dir * EPSILON;
			accum_color += mask * hitsphere.emission; 
			mask *= hitsphere.color;
		}
		mask *= dot(newdir, normal_facing);
	}
	//color = INTEGRAL A * s(direction) * color(direction)
	//Color = (A * s(direction) * color(direction)) / p(direction)
	return accum_color;
}

static int	ft_rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static float clamp1(float x)
{
	return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
}

static int toInt(float x)
{ 
	return int(clamp1(x) * 255);
}

static void intersection_reset(t_intersection * intersection)
{
	intersection->ray.t = INFINITY;	
}

void check_random(int work_item_id, int seed0, seed1)
{
	if(work_item_id == 0)
	{
		int inside_circle = 0;
		int N = 1000000;
		for (int i = 0; i < N; i++)
		{
			float x = 2 * noise_3d(seed0, seed1, i) - 1;
			float y = 2 * noise_3d(seed0, seed1, i + 100) -1;
			if (x* x + y * y < 1)
				inside_circle++;
		}
		printf("\n\n Pi = %f\n\n", 4*float(inside_circle)/N);	
	}
	for (int i = 0; i < 20; i++)
		printf("i :%d %d\n", work_item_id, get_random);
}

void print_debug(int samples, int width)
{
	unsigned int work_item_id = get_global_id(0);	
	unsigned int x = work_item_id % width;
	unsigned int y = work_item_id / width;
		if (x == 0 && y == 0)
	{
		printf("samples %d\n", samples);
	}
}

static t_scene scene_new(__global t_obj* objects, int n_objects, int width, int height, int samples)
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
	return (new_scene);
}

__kernel void render_kernel(__global int* output, int width, int height, int n_objects, __global t_obj* objects,
__global float3 * vect_temp, int samples
	)
{
	
	t_scene scene;
	t_intersection  intersection;
	float3 finalcolor;
	unsigned int work_item_id = get_global_id(0);	/* the unique global id of the work item for the current pixel */
	unsigned int x_coord = work_item_id % width;			/* x-coordinate of the pixel */
	unsigned int y_coord = work_item_id / width;			/* y-coordinate of the pixel */

	/* seeds for random number generator */
	 unsigned int seed0 = x_coord + rand_noise(samples) * 12312 ;
	 unsigned int seed1 = y_coord + rand_noise(samples + 3) * 12312;
	finalcolor = vect_temp[scene.x_coord + scene.y_coord * width];
	scene = scene_new(objects, n_objects, width, height, samples);
	intersection.ray = createCamRay(scene.x_coord, scene.y_coord, width, height);
	
	print_debug(scene.samples, scene.width);

	for (int i = 0; i < 15; i++)
	{	//__constant t_obj* spheres, const Ray* camray, const int sphere_count, const int* seed0, const int* seed1
		finalcolor += trace(scene.objects,  &intersection.ray, n_objects, &seed0, &seed1);
	}
	vect_temp[scene.x_coord + scene.y_coord * width] = finalcolor;
	
	output[scene.x_coord + scene.y_coord * width] = ft_rgb_to_hex(toInt(finalcolor.x  / samples),
	 toInt(finalcolor.y  / samples), toInt(finalcolor.z  / samples)); /* simple interpolated colour gradient based on pixel coordinates */

}
