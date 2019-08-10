 #include "kernel.h"
 #include "random.cl"
 #include "intersect.cl"

// // typedef struct s_camera
// // {
// // 	cl_float3 position;
// // 	cl_float3		axis_x;
// // 	cl_float3		axis_y;
// // 	cl_float3		axis_z;
// // 	cl_float3		forward;
// // 	int				width;
// // 	int				height;
// // } t_camera;

Ray get_camera_ray(int x, int y, t_cam *cam, int *seed0, int *seed1);
Ray get_precise_ray(int x, int y, t_cam *cam);
static float get_random( int *seed0, int *seed1);
float3 reflect(float3 vector, float3 n);
float3 refract(float3 vector, float3 n, float refrIndex);
double          intersect_plane(const t_obj* plane, const Ray* ray);

// Ray get_precise_ray(int x, int y, t_cam *cam)
// {
// 	Ray ray;

// 	ray.origin = (float3)(0,0,0);

// 	ray.dir = (float3)(x - cam->pr_pl_w / 2, -y + cam->pr_pl_h / 2,
// 		-cam->f_length);
// 	ray.dir.x *= cam->ratio;
// 	ray.dir.y *= cam->ratio;
// 	ray.dir = normalize(ray.dir);
// 	return(ray);
// }



Ray get_camera_ray(int x, int y, t_cam *cam, int *seed0, int *seed1)
{
	Ray ray;

	float a = get_random(seed0, seed1) * 2 * PI; //random angle
	float r = sqrt(get_random(seed0, seed1) * cam->aperture); //random radius
	float ax = r * cos(a); //random x
	float ay = r * sin(a); // random y

	ray.origin = (float3)(ax,ay,0);

	ray.dir = (float3)(x - cam->pr_pl_w / 2, -y + cam->pr_pl_h / 2,
		-cam->f_length);
	ray.dir.x = (ray.dir.x + get_random(seed0, seed1) - 0.5f) * cam->ratio;
	ray.dir.y = (ray.dir.y + get_random(seed0, seed1) - 0.5f) * cam->ratio;
	ray.dir -= ray.origin;
	ray.dir = normalize(ray.dir);
	return(ray);
}



// // float3	sample_hemisphere(float3 w, float max_r, uint2 *seeds)
// // {
// // 	float rand1 = 2.0f * PI * get_random(seeds);
// // 	float rand2 = get_random(seeds) * max_r;
// // 	float rand2s = sqrt(rand2);

// // 	float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) :
// // 		(float3)(1.0f, 0.0f, 0.0f);
// // 	float3 u = normalize(cross(axis, w));
// // 	float3 v = cross(w, u);

// // 	float3 newdir = normalize(u * cos(rand1)*rand2s +
// // 		v*sin(rand1)*rand2s +w*sqrt(1.0f - rand2));

// // 	return (newdir);
// // }

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

static Ray createCamRay(const int x_coord, const int y_coord, const int width, const int height){

	float fx = (float)x_coord / (float)width;  /* convert int in range [0 - width] to float in range [0-1] */
	float fy = (float)y_coord / (float)height; /* convert int in range [0 - height] to float in range [0-1] */

	/* calculate aspect ratio */
	float aspect_ratio = (float)(width) / (float)(height);
	float fx2 = (fx - 0.5f) * aspect_ratio;
	float fy2 = fy - 0.5f;

	/* determine position of pixel on screen */
	float3 pixel_pos = (float3)(fx2, -fy2, 0.0f);

	/* create camera ray*/
	Ray ray;
	ray.origin = (float3)(0.0f, 0.1f, 2.f); /* fixed camera position */
	ray.dir = normalize(pixel_pos - ray.origin); /* vector from camera to pixel on screen */
    return ray;
}
 




static bool intersect_scene(__constant t_obj* spheres, const Ray* ray, float* t, int* sphere_id, const int sphere_count)
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


// // float3 sample_lightRND(__constant t_obj* spheres, const Ray* camray, const int sphere_count, const int* seed0, const int* seed1)
// // {
// // 	float3 emission  = (float3)(0.f,0.f,0.f);
// // 	float3 mask = (float3)(1.0f, 1.0f, 1.0f);
// // 	unsigned int max_trace_depth = 16;
// // }

