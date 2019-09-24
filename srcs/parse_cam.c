/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:52:15 by lminta            #+#    #+#             */
/*   Updated: 2019/09/24 17:00:42 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	reconfigure_camera(t_cam *camera)
{
	float		x_fov;
	float		y_fov;

	x_fov = (float)WIN_W / (float)WIN_H > 1 ? camera->fov / 2 :
	camera->fov / 2 * (float)WIN_W / (float)WIN_H;
	y_fov = (float)WIN_H / (float)WIN_W > 1 ? (camera->fov / 2) :
	(camera->fov / 2) * ((float)WIN_H / (float)WIN_W);
	camera->border_y = vector_diff(
	rotate(camera->normal, camera->direction, x_fov),
	rotate(camera->normal, camera->direction, -x_fov));
	camera->border_x = vector_diff(
	rotate(cross(camera->direction, camera->normal), camera->direction, y_fov),
	rotate(cross(camera->direction, camera->normal),
	camera->direction, -y_fov));
}

t_cam	*add_cam(cl_float3 position, cl_float3 direction, cl_float3 normal)
{
	t_cam		*camera;

	camera = (t_cam*)malloc(sizeof(t_cam));
	camera->normal = normal;
	camera->direction = direction;
	camera->position = position;
	camera->fov = M_PI / 3;
	reconfigure_camera(camera);
	return (camera);
}

void	parse_cam(char **data, t_game *game)
{
	char		**vec;
	cl_float3	position;
	cl_float3	v;
	cl_float3	normal;

	if (data[1] == NULL || data[2] == NULL || data[3] == NULL)
		terminate("missing data of cam: not enough arguments!\n");
	vec = ft_strsplit(data[1], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cam pos vector!\n");
	position = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[2], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cam dir vector!\n");
	v = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[3], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cam norm vector!\n");
	normal = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	ft_cam_push(game, add_cam(position, v, normal));
}
