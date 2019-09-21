/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:04:28 by lminta            #+#    #+#             */
/*   Updated: 2019/09/20 20:46:56 by sbrella          ###   ########.fr       */
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
	game->keys.lmb = 0;
	game->keys.mm = 0;
	game->keys.space = 0;
}

void		set_const(t_game *game)
{
	int		img_flag;

	img_flag = IMG_INIT_JPG;
	if (!(game->image = ft_surface_create(WIN_W, WIN_H)))
		exit(-1);
	game->init_render = 1;
	game->origin = (t_vec3){0,0,5};
	game->gpu.samples = 0;
	game->quit = 0;
	game->flag = 1;
	set_keys(game);
	ft_init_window(&game->sdl, WIN_W, WIN_H);
	if (!(IMG_Init(img_flag) & img_flag))
		exit(0);
	init_kiwi(game);
}
