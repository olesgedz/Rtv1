/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_cam.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 20:32:27 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/12 17:20:46 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	fill_camera(t_cam *camera, t_json parse)
{
	camera->position = parse_vec3(parse.position, 0);
	if (isnan(camera->position.v4[0]))
		terminate("missing data of cam start pos vector!\n");
	camera->direction = normalize(parse_vec3(parse.v, 0));
	if (isnan(camera->direction.v4[0]))
		terminate("missing data of cam dir vector!\n");
	if (parse.normal != NULL)
	{
		camera->normal = parse_vec3(parse.normal, 0);
		if (isnan(camera->normal.v4[0]))
			terminate("missing data of cam normal vector!\n");
	}
	else
		camera->normal = create_cfloat3(0.0, 1.0, 0.0);
	if (parse.fov != NULL)
		camera->fov = parse.fov->valuedouble * M_PI / 180;
	else
		camera->fov = M_PI / 3;
}

void		check_cam(t_json parse, t_game *game, t_filter *filter)
{
	t_cam *camera;

	camera = (t_cam*)malloc(sizeof(t_cam));
	parse.position = cJSON_GetObjectItemCaseSensitive(parse.camera, "position");
	parse.v = cJSON_GetObjectItemCaseSensitive(parse.camera, "dir");
	parse.normal = cJSON_GetObjectItemCaseSensitive(parse.camera, "normal");
	parse.fov = cJSON_GetObjectItemCaseSensitive(parse.camera, "fov");
	fill_camera(camera, parse);
	camera->ambience = filter->ambiance;
	camera->cartoon = filter->cartoon;
	camera->sepia = filter->sepia;
	camera->motion_blur = filter->motion_blur;
	camera->stereo = filter->stereo;
	game->mask = create_blur_mask(10.f, &camera->mask_size);
	reconfigure_camera(camera);
	ft_cam_push(game, camera);
}
