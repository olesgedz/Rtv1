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

	// if (object->type == SPHERE)
		normal = sphere_get_normal(object, intersection);
	// else if (object->type == PLANE)
	// 	normal = plane_get_normal(object, intersection);
	return (normalize(normal));
}
