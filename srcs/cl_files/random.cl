#include "options.cl"

static float get_random( int *seed0, int *seed1) {

	/* hash the seeds using bitwise AND operations and bitshifts */
	*seed0 = 36969 * ((*seed0) & 65535) + ((*seed0) >> 16);  
	*seed1 = 18000 * ((*seed1) & 65535) + ((*seed1) >> 16);

	unsigned int ires = ((*seed0) << 16) + (*seed1);

	/* use union struct to convert int to float */
	union 
	{
		float f;
		unsigned int ui;
	} res;

	res.ui = (ires & 0x007fffff) | 0x40000000;  /* bitwise AND, bitwise OR */
	return (res.f - 2.0f) / 2.0f;
}

int rand(int* seed) // 1 <= *seed < m
{
    int const a = 16807; //ie 7**5
    int const m = 2; //ie 2**31-1

    *seed = ((long)(*seed * a)) % m - 1;
    return(*seed);
}


float3	sample_hemisphere(float3 w, float max_r, int *seed0, int *seed1)
{
	float rand1 = 2.0f * PI * get_random(seed0, seed1);
	float rand2 = get_random(seed0, seed1) * max_r;
	float rand2s = sqrt(rand2);

	float3 axis = fabs(w.x) > 0.1f ? (float3)(0.0f, 1.0f, 0.0f) :
		(float3)(1.0f, 0.0f, 0.0f);
	float3 u = normalize(cross(axis, w));
	float3 v = cross(w, u);

	float3 newdir = normalize(u * cos(rand1)*rand2s +
		v*sin(rand1)*rand2s +w*sqrt(1.0f - rand2));

	return (newdir);
}

double rand_noise(int t)
{
    t = (t<<13) ^ t;
    t = (t * (t * t * 15731 + 789221) + 1376312589);
    return ((t & 0x7fffffff) / 2147483648.0);
}


/* takes 3 int to return a double between 0 and 1 */

double noise_3d(int x, int y, int z)
{
	int		tmp1;
	int		tmp2;
    tmp1 = rand_noise(x) * 850000;
    tmp2 = rand_noise (tmp1 + y) * 850000 ;
    return(rand_noise(tmp2 + z));
}

unsigned int ParallelRNG( unsigned int x )
{
	unsigned int value = x;

	value = (value ^ 61) ^ (value>>16);
	value *= 9;
	value ^= value << 4;
	value *= 0x27d4eb2d;
	value ^= value >> 15;

	return value;
}

unsigned int ParallelRNG3( unsigned int x,  unsigned int y,  unsigned int z )
{
	unsigned int value = ParallelRNG(x);

	value = ParallelRNG( y ^ value );

	value = ParallelRNG( z ^ value );

	return value;
}