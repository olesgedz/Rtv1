#include "options.cl"

static float ft_solve(float a, float b, float c)
{
	float  disc = b * b - 4*a*c;
   	float temp = 1/(2*a);
	float res1;
	float res2;

 	if (disc < 0.0f)
		return 0.0f;

	disc = sqrt(disc);
	res1 = (-b - disc) * temp;
	res2 = (-b + disc) * temp;
	if ((res1) > EPSILON && res2 > EPSILON)
		return res1 <= res2 ? res1 : res2;
	if (res1 > EPSILON || res2 > EPSILON)
		return res1 <= res2 ? res2 : res1;
	return(0.f);
}

static float intersect_cone(__global t_obj* cone, const t_ray *  ray)
{
	float3	x = ray->origin - cone->position;
	float	a = dot(ray->dir, cone->v);
	float	c = dot(x, cone->v);
	float	temp = 1 + cone->radius * cone->radius;
	float	b = 2.0 * (dot(ray->dir, x) - temp * a * c);

	a = dot(ray->dir, ray->dir) - temp * a * a;
	c = dot(x, x) - temp * c * c;
	return (ft_solve(a, b, c));
}

static float intersect_sphere(__global t_obj *sphere,  t_ray *  ray)
{
	float3 rayToCenter = ray->origin - sphere->position;
    float a = 1;
    float b = 2*dot(rayToCenter, ray->dir);
    float c = dot(rayToCenter, rayToCenter) - sphere->radius*sphere->radius;
	return (ft_solve(a, b, c));
}

static float		intersect_plane(__global t_obj *plane, const t_ray *ray)
{
	float	a;
	float	b;
	a = dot(plane->v, ray->dir);
	if (fabs(a) < EPSILON)
		return (0);
	b = -(dot(ray->origin - plane->position, plane->v)) / a;
	return (b < EPSILON) ? 0 : b;
}


static float		intersect_cylinder(__global t_obj *cylinder, const t_ray *  ray)
{
	float3	x = ray->origin - cylinder->position;
	float	a = dot(ray->dir, cylinder->v);
	float	c = dot(x, cylinder->v);
	float	b = 2 * (dot(ray->dir, x) - a * dot(x, cylinder->v));

	a = dot(ray->dir, ray->dir) - a * a;
	c = dot(x, x) - c * c - cylinder->radius * cylinder->radius;
	return (ft_solve(a, b, c));
}

static int inside_triangle(__global t_obj *triangle, float3 collision)
{
	if (dot(triangle->v, cross(triangle->vertices[1] - triangle->vertices[0], collision - triangle->vertices[0])) > 0 &&
		dot(triangle->v, cross(triangle->vertices[2] - triangle->vertices[1], collision - triangle->vertices[1])) > 0 &&
		dot(triangle->v, cross(triangle->vertices[0] - triangle->vertices[2], collision - triangle->vertices[2])) > 0)
		return(1);
	return(0);
}

static float		intersect_triangle(__global t_obj *triangle,  t_ray *  ray)
{
	float	a;
	float	b;


	a = dot(triangle->v, ray->dir);
	if (fabs(a) < EPSILON)
		return (0);
	b = -(dot(ray->origin - triangle->vertices[1], triangle->v)) / a;
	if (!inside_triangle(triangle, ray->origin + ray->dir * b))
		return (0);
	return (b < EPSILON) ? 0 : b;
}

static float	intersect_parabol(__global t_obj *parabol, t_ray *ray)
{
	float3 pos =  ray->origin - parabol->position;
	float3 dir =  ray->dir;
	float dv = dot(ray->dir, parabol->v);
	float xv = dot(pos, parabol->v);
	float a = dot(ray->dir, ray->dir) - dv * dv;
	float b = 2 * (dot(ray->dir, pos) - dv * (xv + 2 * parabol->radius));
	float c = dot(pos, pos) - xv * (xv + 4 * parabol->radius);
	return (ft_solve(a, b, c));
}

void positive_discriminant(double Q, __double2 koefs, double *solve, double b)
{
	double alpha, betha, ntmp;

	ntmp = -koefs[1] / 3.f;
		alpha = cbrt(-koefs[0] / 2.f + sqrt(Q));
		betha = -koefs[1] / (3.f * alpha);
		*solve = alpha + betha - b;
}

void negative_discriminant(double Q, __double2 koefs, double *solve, double b)
{
	double cosphi, tmp, ntmp, phi;

	tmp = -3.f / koefs.y;
	ntmp = -koefs.y / 3.f;
	cosphi = -koefs.x * 0.5f * sqrt(tmp * tmp * tmp);
	phi = acos(cosphi);
	*solve = 2.f * sqrt(ntmp) * cos(phi / 3.f) - b;
}


