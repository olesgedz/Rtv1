static int	ft_rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
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