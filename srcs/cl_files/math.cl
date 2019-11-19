static int	ft_rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}

static float u_clamp(float x)
{
	return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
}

static int	c_floor(float x)
{
	return (x < 0.0f ? 0 : x > 255.f ? 255 : (char)floor(x));
}

static int toInt(float x)
{
	return (int)(c_floor(x * 255.f));
}

float cl_float3_max(float3 v)
{
	return (fmax(fmax(v.x, v.y), v.z));
}

float cl_float3_min(float3 v)
{
	return (fmin(fmin(v.x, v.y), v.z));
}

float3		cl_int_to_float3(int i)
{
	float3		flt;

	flt.z = ((float)((i >> 16) & 255)) / 255;
	flt.y = ((float)((i >> 8) & 255)) / 255;
	flt.x = ((float)((i) & 255)) / 255;
	return (flt);
}
