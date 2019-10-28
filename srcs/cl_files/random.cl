#include "kernel.hl"
#include "options.cl"

static float		rng_lgc(global ulong *rng_state)
{
	int				gi;
	ulong			x;

	gi = get_global_id(0);
	x = rng_state[gi];
	x = (0x5DEECE66DL * x + 0xBL) & ((1L << 32) - 1);
	rng_state[gi] = x;
    return ((float)x / (1L << 32));
}

static float		rng(global ulong *rng_state)
{
	return (rng_lgc(rng_state));
}

static float rng_range(global ulong *rng_state, float a, float b)
{
	if (a < b)
		return (rng(rng_state) * (b - a) + a);
	else
		return (rng(rng_state) * (a - b) + b);

}

static float3		sphere_random(global t_obj *object, global ulong *rnd)
{
	float 			theta;
	float 			phi;
	float3			random;

	theta = rng(rnd) * PI;
	phi = rng(rnd) * 2 * PI;
	random.x = 0.5 * object->radius * sin(theta) * cos(phi);
	random.y = 0.5 * object->radius * sin(theta) * sin(phi);
	random.z = 0.5 * object->radius * cos(theta);
	random = random + object->position;
	return (random);
}

static void			create_coordinate_system(float3 *normal, float3 *nt, float3 *nb)
{
	if (normal->x != 0.0f || normal->z != 0.0f)
		*nt = (float3){normal->z, 0., -1.f * normal->x};
	else
		*nt = (float3){0., -1.f * normal->z, normal->y};
	*nt = normalize(*nt);
	*nb = normalize(cross(*normal, *nt));
}

static float3		convert_sample(float3 *normal, float3 *sample, float3 *nt, float3 *nb)
{
	return (sample->x * (*nt) + sample->z * (*normal) + sample->y * (*nb));
}

static float3		sampler_transform(float3 *normal, float3 *sample)
{
	float3		nt;
	float3		nb;

	create_coordinate_system(normal, &nt, &nb);
	return (convert_sample(normal, sample, &nt, &nb));
}

static float3		sample_uniform
					(float3 *normal,
					float *cosine,
					t_scene * scene)
{
	float3 			r;
	float3			ret;
	// float3			sample;
	// float			sin_theta;
	// float			phi;

	r.z = rng(scene->random);
	r.x = rng(scene->random) * 2.f - 1.f;
	r.y = rng(scene->random) * 2.f - 1.f;
	// sin_theta = sqrt(max(0.0f , 1.0f - r.x * r.x));
	// phi = 2.0f * PI * r.y;
	ret = normalize(sampler_transform(normal, &r));
	*cosine = dot(*normal, ret);
	// if (get_global_id(0) == 16000)
	// 	printf("%f %f %f\n", ret.x, ret.y, ret.z);
	// sample = (float3)
	// 	{
	// 		sin_theta * cos(phi),
	// 		r[0],
	// 		sin_theta * sin(phi)
	// 	};
	return (ret);
}

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