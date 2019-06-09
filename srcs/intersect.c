/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:17:28 by jblack-b          #+#    #+#             */
/*   Updated: 2019/06/09 20:46:57 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


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
	if (t1 < 0)
		t1 = t2;
	if (t1 < 0)
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


/*
*	Fucntion: checks if a ray hits the sphere
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/
int ray_intersect(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	t_vec3 L = ft_vec3_substract(sphere->center, *orig);
	// printf("%f %f %f, dir: %f %f %f\n", L.x, L.y, L.z, dir->x, dir->y, dir->z);
	float tca = ft_vec3_dot_multiply(L, *dir);
	//printf("tca %f\n", tca);
	float d2 = ft_vec3_dot_multiply(L, L) - tca * tca;
	//printf("d2 %f %f \n", d2, sphere->radius * sphere->radius);
	if (d2 > sphere->radius * sphere->radius)
		return FALSE;
	float thc = sqrtf(sphere->radius * sphere->radius - d2);
	*t0	= tca - thc;
	float t1 = tca + thc;
	if (*t0 < 0)
		*t0 = t1;
	if (*t0 < 0)
		return FALSE;
	return TRUE;
}

double		ray_intersect_sphere(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	float	a;
	float	b;
	float	c;
	float	d;

	a = ft_vec3_dot_multiply(*dir, *dir);
	b = 2 * ft_vec3_dot_multiply(*dir, ft_vec3_substract(*orig, sphere->center));
	c = ft_vec3_dot_multiply(ft_vec3_substract(*orig, sphere->center),
		ft_vec3_substract(*orig, sphere->center)) - sphere->radius * sphere->radius;
	d = b * b - 4 * a * c;
	*t0 = d < 0 ? -1 : quandratic_solve(a, b, c);
	return (d < 0 ? -1 : quandratic_solve(a, b, c));
}


double				sphere_intersection3(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	t_vec3		oc;
	double			k1;
	double			k2;
	double			k3;

	oc = ft_vec3_substract(*orig, sphere->center);
	k1 = ft_vec3_dot_multiply(*dir, *dir);
	k2 = 2 * ft_vec3_dot_multiply(oc, *dir);
	k3 = ft_vec3_dot_multiply(oc, oc) - sphere->radius * sphere->radius;
	*t0 = quandratic_solve(k1, k2, k3);
	return(*t0 < 0.003 ? 0 : 1);
}

double				cylinder_intersection(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	double			k1;
	double			k2;
	double			k3;

	k1 = ft_vec3_dot_multiply(ft_vec3_cross_multiply(*dir, sphere->v),
			ft_vec3_cross_multiply(*dir, sphere->v));
	k2 = 2 * ft_vec3_dot_multiply(ft_vec3_cross_multiply(*dir, sphere->v),
			ft_vec3_cross_multiply(ft_vec3_substract(*orig, sphere->center),
				sphere->v));
	k3 = ft_vec3_dot_multiply(ft_vec3_cross_multiply(ft_vec3_substract(*orig, sphere->center),
				sphere->v),
			ft_vec3_cross_multiply(ft_vec3_substract(*orig, sphere->center),
				sphere->v)) - sphere->radius * sphere->radius;
	*t0 = quandratic_solve(k1, k2, k3);
	return(*t0 < 0.003 ? 0 : 1);
}

double				cone_intersection(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	t_vec3		co;
	double			k1;
	double			k2;
	double			k3;

	co = ft_vec3_substract(*orig, sphere->tip);
	k1 = ft_vec3_dot_multiply(*dir, sphere->v) *
		ft_vec3_dot_multiply(*dir, sphere->v) - cos(sphere->angle)
		* cos(sphere->angle);
	k2 = 2 * (ft_vec3_dot_multiply(*dir, sphere->v) *
			ft_vec3_dot_multiply(co, sphere->v)
			- ft_vec3_dot_multiply(*dir, co) * cos(sphere->angle)
			* cos(sphere->angle));
	k3 = ft_vec3_dot_multiply(co, sphere->v) * ft_vec3_dot_multiply(co, sphere->v)
		- ft_vec3_dot_multiply(co, co)
		* cos(sphere->angle) * cos(sphere->angle);
	*t0 = quandratic_solve(k1, k2, k3);
	return(*t0 < 0.003 ? 0 : 1);
}


double		ray_intersect_cylinder(t_sphere *cylinder, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	t_vec3	x;
	double	a;
	double	b;
	double	c;
	double	d;
	
	x = ft_vec3_substract(*orig, cylinder->center);
	a = ft_vec3_dot_multiply(*dir, cylinder->v);
	a = ft_vec3_dot_multiply(*dir, *dir) - a * a;
	b = 2 * (ft_vec3_dot_multiply(*dir, x) - ft_vec3_dot_multiply(*dir, cylinder->v)
		* ft_vec3_dot_multiply(x, cylinder->v));
	c = ft_vec3_dot_multiply(x, cylinder->v);
	c = ft_vec3_dot_multiply(x, x) - c * c - cylinder->radius * cylinder->radius;
	d = b * b - 4 * a * c;
	d = DROUND(d);
	return (d = d < 0 ? -1 : get_t(a, b, d, t0));
}



double		ray_intersect_cone(t_sphere *cone, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	t_vec3	x;
	double	a;
	double	b;
	double	c;
	double	d;

	x = ft_vec3_substract(*orig, cone->center);
	a = ft_vec3_dot_multiply(*dir, cone->v);
	a = ft_vec3_dot_multiply(*dir, *dir) - (1 + cone->radius * cone->radius) * a * a;
	b =  2 * (ft_vec3_dot_multiply(*dir, x) - (1 + cone->radius * cone->radius)
		* ft_vec3_dot_multiply(*dir, cone->v) * ft_vec3_dot_multiply(x, cone->v));
	c = ft_vec3_dot_multiply(x, cone->v);
	c = ft_vec3_dot_multiply(x, x) - (1 + cone->radius * cone->radius) * c * c;
	d = b * b - 4 * a * c;
	d = DROUND(d);
	return (d = d < 0 ? -1 : get_t(a, b, d, t0));
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

double		ray_intersect_sphere_book(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	double t;
	t_vec3 temp = ft_vec3_substract(*orig, sphere->center);
	double a = ft_vec3_dot_multiply(*dir, *dir);
	double b = ft_vec3_dot_multiply(ft_vec3_scalar_multiply(temp, 2), *dir);
	double c = ft_vec3_dot_multiply(temp, temp) - sphere->radius * sphere->radius;
	double disc = b * b - 4.0 * a * c;
	if(disc < 0)
		return ( 0);
	else
	{
			double e = sqrt(disc);
			double denom = 2 * a;
			t = (-b - e) / denom;
			if (t > 0)
			{
				*t0 = t;
				return (1);
			}
			t = (-b + e)/denom;

			if (t > 0)
			{
				*t0 = t;
				return (1);
			}

	}

		return 0;
	

}
extern inline float ft_vec3_dot_multiply1(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x - a.y * b.y + a.z * b.z);
}
double		ray_intersect_cone_book(t_cone *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	double t;
	t_vec3 temp = ft_vec3_substract(*orig, sphere->center);
	double a = ft_vec3_dot_multiply1(*dir, *dir);
	double b = ft_vec3_dot_multiply1(ft_vec3_scalar_multiply(temp, 2), *dir);
	double c = ft_vec3_dot_multiply1(temp, temp);
	double disc = b * b - 4.0 * a * c;
	if(disc < 0)
		return ( 0);
	else
	{
			double e = sqrt(disc);
			double denom = 2 * a;
			t = (-b - e) / denom;
			if (t > 0.005)
			{
				*t0 = t;
				return (1);
			}
			t = (-b + e)/denom;

			if (t > 0.005)
			{
				*t0 = t;
				return (1);
			}

	}

		return 0;
	

}

// double		intersect_plane(t_plane *plane, t_vec3 *orig, t_vec3 *dir, float *t0)
// {
// 	double	t;
// 	double	ddotv;
// 	double	xdotv;
// 	t_vec3	x;

// 	x = ft_vec3_substract(plane.org, s.c);
// 	ddotv = v_dot(r.dir, s.d);
// 	xdotv = v_dot(x, s.d);
// 	if (ddotv != 0)
// 	{
// 		t = -xdotv / ddotv;
// 		if (t > T_MIN && t < T_MAX)
// 			return (t);
// 	}
// 	return (T_MAX);
// }

double				plane_intersection(t_ray ray, t_triangle triangle, float *t0)
{
	double				det;

	det = ft_vec3_dot_multiply(ft_vec3_substract(triangle.a, triangle.b),
			ft_vec3_cross_multiply(ray.dir, ft_vec3_substract(triangle.c, triangle.a)));
	if (det < 1e-8 && det > -1e-8)
		return (0);
	det = ft_vec3_dot_multiply(ft_vec3_substract(triangle.c, triangle.a),
			ft_vec3_cross_multiply(ft_vec3_substract(ray.orig, triangle.a),
				ft_vec3_substract(triangle.a, triangle.b))) * (1 / det);
	return (*t0 = det);
}

double				plane_intersection2(t_ray ray, t_plane plane, float *t0)
{
	double	t =  ft_normal3_dot_multiply_vec3(plane.normal, ft_vec3_substract(plane.point, ray.orig)) / ft_normal3_dot_multiply_vec3(plane.normal, ray.dir);
	if (t < 0.3)
	{
		*t0 = t;
		return (TRUE);
	}
	else
		return(FALSE);
}


/*
*	Fucntion: checks if a ray hits the sphere
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/
// int ray_intersect(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
// {
// 	t_vec3 L = ft_vec3_substract(sphere->center, *orig);
// 	// printf("%f %f %f, dir: %f %f %f\n", L.x, L.y, L.z, dir->x, dir->y, dir->z);
// 	float tca = ft_vec3_dot_multiply(L, *dir);
// 	//printf("tca %f\n", tca);
// 	float d2 = ft_vec3_dot_multiply(L, L) - tca * tca;
// 	//printf("d2 %f %f \n", d2, sphere->radius * sphere->radius);
// 	if (d2 > sphere->radius * sphere->radius)
// 		return FALSE;
// 	float thc = sqrtf(sphere->radius * sphere->radius - d2);
// 	*t0	= tca - thc;
// 	float t1 = tca + thc;
// 	if (*t0 < 0)
// 		*t0 = t1;
// 	if (*t0 < 0)
// 		return FALSE;
// 	return TRUE;
// }
