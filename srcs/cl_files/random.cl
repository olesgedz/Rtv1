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
					t_scene * scene, float metalness)
{
	float3 			r;
	float3			ret;
	// float 			phi, theta;
	// float 			thetasin;

	metalness = cos(PI * 0.5f * metalness);
	// phi = rng(scene->random) * 2 * PI;
	// theta = rng(scene->random) * 2 * PI;
	// thetasin = sin(theta);
	// r.x = thetasin * cos(phi) * metalness;
	// r.y = thetasin * sin(phi) * metalness;
	// r.z = sqrt(fabs(1.f - r.x * r.x - r.y * r.y));
	// r = normalize(r);
	r.x = (rng(scene->random) * 2.f - 1.f);
	r.y = ((rng(scene->random) * 2.f - 1.f)) * sqrt(1.f - r.x * r.x);
	r *= metalness;
	r.z = sqrt(fabs(1.f - r.y * r.y - r.x * r.x));
	ret = sampler_transform(normal, &r);
	return (ret);
}

