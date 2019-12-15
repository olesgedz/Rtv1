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

constant int hash[] = {208,34,231,213,32,248,233,56,161,78,24,140,71,48,140,254,245,255,247,247,40,
					 185,248,251,245,28,124,204,204,76,36,1,107,28,234,163,202,224,245,128,167,204,
					 9,92,217,54,239,174,173,102,193,189,190,121,100,108,167,44,43,77,180,204,8,81,
					 70,223,11,38,24,254,210,210,177,32,81,195,243,125,8,169,112,32,97,53,195,13,
					 203,9,47,104,125,117,114,124,165,203,181,235,193,206,70,180,174,0,167,181,41,
					 164,30,116,127,198,245,146,87,224,149,206,57,4,192,210,65,210,129,240,178,105,
					 228,108,245,148,140,40,35,195,38,58,65,207,215,253,65,85,208,76,62,3,237,55,89,
					 232,50,217,64,244,157,199,121,252,90,17,212,203,149,152,140,187,234,177,73,174,
					 193,100,192,143,97,53,145,135,19,103,13,90,135,151,199,91,239,247,33,39,145,
					 101,120,99,3,186,86,99,41,237,203,111,79,220,135,158,42,30,154,120,67,87,167,
					 135,176,183,191,253,115,184,21,233,58,129,233,142,39,128,211,118,137,139,255,
					 114,20,218,113,154,27,127,246,250,1,8,198,250,209,92,222,173,21,88,102,219};

int noise2(int x, int y)
{
	int tmp = hash[(y + 4) % 256];
	return hash[(tmp + x) % 256];
}

float lin_inter(float x, float y, float s)
{
	return x + s * (y-x);
}

float smooth_inter(float x, float y, float s)
{
	return lin_inter(x, y, s * s * (3-2*s));
}

float	noise2d(float x, float y)
{
	int x_int = x;
	int y_int = y;
	float x_frac = x - x_int;
	float y_frac = y - y_int;
	int s = noise2(x_int, y_int);
	int t = noise2(x_int+1, y_int);
	int u = noise2(x_int, y_int+1);
	int v = noise2(x_int+1, y_int+1);
	float low = smooth_inter(s, t, x_frac);
	float high = smooth_inter(u, v, x_frac);
	return smooth_inter(low, high, y_frac);
}

float	perlin_noise(float2 coord)
{
	float	freq = 50.f;
	float	amp = 1.f;
	float	fin = 0;
	float	div = 0.0;

	float	xa = coord.x * freq;
	float	ya = coord.y * freq;

	for (int i = 0; i < 5; ++i)
	{
		div += 256 * amp;
		fin += noise2d(xa, ya) * amp;
		amp /= 2;
		xa *= 2;
		ya *= 2;
	}

	return (fin / div);
}


float3					get_color(t_obj *object, float3 hitpoint, t_scene *scene, float2 *coord)
{
	__global t_txture	*texture;
	int					i;

	if (object->texture > 0)
	{
		texture = &((scene->textures)[object->texture - 1]);
		i = ((int)(coord->y * (float)(texture->height))) * (texture->width) + (int)(coord->x * (float)(texture->width));
	if (object->transparency == 0)
		{
			object->transparency = 1.f - (float)(texture->texture[i] >> 24 & 0xFF) / 255.f;
			if (object->transparency > 0.99)
				return ((float3)(1.f, 1.f, 1.f));
		}
		return (cl_int_to_float3(texture->texture[i]));
	}
	else if (object->texture == -1)
		return (chess(object, coord));
	else if (object->texture == -2)
	{
		float val = perlin_noise(*coord);
		return (object->color * val);
	}
	else if (object->texture == -3)
	{
		float cos1 = cos(coord->y * PI);
		cos1 = cos1 < 0 ? -cos1 : cos1;
		float cos2 = cos(coord->x * PI);
		cos2 = cos2 < 0 ? -cos2 : cos2;
		return object->color * cos1 * cos2;
		//return (object->color * clamp(fabs(sin((coord->x + coord->y) * object->prolapse.x * object->prolapse.y)), 0.5f, 1.0f));
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
	u = 0.5 + (atan2(vect.z, vect.x)) / (2 * PI);
	v = 0.5 - (asin(vect.y)) / PI;
	texture = &((scene->textures)[scene->global_texture_id]);
	i = ((int)(v * (float)(texture->height - 1))) * (texture->width) + (int)(u * (float)(texture->width - 1));
	return(cl_int_to_float3(texture->texture[i]));
}
