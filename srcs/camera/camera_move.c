/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_move.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 08:30:07 by olesgedz          #+#    #+#             */
/*   Updated: 2019/08/10 08:48:44 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "rtv1.h"

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