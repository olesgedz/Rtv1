#include "options.cl"

static float3	get_cone_normal(t_obj * object, t_intersection * intersection)
{
	float3		norm;
	float3		center_to_point;
	float3		tangent;

	center_to_point = intersection->hitpoint - object->position;
	tangent = cross(center_to_point, object->v);
	norm = cross(tangent, center_to_point);
	return(normalize(norm));
}

static float3	get_cylinder_normal(t_obj * object, t_intersection * intersection)
	{
		float3		norm;
		float3		cp = object->position - intersection->hitpoint;
		float3		g = dot(object->v, cp) * object->v;

		norm = -normalize(g - cp);
		return(norm);
	}

static float3 sphere_get_normal(t_obj * object, t_intersection * intersection)
{
	return (normalize(intersection->hitpoint - object->position));
}

static float3 plane_get_normal(t_obj *object, t_intersection *intersection)
{
	return (object->v);
}

float3 get_normal(t_obj *object, t_intersection *intersection, float2 *coord, t_scene *scene)
{
	float3 normal;

	if (object->type == PLANE)
	 	normal = plane_get_normal(object, intersection);
	else if (object->type == CYLINDER)
	 	normal = get_cylinder_normal(object, intersection);
	else if (object->type == CONE)
	 	normal = get_cone_normal(object, intersection);
	else if (object->type == TRIANGLE)
		normal = object->v;
	else if (object->type == PARABOLOID)
	{
		normal = intersection->hitpoint - object->v * object->radius;
		normal = normalize(normal);
	}
	else if (object->type == TORUS)
	{
		float3 govno = intersection->hitpoint;

		govno -= object->position;
		normal = govno - dot(govno, object->v) * object->v;
		normal = normalize(normal);
		normal = govno - normal * object->radius;
		normal = normalize(normal);
	}
	else
		normal = sphere_get_normal(object, intersection);
	// if (dot(intersection->ray.dir, normal) < 0)
	// 	normal = -normal;
	if (object->normal != 0)
	{
		normal = normal_map(object, intersection, normal, coord, scene);
	}
	return (normal);
}
