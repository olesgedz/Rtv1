/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   object_push.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 21:03:09 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/10 21:07:08 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "errno.h"

void		ft_object_push(t_game *game, t_obj *object)
{
	if (game->gpu.objects == NULL)
		game->obj_quantity = 0;
	game->gpu.objects = realloc(game->gpu.objects,
	sizeof(t_obj) * (game->obj_quantity + 1));
	game->gpu.objects[game->obj_quantity] = *object;
	game->obj_quantity += 1;
	free(object);
}

void		ft_cam_push(t_game *game, t_cam *cam)
{
	if (game->gpu.camera == NULL)
		game->cam_quantity = 0;
	game->gpu.camera = realloc(game->gpu.camera,
	sizeof(t_obj) * (game->cam_quantity + 1));
	cam->id = game->cam_quantity;
	game->gpu.camera[game->cam_quantity] = *cam;
	game->cam_quantity += 1;
	free(cam);
}

void		ft_texture_push(t_game *game, char ***mass, char *texture_name)
{
	if (texture_name == NULL)
		return ;
	if (*mass == NULL)
		game->textures_num = 0;
	*mass = realloc(*mass,
	sizeof(char*) * (game->textures_num + 1));
	mass[0][game->textures_num] = ft_strdup(texture_name);
	game->textures_num += 1;
}

void		ft_normal_push(t_game *game, char ***mass, char *normal_name)
{
	if (normal_name == NULL)
		return ;
	if (*mass == NULL)
		game->normals_num = 0;
	*mass = realloc(*mass,
	sizeof(char*) * (game->normals_num + 1));
	mass[0][game->normals_num] = ft_strdup(normal_name);
	game->normals_num += 1;
}
