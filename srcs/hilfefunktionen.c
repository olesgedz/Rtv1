/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hilfefunktionen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:51:09 by lminta            #+#    #+#             */
/*   Updated: 2019/11/26 18:43:53 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "errno.h"

cl_ulong	*get_random(cl_ulong *random)
{
	int i;

	i = -1;
	if (!(random = ft_memalloc(sizeof(cl_ulong) * (int)WIN_H * (int)WIN_W)))
		ft_exit(0);
	srand(time(NULL));
	while (++i < WIN_H * WIN_W)
		random[i] = rand() | (cl_ulong)rand() << 32;
	return (random);
}

void		terminate(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

void		feel_free(char **str)
{
	int i;

	i = -1;
	while (str[++i] != NULL)
		free(str[i]);
	free(str);
}

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

int compare_in_texture_dict(t_game *game, char *texture_name)
{
	int i;

	i = 0;

	if (game->texture_list == NULL)
		return (game->textures_num + 1);
	while (i < game->textures_num)
	{
		if (ft_strcmp(game->texture_list[i], texture_name) == 0)
			return (i + 1);
		i++;
	}
	return (game->textures_num + 1);
}

int compare_in_normal_dict(t_game *game, char *normal_name)
{
	int i;

	i = 0;

	if (game->normal_list == NULL)
		return (game->normals_num + 1);
	while (i < game->normals_num)
	{
		if (ft_strcmp(game->normal_list[i], normal_name) == 0)
			return (i + 1);
		i++;
	}
	return (game->normals_num + 1);
}
