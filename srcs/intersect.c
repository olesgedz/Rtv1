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

double calc(double start, double center)
{
	return ((start - center) * (start - center));
}

double		sphere_intersection(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
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

double		cone_intersection(t_cone *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	double a;
	double b;
	double c;
	t_cone *s;
	t_vec3 temp = ft_vec3_substract(*orig, sphere->center);
	a = ft_vec3_multiply_cone(*dir, *dir);
	b = ft_vec3_multiply_cone(ft_vec3_scalar_multiply(temp, 2), *dir);
	c = ft_vec3_multiply_cone(temp, temp);
	return (get_solution(a, b, c, t0));
}

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
