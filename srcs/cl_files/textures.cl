#include "kernel.hl"
float3					chess(t_obj *object, float2 *coord)
{
	if ((coord->x > 0.5f && coord->y > 0.5f) || (coord->x  < 0.5f && coord->y < 0.5f))
	{
		object->transparency = 1.f;
		return (cl_int_to_float3(0xFFFFFF));
	}
	return (object->color);
}

float3					get_color(t_obj *object, float3 hitpoint, t_scene *scene, float2 *coord)
{
	__global t_txture	*texture;
	int					i;

	if (object->texture > 0)
	{
		texture = &((scene->textures)[object->texture - 1]);
		i = ((int)(coord->y * (float)(texture->height))) * (texture->width) + (int)(coord->x * (float)(texture->width));
		if (((texture->texture[i] >> 24) && 0xFFFF) == 0)
			object->transparency = 1.f;// - (float)(texture->texture[i] >> 24 && 0xFFFF) / 255.f;
		return(cl_int_to_float3(texture->texture[i]));
	}
	else if (object->texture == -1)
		return (chess(object, coord));
	else if (object->texture == -2) // just for check, it's not perlin it's some weird stuff i've snatched from internet
		return (object->color * clamp(fabs(sin((coord->x + coord->y) * object->prolapse.x * object->prolapse.y)), 0.5f, 1.0f));
	else 
		return (object->color);
}

float3					global_texture(t_ray *ray, t_scene *scene)
{
	float3				vect;
	__global t_txture	*texture;
	float				u;
	float				v;
	int					i;

	vect = ray->dir;
	u = 0.5 + (atan2(vect.z, vect.x)) / (2 * PI);
	v = 0.5 - (asin(vect.y)) / PI;
	texture = &((scene->textures)[scene->global_texture_id]);
	i = ((int)(v * (float)(texture->height - 1))) * (texture->width) + (int)(u * (float)(texture->width - 1));
	return(cl_int_to_float3(texture->texture[i]));
}