#include "options.cl"

static float3	get_cone_normal(float3 hitpoint, __constant t_obj *sphere)
{
	return(normalize(hitpoint - sphere->position));
}

static float3	get_cylinder_normal(float3 hitpoint, __constant t_obj *sphere)
{
	float3		norm;
	float3		cp = sphere->position - hitpoint;
	float3		g = dot(sphere->v, cp) * sphere->v;

	norm = normalize(g - cp);
	return(norm);
}

float3      	get_surface_normal(float3 hitpoint, __constant t_obj *sphere)
{
	if (sphere->type == SPHERE)
		return (normalize(hitpoint - sphere->position));
	else if (sphere->type == CYLINDER)
		return (get_cylinder_normal(hitpoint, sphere));
	else if (sphere->type == CONE)
		return (get_cone_normal(hitpoint, sphere));
	else
		return (normalize(sphere->v));
}