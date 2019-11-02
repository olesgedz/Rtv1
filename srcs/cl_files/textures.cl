#include "kernel.hl"

float3					get_color(t_obj *object, float3 hitpoint, t_scene *scene, float2 *coord)
{
	__global t_txture	*texture;
	int					i;

	if (object->texture > 0)
	{
		texture = &((scene->textures)[object->texture - 1]);
		i = ((int)(coord->y * (float)(texture->height))) * (texture->width) + (int)(coord->x * (float)(texture->width));
		return(cl_int_to_float3(texture->texture[i]));
	}
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
	u = 0.5 + (atan2(vect[2], vect[0])) / (2 * PI);
	v = 0.5 - (asin(vect[1])) / PI;
	texture = &((scene->textures)[0]);
	i = ((int)(v * (float)(texture->height - 1))) * (texture->width) + (int)(u * (float)(texture->width - 1));
	return(cl_int_to_float3(texture->texture[i]));
}