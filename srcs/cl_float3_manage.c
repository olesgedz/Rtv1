/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_float3_manage.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/07 17:03:05 by sbrella           #+#    #+#             */
/*   Updated: 2019/09/09 18:29:57 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "rtv1.h"

cl_float3 create_cfloat3 (float x, float y, float z)
{
	cl_float3 re;

	re.v4[0] = x;
	re.v4[1] = y;
	re.v4[2] = z;
	return re;
}

cl_float3		sum_cfloat3(cl_float3 one, cl_float3 two)
{
	cl_float3	res;

	res.s[0] = one.s[0] + two.s[0];
	res.s[1] = one.s[1] + two.s[1];
	res.s[2] = one.s[2] + two.s[2];
	return (res);
}

cl_float3		mult_cfloat3(cl_float3 one, float f)
{
	cl_float3	res;

	res.s[0] = one.s[0] * f;
	res.s[1] = one.s[1] * f;
	res.s[2] = one.s[2] * f;
	return (res);
}

cl_float3		rotate(cl_float3 axis, cl_float3 vector, float angle)
{
	cl_float3	res;
	float		sin_a;
	float		cos_a;

	sin_a = sin(angle);
	cos_a = cos(angle);
	res.s[0] = (cos_a + (1 - cos_a) * axis.s[0] * axis.s[0]) * vector.s[0] +
	((1 - cos_a) * axis.s[0] * axis.s[1] - sin_a * axis.s[2]) * vector.s[1] +
	((1 - cos_a) * axis.s[0] * axis.s[2] + sin_a * axis.s[1]) * vector.s[2];
	res.s[1] = ((1 - cos_a) * axis.s[1] * axis.s[0] + sin_a * axis.s[2]) * vector.s[0] +
	(cos_a + (1 - cos_a) * axis.s[1] * axis.s[1]) * vector.s[1] +
	((1 - cos_a) * axis.s[2] * axis.s[1] - sin_a * axis.s[0]) * vector.s[2];
	res.s[2] = ((1 - cos_a) * axis.s[2] * axis.s[0] - sin_a * axis.s[1]) * vector.s[0] +
	((1 - cos_a) * axis.s[2] * axis.s[1] + sin_a * axis.s[0]) * vector.s[1] +
	(cos_a + (1 - cos_a) * axis.s[2] * axis.s[2]) * vector.s[2];
	return (res);
}

cl_float3   	cross(cl_float3 one, cl_float3 two)
{
	cl_float3	ret;

	ret.s[0] = one.s[1] * two.s[2] - one.s[2] * two.s[1];
	ret.s[1] = one.s[2] * two.s[0] - one.s[0] * two.s[2];
	ret.s[2] = one.s[0] * two.s[1] - one.s[1] * two.s[0];
	return (ret);
}

cl_float3		vector_diff(cl_float3 one, cl_float3 two)
{
	cl_float3	res;

	res.s[0] = one.s[0] - two.s[0];
	res.s[1] = one.s[1] - two.s[1];
	res.s[2] = one.s[2] - two.s[2];
	return (res);
}

cl_float3	normalize(cl_float3 vector)
{
	cl_float3	res;
	float		norm;

	norm = sqrt(vector.s[0] * vector.s[0] + vector.s[1] * vector.s[1] + vector.s[2] * vector.s[2]);
	res.s[0] = vector.s[0] / norm;
	res.s[1] = vector.s[1] / norm;
	res.s[2] = vector.s[2] / norm;
	return (res);
}

void			rotate_horizontal(t_cam *camera, float angle)
{
	cl_float3	axis;

	axis = create_cfloat3(0.0f, -1.0f, 0.0f);
	camera->direction = rotate(axis, camera->direction, angle);
	camera->normal = rotate(axis, camera->normal, angle);
}

void			rotate_vertical(t_cam *camera, float angle)
{
	cl_float3	axis;

	axis = cross(camera->direction, camera->normal);
	camera->direction = rotate(axis, camera->direction, angle);
	camera->normal = rotate(axis, camera->normal, angle);
}