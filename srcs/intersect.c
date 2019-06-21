/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:17:28 by jblack-b          #+#    #+#             */
/*   Updated: 2019/06/21 16:39:45 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
# define DROUND(d)	ABS(d) < 0.00001 ? 0 : (d)

double				quandratic_solve(double k1, double k2, double k3)
{
	double			diskr;
	double			t1;
	double			t2;
	double			tmp;

	diskr = k2 * k2 - 4 * k1 * k3;
	if (diskr < 0)
		return (0);
	t1 = (-k2 + sqrt(diskr)) / (2 * k1);
	t2 = (-k2 - sqrt(diskr)) / (2 * k1);
	if (t1 > t2)
	{
		tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
	if (t1 < 0.003)
		t1 = t2;
	if (t1 < 0.003)
		return (-1.);
	return (t1);
}

double		get_t(double a, double b, double d, float *t0)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(d)) / (2 * a);
	t2 = (-b + sqrt(d)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (*t0 = t1);
	if ((t2 <= t1 && t2 >= 0) || (t2 >= 0 && t1 < 0))
		return (*t0 = t2);
	return (-1);
}

double calc(double start, double center)
{
	return ((start - center) * (start - center));
}

int	have_solutions(double d)
{
	if (d > 0)
		return (2);
	else if (d == 0)
		return (1);
	else
		return (0);
}


// double				plane_intersection2(t_ray ray, t_plane plane, float *t0)
// {
// 	double	t =  ft_normal3_dot_multiply_vec3(plane.normal, ft_vec3_substract(plane.point, ray.orig)) / ft_normal3_dot_multiply_vec3(plane.normal, ray.dir);
// 	if (t < 0.3)
// 	{
// 		*t0 = t;
// 		return (TRUE);
// 	}
// 	else
// 		return(FALSE);
// }

double		get_solution(double a, double b, double c, float *t0)
{
	double		d;
	double		tmp1;
	double		tmp2;

	d = b * b - 4.0 * a * c;
	if (have_solutions(d) == 0)
		return (0);
	else if (have_solutions(d) == 1)
		*t0 = - b / (2 * a);
	else
	{
		tmp1 = sqrt(d);
		tmp2 = 1 / (2 * a);
		if (((*t0 = (- b - tmp1) * tmp2)) < 0.003)
			if ((*t0 = ((- b + tmp1) * tmp2)) < 0.003)
				return (0);
	}
		return (1);
}

extern inline float ft_vec3_multiply_cone(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x - a.y * b.y + a.z * b.z);
}

double		sphere_intersection(void *figure, t_ray *ray, float *t0)
{
	double t;
	t_sphere *sphere = (t_sphere *) ((t_object *)figure)->object;
	t_vec3 temp = ft_vec3_substract(ray->orig, sphere->center);
	double a = ft_vec3_dot_multiply(ray->dir, ray->dir);
	double b = ft_vec3_dot_multiply(ft_vec3_scalar_multiply(temp, 2), ray->dir);
	double c = ft_vec3_dot_multiply(temp, temp) - sphere->radius * sphere->radius;
	return (get_solution(a, b, c, t0));
}

double	cone_intersection(void *object, t_ray *ray, float *t0)
{
	t_vec3	x;
	double	a;
	double	b;
	double	c;
	double	d;
	t_cone *cone;
	cone = (t_cone *)((t_object *)object)->object;
	x = ft_vec3_substract(ray->orig, cone->center);
	a = ft_vec3_dot_multiply(ray->dir, cone->v);
	a = ft_vec3_dot_multiply(ray->dir, ray->dir) - (1 + cone->radius * cone->radius) * a * a;
	b = 2.0 * (ft_vec3_dot_multiply(ray->dir, x) - (1 + cone->radius * cone->radius)
		* ft_vec3_dot_multiply(ray->dir, cone->v) * ft_vec3_dot_multiply(x, cone->v));
	c = ft_vec3_dot_multiply(x, cone->v);
	c = ft_vec3_dot_multiply(x, x) - (1 + cone->radius * cone->radius) * c * c;
	return (get_solution(a, b, c, t0));
}

// double		plane_intersection(void *object, t_ray *ray, float *t0) // doesn't work
// {
// 	double tmp;
// 	t_plane *p;

// 	p = (t_plane *)((t_object *)object)->object;
// 	tmp = p->point.x * ray->dir.x + p->point.y * ray->dir.y + p->point.z * ray->dir.z;
// 	if (!tmp)
// 		return (0);
// 	*t0 = -(p->point.x * ray->orig.x +  p->point.y * ray->orig.y +  p->point.z * ray->orig.z +  p->point.w) / tmp;
// 	return ((*t0 >= 0) ? 1 : 0);
// }


extern inline float ft_vec3_multiply_cylinder(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.z * b.z);
}

// double		cylinder_intersection(void *object, t_ray *ray, float *t0)
// {
// 	double a;
// 	double b;
// 	double c;
// 	t_cylinder *cyl;

// 	cyl = (t_cylinder *)((t_object *)object)->object;
// 	t_vec3 temp = ft_vec3_substract(ray->orig, cyl->center);
// 	a =  ft_vec3_multiply_cylinder(ray->dir, ray->dir);
// 	b = ft_vec3_multiply_cylinder(ft_vec3_scalar_multiply(temp, 2), ray->dir);
// 	c = ft_vec3_multiply_cylinder(temp, temp) - cyl->radius * cyl->radius;
// 	return (get_solution(a, b, c, t0));
// }

double		cylinder_intersection(void *object, t_ray *ray, float *t0)
{
	t_vec3	x;
	double	a;
	double	b;
	double	c;
	double	d;
	t_cylinder *cylinder;
	cylinder = (t_cylinder *)((t_object *)object)->object;

	x = ft_vec3_substract(ray->orig, cylinder->center);
	a = ft_vec3_dot_multiply(ray->dir, cylinder->v);
	a = ft_vec3_dot_multiply(ray->dir, ray->dir) - a * a;
	b = 2 * (ft_vec3_dot_multiply(ray->dir, x) - ft_vec3_dot_multiply(ray->dir, cylinder->v)
		* ft_vec3_dot_multiply(x, cylinder->v));
	c = ft_vec3_dot_multiply(x, cylinder->v);
	c = ft_vec3_dot_multiply(x, x) - c * c - cylinder->radius * cylinder->radius;
	return (get_solution(a, b, c, t0));
}

// double		plane_intersection(void *object, t_ray *ray, float *t0)
// {
// 	double	t;
// 	double	a;
// 	double	b;
// 	t_plane *plane;
// 	plane = (t_plane *)((t_object *)object)->object;
// 	a = ft_vec3_dot_multiply(ft_vec3_substract(ray->orig, plane->point), plane->normal);
// 	b = ft_vec3_dot_multiply(ray->dir, plane->normal);
// 	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
// 		return (0);
// 	*t0 = -a / b;
// 	//*t0 = ;
// 	return (*t0 > 0 ? *t0 : -1);
// }

double		plane_intersection(void *object, t_ray *ray, float *t0)
{
	double	t;
	double	a;
	double	b;
	t_plane *plane;
	plane = (t_plane *)((t_object *)object)->object;
	a = ft_vec3_dot_multiply(ft_vec3_substract(ray->orig, plane->point), plane->normal);
	b = ft_vec3_dot_multiply(ray->dir, plane->normal);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (0);
	*t0 = -a / b;
	//*t0 = ;
	return (1);
}

// 