void fourth_degree_equation_solver(__float4 koefs, __float2 *solve)
{
	__double3 ferrari_koefs, cubic_resol_koefs;
	__double2 cubic_two_params_koefs;
	double a2, a3, a4, p2, b2, Q, cubic_solve;
	t_quad q;

	a2 = koefs[3] * koefs[3];
	a3 = a2 * koefs[3];
	a4 = a2 * a2;
	//y4+py2+qy+r=0
	ferrari_koefs[2] = koefs[2] - 0.375f * a2;
	ferrari_koefs[1] = 0.125f * a3 - 0.5f * koefs[2] * koefs[3] + koefs[1];
	ferrari_koefs[0] = (-0.01171875f) * a4 + 0.0625f * koefs[2] * a2 - 0.25f * koefs[1] * koefs[3] + koefs[0];
	if (ferrari_koefs[1] * ferrari_koefs[1] < 1e-4)
	{
		q.b = ferrari_koefs[2];
		q.c = ferrari_koefs[0];
		q.d = q.b * q.b - 4.f * q.c + 1e-4;
		if (q.d >= 0.f)
		{
			q.d = sqrt(q.d);
			(*solve)[0] = (-q.b - q.d) / 2.f;
			(*solve)[1] = (-q.b + q.d) / 2.f;
			if ((*solve)[0] >= 0.f)
				(*solve)[0] = (q.res = -sqrt((*solve)[0]) - koefs[3] / 4.f) > 0.f ? q.res : sqrt((*solve)[0]) - koefs[3] / 4.f;
			if ((*solve)[1] >= 0.f)
				(*solve)[1] = (q.res = -sqrt((*solve)[1]) - koefs[3] / 4.f) > 0.f ? q.res : sqrt((*solve)[1]) - koefs[3] / 4.f;
		}
		return;
	}
	//y3+py2+qy+r=0
	cubic_resol_koefs[2] = (-0.5f) * ferrari_koefs[2];
	cubic_resol_koefs[1] = -ferrari_koefs[0];
	cubic_resol_koefs[0] = (-0.125f) * ferrari_koefs[1] * ferrari_koefs[1] + 0.5f * ferrari_koefs[0] * ferrari_koefs[2];
	p2 = cubic_resol_koefs[2] * cubic_resol_koefs[2];
	//y3+py+q=0
	cubic_two_params_koefs[1] = cubic_resol_koefs[1] - p2 / 3.f;
	cubic_two_params_koefs[0] = cubic_resol_koefs[0] + 2.f * p2  * cubic_resol_koefs[2] / 27.f - cubic_resol_koefs[2] * cubic_resol_koefs[1] / 3.f;
	//y = z+t, 3zt+p = 0
	b2 = cubic_two_params_koefs[0] * cubic_two_params_koefs[0];
	Q = cubic_two_params_koefs[1] * cubic_two_params_koefs[1] * cubic_two_params_koefs[1] / 27.f + cubic_two_params_koefs[0] * cubic_two_params_koefs[0] / 4.f;
	if (Q > 0)
		positive_discriminant(Q, cubic_two_params_koefs, &cubic_solve, cubic_resol_koefs[2] / 3.f);
	else
		negative_discriminant(Q, cubic_two_params_koefs, &cubic_solve, cubic_resol_koefs[2] / 3.f);
	if ((q.b = 2.f * cubic_solve - ferrari_koefs[2]) > 0.f ) {
		q.a = q.b;
		q.b = -sqrt(q.b);
		q.c = ferrari_koefs[1] / (-2.f * q.b) + cubic_solve;
		q.d = q.a - 4.f * q.c + 1e-4;
		if (q.d >= 0.f)
		{
			q.d = sqrt(q.d);
			(*solve)[0] =
					(q.res = (-q.b - q.d) / 2.f - koefs[3] / 4.f) > 0.f
					? q.res : (-q.b + q.d) / 2.f - koefs[3] / 4.f;
		}
		q.b = -q.b;
		q.c = ferrari_koefs[1] / (-2.f * q.b) + cubic_solve;
		q.d = q.a - 4.f * q.c + 1e-4;
		if (q.d >= 0.f)
		{
			q.d = sqrt(q.d);
			(*solve)[1] =
					(q.res = (-q.b - q.d) / 2.f - koefs[3] / 4.f) > 0.f
					? q.res : (-q.b + q.d) / 2.f - koefs[3] / 4.f;
		}
	}
}


float intersection_torus(__global t_obj *torus, t_ray *ray)
{
	__float3    x;
	__float4 equation_koefs, dots,qq;
	__float2 solve = (__float2){-1.f, -1.f};
	float R2, r2, Rr, dist;

	Rr = torus->radius + torus->tor_radius + 1;
	x = ray->origin - torus->position;
	dist = length(x) - Rr;
	if (dist > 0.f)
		x += ray->dir * dist;
	else
		dist = 0.f;
	R2 = torus->radius * torus->radius;
	r2 = torus->tor_radius * torus->tor_radius;
	//ax4+bx3+cx2+dx1+e
	//a == 1
	dots[0] = dot(x, torus->v);
	dots[1] = dot(ray->dir, torus->v);
	dots[2] = dot(x, x);
	dots[3] = dot(x, ray->dir);
	qq[0] = 1.0f - dots[1] * dots[1];
	qq[1] = 2.0f * (dots[3] - dots[0] * dots[1]);
	qq[2] = dots[2] - dots[0] * dots[0];
	qq[3] = dots[2] + R2 - r2;
	equation_koefs[3] = 4.0f * dots[3];
	equation_koefs[2] = 2.0f * qq[3] + equation_koefs[3] * equation_koefs[3] * 0.25f - 4.0f * R2 * qq[0];
	equation_koefs[1] = equation_koefs[3] * qq[3] - 4.0f * R2 * qq[1];
	equation_koefs[0] = qq[3] * qq[3] - 4.0f * R2 * qq[2];
	fourth_degree_equation_solver(equation_koefs, &solve);

	if(solve[0] > 0)
	{
		if(solve[1] > 0)
			return (solve[0] < solve[1] ? solve[0] + dist : solve[1] + dist);
		else
			return (solve[0] + dist);
	}
	else if (solve[1] > 0)
		return (solve[1] + dist);
	else
		return(0.f);
}


