#include "options.cl"

static void			get_color_sphere(t_obj *object, float3 hitpoint, t_scene *scene, float2 *coord)
{
	float3				vect;

	vect = normalize(hitpoint - object->position);
	vect = (float3)(dot(object->basis[0], vect), dot(object->basis[1], vect), dot(object->basis[2], vect));
	// vect.zx = vect.xz;
	coord->x = 0.5 + (atan2(vect.z, vect.x)) / (2 * PI);
	coord->y = 0.5 - (asin(vect.y)) / PI;
}

static void			get_color_plane(t_obj *object, float3 hitpoint, t_scene *scene, float2 *coord)
{
    float           u;
    float           v;

	u = modf((0.5 + object->shift.x + dot(object->basis[0], hitpoint) * object->prolapse.x / 2), &(u));
	v = modf((0.5 + object->shift.y + dot(object->basis[1], hitpoint) * object->prolapse.y / 2), &(v));
	if (v < 0)
		v += 1;
	if (u < 0)
		u += 1;
    coord->x = u;
    coord->y = v;
}

static void			get_color_cylinder(t_obj *object, float3 hitpoint, t_scene *scene, float2 *coord)
{
	float3				vect;
	float3				a;
    __global t_txture	*texture;
    float               v;

	vect = hitpoint - object->position;
	a.y = dot(object->v, vect);
	a.x = -dot(vect, object->basis[0]);
	a.z = dot(vect, object->basis[1]) + object->shift.y;
	coord->x = 0.5 + (atan2(a.z, a.x)) / (2 * PI);
    texture = &((scene->textures)[object->texture - 1]);
	v = modf(0.5 + (a.y * object->prolapse.y), &v);
	if (v < 0)
		v += 1;
    coord->y = v;
}

static void			get_color_cone(t_obj *object, float3 hitpoint, t_scene *scene, float2 *coord)
{
	float3				vect;
	float3				a;
    __global t_txture	*texture;
    float               v;

	vect = hitpoint - object->position;
	a.y = length(vect) * length(vect) / dot(object->v, vect);
	a.x = -dot(vect, object->basis[0]);
	a.z = dot(vect, object->basis[1]) + object->shift.y;
	coord->x = 0.5 + (atan2(a.z, a.x)) / (2 * PI);
    texture = &((scene->textures)[object->texture - 1]);
	v = modf(0.5 + (a.y * object->prolapse.y), &v);
	if (v < 0)
		v += 1;
    coord->y = v;
}

static void			interpolate_uv(t_obj *object, float3 hitpoint, t_scene *scene, float2 *coord)
{
	if (object->type == SPHERE || object->type == TORUS)
		get_color_sphere(object, hitpoint, scene, coord);
	else if (object->type == CYLINDER)
		get_color_cylinder(object, hitpoint, scene, coord);
	else if (object->type == PLANE)
		get_color_plane(object, hitpoint, scene, coord);
	else if (object->type == CONE)
		get_color_cone(object, hitpoint, scene, coord);
}