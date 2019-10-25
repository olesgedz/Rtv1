/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:04:28 by lminta            #+#    #+#             */
/*   Updated: 2019/10/25 22:23:05 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	set_keys(t_game *game)
{
	game->keys.q = 0;
	game->keys.w = 0;
	game->keys.e = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.z = 0;
	game->keys.x = 0;
	game->keys.r = 0;
	game->keys.lmb = 0;
	game->keys.mm = 0;
	game->keys.space = 0;
}

void		set_const(t_game *game, t_gui *gui)
{
	int		img_flag;

	img_flag = IMG_INIT_JPG;
	if (!(game->image = ft_surface_create(WIN_W, WIN_H)))
		exit(-1);
	game->init_render = 1;
	game->origin = (t_vec3){0, 0, 5};
	game->gpu.samples = 0;
	game->quit = 0;
	game->flag = 1;
	gui->over_gui = 0;
	gui->flag = 0;
	gui->sdl = game->sdl;
	gui->quit = 0;
	set_keys(game);
}
