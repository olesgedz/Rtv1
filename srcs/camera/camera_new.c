/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_new.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 08:34:38 by olesgedz          #+#    #+#             */
/*   Updated: 2019/08/10 08:36:21 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_camera			*camera_new(int width, int height)
{
	t_camera		*new;

	new = (t_camera *)malloc(sizeof(t_camera));
	new->forward =
		(cl_float3){0., 0., -1. *  width / (tan((M_PI / 3.) / 2.))};
	new->axis_x = (cl_float3){1., 0., 0.};
	new->axis_y = (cl_float3){0., 1., 0.};
	new->axis_z = (cl_float3){0., 0., 1.};
	new->position = (cl_float3){0., 0., 0.};
	new->width = width;
	new->height =  height;
	return (new);
}