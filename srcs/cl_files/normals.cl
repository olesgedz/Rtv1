#include "options.cl"

static float3	get_cone_normal(t_obj * object, t_intersection * intersection)
{
	return(normalize(intersection->hitpoint - object->position));
}

// static float3	get_cylinder_normal(t_obj * object, t_intersection * intersection)
// {
// 	float3		norm;
// 	float m;
// 	float3 p;

// 	// m = dot(intersection->ray.dir, object->v) * intersection->ray.t +
// 	// 	dot(intersection->ray.origin -  object->position,  object->v);
// 	// p = intersection->ray.origin + intersection->ray.dir * intersection->ray.t;
// 	// norm = normalize(p - object->position - (object->v * m));
// 	// if (dot(intersection->ray.dir, norm) > EPSILON)
// 	// 	norm = norm * -1;
// 	float3		cp = object->position - intersection->hitpoint;
// 	float3		g = dot(object->v, cp) * object->v;

// 	norm = normalize(g - cp);
// 	if (dot(intersection->ray.dir, norm) > EPSILON)
// 		norm = norm * -1;
// 	return(norm);
// }

// static float3	get_cylinder_normal(float3 hitpoint, t_obj *sphere)
// 	{
// 		float3		norm;
// 		float3		cp = sphere->position - hitpoint;
// 		float3		g = dot(sphere->v, cp) * sphere->v;
	
// 		norm = normalize(g - cp);
// 		return(norm);
// 	}

static float3	get_cylinder_normal(t_obj * object, t_intersection * intersection)
	{
		float3		norm;
		float3		cp = object->position - intersection->hitpoint;
		float3		g = dot(object->v, cp) * object->v;
	
		norm = normalize(g - cp);
		return(norm);
	}

static float3 sphere_get_normal(t_obj * object, t_intersection * intersection)
{
	return (intersection->hitpoint - object->position);
}

static float3 plane_get_normal(t_obj * object, t_intersection * intersection)
{
	if (dot(intersection->ray.dir,object->v) < 0)
		return (object->v);
	return (object->v * -1);
}

float3 get_normal(t_obj * object, t_intersection * intersection)
{
	float3 normal;

	if (object->type == PLANE)
	 	normal = plane_get_normal(object, intersection);
	else if (object->type == CYLINDER)
	 	normal = get_cylinder_normal(object, intersection);
	else if (object->type == CONE)
	 	normal = plane_get_normal(object, intersection);
	else if (object->type == TRIANGLE)
		normal = object->v;
	else 
		normal = sphere_get_normal(object, intersection);

	// if (sphere->type == CYLINDER)
	// 
	return (normalize(normal));
}