// // float cl_float3_max(float3 v)
// // {
// // 	return (fmax(fmax(v.x, v.y), v.z);
// // } 
static float3 trace(__constant t_obj* spheres, const Ray* camray, const int sphere_count, const int* seed0, const int* seed1)
{
	Ray ray = *camray;

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

// // float3 sample_light(__constant t_obj* spheres, const int sphere_count )
// // {
// // 		float3 lightSampling;
// // 		for (int i = 0; i < sphere_count; i++)  {

// // 			if (length(spheres[i].emission) > 0) {
// // 				continue;
// // 			}
// // 			float3 lightPos = spheres[i].position;
// // 			float3 lightDirection = normalize(lightPos - hitpoint);
// // 			Ray rayToLight;
// // 			 rayToLight.origin =  hitpoint;
// // 			 rayToLight.dir = lightDirection;
// // 			float t_light;
// // 			int hit_id_light = 0; 
// // 			if (!intersect_scene(spheres, &rayToLight, &t_light, &hit_id_light, sphere_count))
// // 				continue;
// // 			if(length(spheres[hit_id_light].emission) > 0)
// // 			{
// // 				float wi = dot(lightDirection, normal_facing);
// // 				if (wi > 0)
// // 				{
// // 					float srad = 1.5;
// // 					float cos_a_max = sqrt(1-srad*srad/dot(hitpoint - lightPos,hitpoint - lightPos));
// // 					float omega = 2* PI *(1-cos_a_max);
// // 					lightSampling += spheres[hit_id_light].emission * wi * omega * M_1_PI;
// // 				}
// // 			}

// // 		}
// // }


/* the path tracing function */
/* computes a path (starting from the camera) with a defined number of bounces, accumulates light/color at each bounce */
/* each ray hitting a surface will be reflected in a random direction (by randomly sampling the hemisphere above the hitpoint) */
/* small optimisation: diffuse ray directions are calculated using cosine weighted importance sampling */

// // static float3 trace1(__constant t_obj* spheres, const Ray* camray, const int sphere_count, const int* seed0, const int* seed1)
// // {
// // 	Ray ray = *camray;

// // 	float3 accum_color = (float3)(0.0f, 0.0f, 0.0f);
// // 	float3 mask = (float3)(1.0f, 1.0f, 1.0f);
// // 	unsigned int max_trace_depth = 5;

// // 	for (int bounces = 0; bounces < max_trace_depth; bounces++)
// // 	{
// // 		float t;   /* distance to intersection */
// // 		int hitsphere_id = 0; /* index of intersected sphere */

// // 		/* if ray misses scene, return background colour */
// // 		if (!intersect_scene(spheres, &ray, &t, &hitsphere_id, sphere_count))
// // 			return mask * (float3)(0.7f, 0.7f, 0.7f);

// // 		/* else, we've got a hit! Fetch the closest hit sphere */
// // 		t_obj hitsphere = spheres[hitsphere_id]; /* version with local copy of sphere */

// // 		/* compute the hitpoint using the ray equation */
// // 		float3 hitpoint = ray.origin + ray.dir * t;
		
// // 		/* compute the surface normal and flip it if necessary to face the incoming ray */
// // 		float3 normal = normalize(hitpoint - hitsphere.position); 
// // 		float3 normal_facing = dot(normal, ray.dir) < 0.0f ? normal : normal * (-1.0f);
// // 		//
	
// // 		/* compute two random numbers to pick a random point on the hemisphere above the hitpoint*/
// // 		float rand1 = 2.0f * PI * get_random(seed0, seed1);
// // 		float rand2 = get_random(seed0, seed1);
// // 		float rand2s = sqrt(rand2);

// // 		/* create a local orthogonal coordinate frame centered at the hitpoint */
// // 		float3 w = normal_facing;
// // 		float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) : (float3)(1.0f, 0.0f, 0.0f);
// // 		float3 u = normalize(cross(axis, w));
// // 		float3 v = cross(w, u);
// // 		float3 newdir;
// // 		/* use the coordinte frame and random numbers to compute the next ray direction */
// // 		newdir = normalize(u * cos(rand1)*rand2s + v*sin(rand1)*rand2s + w*sqrt(1.0f - rand2));
		
// // 		newdir = sample_hemisphere(w, 1, seed0, seed1);
// // 		//  else
// // 		// 	newdir = normalize((float3)(0.7f, 0.7f, 0.0f) - hitpoint);
// // 		/* add a very small offset to the hitpoint to prevent self intersection */
// // 		if (hitsphere.reflection > 0) {
// // 			ray.dir = reflect(ray.dir, normal_facing);
// // 			ray.origin = hitpoint + ray.dir * EPSILON;

// // 			accum_color += mask * hitsphere.emission; 	/* add the colour and light contributions to the accumulated colour */ 
// // 			mask *= hitsphere.color * lightSampling; //hitsphere.reflection;	/* the mask colour picks up surface colours at each bounce */
// // 		} else {
// // 			ray.dir = newdir;
// // 			ray.origin = hitpoint + ray.dir * EPSILON;
// // 			accum_color += mask * lightSampling;//;hitsphere.emission; 
// // 			mask *= hitsphere.color;
// // 		}
// // 		mask *= dot(newdir, normal_facing);
// // 	}
// // 	//color = INTEGRAL A * s(direction) * color(direction)
// // 	//Color = (A * s(direction) * color(direction)) / p(direction)
// // 	return accum_color;
// // }

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

// //#include "noise.h"

// /* function that returns a pseudo random number between 0 and 1 */

// // double rand_noise(int t)
// // {
// //     t = (t<<13) ^ t;
// //     t = (t * (t * t * 15731 + 789221) + 1376312589);
// //     return ((t & 0x7fffffff) / 1073741824.0);
// // }



// // static t_ray		camera_build_ray(constant t_camera *camera, int2 *screen)
// // {
// // 	t_ray			result;
// // 	float3			up;
// // 	float3			right;
// // 	float 			xf;
// // 	float 			yf;

// // 	xf = (float)screen->x;
// // 	yf = (float)screen->y;
// // 	result.origin = camera->position;
// // 	up = (float3)camera->axis_y * (float)(-1.f * yf + (camera->height - 1.f) / 2.f);
// // 	right = (float3)camera->axis_x * (float)(xf - (camera->width - 1.f) / 2.f);
// // 	result.direction = up + right + camera->forward;
// // 	result.direction = normalize(result.direction);
// // 	return (result);
// // }
// typedef enum e_figure
// {
// 	 SPHERE, CYLINDER, CONE, PLANE
// } t_type;
// typedef struct Object{
// 	float radius;
// 	float3 position;
// 	float3 color;
// 	float3 emission;
// 	float3 v;
// 	t_type type;
// 	float refraction;
// 	float reflection;
// 	float plane_d;
// } t_obj;

__kernel void render_kernel(__global int* output, int width, int height, int n_spheres, __constant t_obj* spheres,
__global float3 * vect_temp, int samples
	)
{
	
	unsigned int work_item_id = get_global_id(0);	/* the unique global id of the work item for the current pixel */
	unsigned int x_coord = work_item_id % width;			/* x-coordinate of the pixel */
	unsigned int y_coord = work_item_id / width;			/* y-coordinate of the pixel */

	/* seeds for random number generator */
	 unsigned int seed0 = x_coord + rand_noise(samples) * 12312 ;
	 unsigned int seed1 = y_coord + rand_noise(samples + 3) * 12312;
	// int2			screen;
	// // screen.x = global_id % camera->width;
	// screen.y = global_id / camera->width;
// Ray ray =  createCamRay(x_coord, y_coord, width,  height);
// 	t_cam cam = (t_cam){(	float3)(0.0f, 0.1f, 2.f), ray.dir};
	//t_camera racy_cam = camera_build_ray(cam, &screen);
	/* add the light contribution of each sample and average over all samples*/
		float3 finalcolor;
	if (samples == 15)
		finalcolor  = 0;
	else
		finalcolor = vect_temp[x_coord + y_coord * width];// (float3)(0.0f, 0.0f, 0.0f);
	
	 Ray camray = createCamRay(x_coord, y_coord, width, height);
	// // Ray camray.origin = camraysad.origin;

	if (x_coord == 0 && y_coord == 0)
	{
		printf("samples %d\n", samples);
	}
	for (int i = 0; i < 15; i++)
	{
		finalcolor += trace(spheres, &camray, n_spheres, &seed0, &seed1);
	}
	vect_temp[x_coord + y_coord * width] = finalcolor;
	// if(work_item_id == 0)
	// {
	// 	int inside_circle = 0;
	// 	int N = 1000000;
	// 	for (int i = 0; i < N; i++)
	// 	{
	// 		float x = 2 * noise_3d(seed0, seed1, i) - 1;
	// 		float y = 2 * noise_3d(seed0, seed1, i + 100) -1;
	// 		if (x* x + y * y < 1)
	// 			inside_circle++;
	// 	}
	// 	printf("\n\n Pi = %f\n\n", 4*float(inside_circle)/N);	
	// }
	// for (int i = 0; i < 20; i++)
	// 	printf("i :%d %d\n", work_item_id, get_random);
	//output[x_coord + y_coord * width] = -1;
	output[x_coord + y_coord * width] = ft_rgb_to_hex(toInt(finalcolor.x  / samples),
	 toInt(finalcolor.y  / samples), toInt(finalcolor.z  / samples)); /* simple interpolated colour gradient based on pixel coordinates */
	//output[x_coord + y_coord * width] = ft_rgb_to_hex(toInt(0), toInt(0), toInt(255)); /* simple interpolated colour gradient based on pixel coordinates */

}
