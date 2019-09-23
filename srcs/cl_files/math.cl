static int	ft_rgb_to_hex(int r, int g, int b)
{
	return (r << 0 | g << 8 | b << 16);
}

static float u_clamp(float x)
{
	return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
}

static int toInt(float x)
{ 
	return int(u_clamp(x) * 255);
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

	// flt[0] = ((float)((i >> 16) & 255)) / 255;
	// flt[1] = ((float)((i >> 8) & 255)) / 255;
	// flt[2] = ((float)((i) & 255)) / 255;
	flt[0] = ((float)((i >> 16) & 255)) / 255;
	flt[1] = ((float)((i >> 8) & 255)) / 255;
	flt[2] = ((float)((i) & 255)) / 255;
	return (flt);
}