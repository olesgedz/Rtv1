/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:51:09 by lminta            #+#    #+#             */
/*   Updated: 2019/10/23 21:54:01 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "errno.h"

cl_ulong	*get_random(cl_ulong *random)
{
	int i;

	i = -1;
	if (!(random = ft_memalloc(sizeof(cl_ulong) * (int)WIN_H * (int)WIN_W)))
		ft_exit(0);
	srand(21);
	while (++i < WIN_H * WIN_W)
	{
		random[i] = rand();
	}
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
	object->is_visible = 1;
	game->gpu.objects = ft_realloc(game->gpu.objects,
	sizeof(t_obj) * (game->obj_quantity + 1));
	game->gpu.objects[game->obj_quantity] = *object;
	game->obj_quantity += 1;
	free(object);
}

void		ft_cam_push(t_game *game, t_cam *cam)
{
	if (game->gpu.camera == NULL)
		game->cam_quantity = 0;
	game->gpu.camera = ft_realloc(game->gpu.camera,
	sizeof(t_obj) * (game->cam_quantity + 1));
	game->gpu.camera[game->cam_quantity] = *cam;
	game->cam_quantity += 1;
	free(cam);
}
