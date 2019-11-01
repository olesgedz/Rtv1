/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:04:28 by lminta            #+#    #+#             */
/*   Updated: 2019/11/01 18:59:08 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	set_keys(t_game *game)
{
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		print_error_gui("Could not initialize mixer ", Mix_GetError());
		exit(1);
	}
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
	game->keys.show_gui = 1;
	game->textures = 0;
	game->normals = 0;
}

void		set_const(t_game *game, t_gui *gui)
{
	int		img_flag;

	img_flag = IMG_INIT_JPG;
	if (!(IMG_Init(img_flag) & img_flag))
	{
		print_error_gui("No IMG for you: ", IMG_GetError());
		exit(1);
	}
	// img_flag = MIX_INIT_MP3;
	// if (img_flag != Mix_Init(img_flag))
	// {
	// 	print_error_gui("Could not initialize mixer ", Mix_GetError());
	// 	exit(1);
	// }
	if (!(game->image = ft_surface_create(WIN_W, WIN_H)))
		exit(-1);
	game->init_render = 1;
	game->gpu.samples = 0;
	game->quit = 0;
	game->flag = 1;
	gui->over_gui = 0;
	gui->flag = 0;
	gui->sdl = game->sdl;
	gui->quit = 0;
	set_keys(game);
}
