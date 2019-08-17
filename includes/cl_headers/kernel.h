
#ifndef KERNEL_H
#define KERNEL_H

typedef struct s_ray
{
	float3 origin;
	float3 dir;
	float	t;
} t_ray;

typedef struct 		s_material
{
	float3			color;
	float3			emission;
}					t_material;


typedef struct		s_intersection
{
	t_ray			ray;
	float3			hitpoint;
	float3			normal;
	t_material		material;
	int 			object_id;
}					t_intersection;


typedef enum e_figure
{
	 SPHERE, CYLINDER, CONE, PLANE
} t_type;

typedef struct Object{
	float radius;
	float3 position;
	float3 color;
	float3 emission;
	float3 v;
	t_type type;
	float refraction;
	float reflection;
	float plane_d;
} t_obj;
// typedef struct s_scene{

// 	__global t_obj * objects;
// 	int n_objects;
// 	unsigned int global_id;
// 	unsigned int x_coord;
// 	unsigned int y_coord;
// 	int width;
// 	int height;
// 	int samples;
// 	unsigned int seed0;
// 	unsigned int seed1;
// } t_scene;

#endif