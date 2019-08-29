/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 08:30:07 by olesgedz          #+#    #+#             */
/*   Updated: 2019/08/28 22:00:13 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"


cl_float3 cl_scalar_mul(cl_float3 vector, double scalar)
{
	return (create_cfloat3 (vector.v4[0] * scalar,\
	vector.v4[1] * scalar,\
	vector.v4[2] * scalar));
}

cl_float3 cl_add(cl_float3 v1, cl_float3 v2)
{
	return (create_cfloat3 (v1.v4[0] + v2.v4[0],\
	v1.v4[1] + v2.v4[1],\
	v1.v4[2] + v2.v4[2]));
}

void 				camera_move
					(t_camera *camera,
					t_camera_direction direction,
					float length)
{
	cl_float3		step;

	if (direction == left)
		step = cl_scalar_mul(camera->axis_x, -1.f);
	else if (direction == right)
		step = cl_scalar_mul(camera->axis_x, 1.f);
	else if (direction == up)
		step = cl_scalar_mul(camera->axis_y, 1.f);
	else if (direction == down)
		step = cl_scalar_mul(camera->axis_y, -1.f);
	else if (direction == forward)
		step = cl_scalar_mul(camera->axis_z, -1.f);
	else if (direction == backward)
		step = cl_scalar_mul(camera->axis_z, 1.f);
	else
		return ;
	step = cl_scalar_mul(step, length);
	camera->position = cl_add(camera->position, step);
}