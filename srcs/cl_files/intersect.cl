#include "options.cl"

static float ft_solve(float a, float b, float c)
{
	float  disc = b * b - 4*a*c;
   	float temp = 1/(2*a);
	float res;

 	if (disc < 0.0f) 
		return 0.0f;
	
	disc = sqrt(disc);
	if ((res = (-b - disc) * temp) > EPSILON)
		return res;
    if ((res = (-b + disc) * temp) > EPSILON)
		return res;
	return(0.f);
}

				/* (__global Sphere* sphere, const Ray* ray) */
static float intersect_cone(const t_obj* cone, const Ray* ray) /* version using local copy of sphere */
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

static float intersect_sphere(const t_obj* sphere, const Ray* ray) /* version using local copy of sphere */
{
	float3 rayToCenter = ray->origin - sphere->position;
    float a = 1;
    float b = 2*dot(rayToCenter, ray->dir);
    float c = dot(rayToCenter, rayToCenter) - sphere->radius*sphere->radius;	
	return (ft_solve(a, b, c));
}

double		intersect_plane(const t_obj* plane, const Ray* ray)
{
	double	a;
	double	b;
	a = dot(plane->position, ray->dir);//ft_vec3_dot_multiply(ft_vec3_substract(ray->orig, plane->point), plane->normal);
	//b = ft_vec3_dot_multiply(ray->dir, plane->normal);
	if (a == 0)
		return (0);
	b = -(dot(plane->position, ray->origin) + plane->plane_d) / a;
	return (b < EPSILON) ? 0 : b;
}

static double		intersect_cylinder(const t_obj* cylinder, const Ray* ray)
{
	float3	x = ray->origin - cylinder->position;
	double	a = dot(ray->dir, cylinder->v);
	double	c = dot(x, cylinder->v);
	double	b = 2 * (dot(ray->dir, x) - a * dot(x, cylinder->v));

	a = dot(ray->dir, ray->dir) - a * a;
	c = dot(x, x) - c * c - cylinder->radius * cylinder->radius;
	return (ft_solve(a, b, c));
}

