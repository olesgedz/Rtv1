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

double		plane_intersection(void *object, t_ray *ray, float *t0)
{
	// double tmp;
	// t_plane *p;

	// p = (t_plane *)((t_object *)object)->object;
	// tmp = p->point.x * ray->dir.x + p->point.y * ray->dir.y + p->point.z * ray->dir.z;
	// if (!tmp)
	// 	return (0);
	// *t0 = -(p->point.x * ray->orig.x +  p->point.y * ray->orig.y +  p->point.z * ray->orig.z +  p->point.w) / tmp;
	// return ((*t0 >= 0.0003) ? 1 : 0);
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
// 	return (1);
// }