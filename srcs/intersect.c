/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:17:28 by jblack-b          #+#    #+#             */
/*   Updated: 2019/06/09 20:49:34 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
*	Fucntion: checks if a ray hits the sphere
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/

int		sphere_intersection(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	double a;
	double b;
	double c;
	t_sphere *s;

	s = (t_sphere *)sphere;
	t_vec3 temp = ft_vec3_substract(*orig, s->center);
	a = 1;
	b = ft_vec3_dot_multiply(ft_vec3_scalar_multiply(temp, 2), *dir);
	c = ft_vec3_dot_multiply(temp, temp) - s->radius * s->radius;
	return (get_solution(a, b, c, t0));
}

extern inline float ft_vec3_multiply_cone(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x - a.y * b.y + a.z * b.z);
}

int		cone_intersection(void *vcone, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	double a;
	double b;
	double c;
	t_cone *cone;

	cone = (t_cone *)vcone;
	t_vec3 temp = ft_vec3_substract(*orig, cone->center);
	a = ft_vec3_multiply_cone(*dir, *dir);
	b = ft_vec3_multiply_cone(ft_vec3_scalar_multiply(temp, 2), *dir);
	c = ft_vec3_multiply_cone(temp, temp);
	return (get_solution(a, b, c, t0));
}

int		plane_intersection(void *plane, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	double tmp;
	t_plane *p;

	p = (t_plane *)plane;
	tmp = p->point.x * dir->x + p->point.y * dir->y + p->point.z * dir->z;
	if (!tmp)
		return (0);
	*t0 = -(p->point.x * orig->x +  p->point.y * orig->y +  p->point.z * orig->z +  p->point.w) / tmp;
	return ((*t0 >= 0) ? 1 : 0);
}


extern inline float ft_vec3_multiply_cylinder(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.z * b.z);
}

int		cylinder_intersection(void *cylinder, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	double a;
	double b;
	double c;
	t_cylinder *cyl;

	cyl = (t_cylinder *)cylinder;
	t_vec3 temp = ft_vec3_substract(*orig, cyl->center);
	a = 1;
	b = ft_vec3_multiply_cylinder(ft_vec3_scalar_multiply(temp, 2), *dir);
	c = ft_vec3_multiply_cylinder(temp, temp) - cyl->radius * cyl->radius;
	return (get_solution(a, b, c, t0));
}
