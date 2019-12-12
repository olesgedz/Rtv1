/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_float3_rotate.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 13:50:09 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/10 18:10:07 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float2	create_cfloat2(float x, float y)
{
	cl_float2 re;

	re.s[0] = x;
	re.s[1] = y;
	return (re);
}

cl_float3	normalize(cl_float3 vector)
{
	cl_float3	res;
	float		norm;

	norm = sqrt(vector.s[0] * vector.s[0] + vector.s[1] *
	vector.s[1] + vector.s[2] * vector.s[2]);
	res.s[0] = vector.s[0] / norm;
	res.s[1] = vector.s[1] / norm;
	res.s[2] = vector.s[2] / norm;
	return (res);
}

void		rotate_horizontal(t_cam *camera, float angle)
{
	cl_float3	axis;

	axis = create_cfloat3(0.0f, 1.0f, 0.0f);
	camera->direction = normalize(rotate(axis, camera->direction, -angle));
	camera->normal = normalize(rotate(axis, camera->normal, -angle));
}

void		rotate_vertical(t_cam *camera, float angle)
{
	cl_float3	axis;

	axis = cross(camera->direction, camera->normal);
	camera->direction = rotate(axis, camera->direction, angle);
	camera->normal = rotate(axis, camera->normal, angle);
}

cl_float3	rotate(cl_float3 axis, cl_float3 vector, float angle)
{
	cl_float3	res;
	float		sin_a;
	float		cos_a;

	sin_a = sin(angle);
	cos_a = cos(angle);
	res.s[0] = (cos_a + (1 - cos_a) * axis.s[0] * axis.s[0]) * vector.s[0] +
	((1 - cos_a) * axis.s[0] * axis.s[1] - sin_a * axis.s[2]) * vector.s[1] +
	((1 - cos_a) * axis.s[0] * axis.s[2] + sin_a * axis.s[1]) * vector.s[2];
	res.s[1] = ((1 - cos_a) * axis.s[1] * axis.s[0] + sin_a * axis.s[2]) *
	vector.s[0] + (cos_a + (1 - cos_a) * axis.s[1] * axis.s[1]) * vector.s[1] +
	((1 - cos_a) * axis.s[2] * axis.s[1] - sin_a * axis.s[0]) * vector.s[2];
	res.s[2] = ((1 - cos_a) * axis.s[2] * axis.s[0] - sin_a * axis.s[1]) *
	vector.s[0] +
	((1 - cos_a) * axis.s[2] * axis.s[1] + sin_a * axis.s[0]) * vector.s[1] +
	(cos_a + (1 - cos_a) * axis.s[2] * axis.s[2]) * vector.s[2];
	return (res);
}
