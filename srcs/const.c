/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   const.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 20:04:28 by lminta            #+#    #+#             */
/*   Updated: 2019/12/10 16:00:31 by lminta           ###   ########.fr       */
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
	game->normal_list = NULL;
	game->normals_num = 0;
	game->keys.q = 0;
	game->keys.ed_box = 0;
	game->keys.w = 0;
	game->keys.e = 0;
	game->keys.a = 0;
	game->keys.s = 0;
	game->keys.d = 0;
	game->keys.z = 0;
	game->keys.x = 0;
	game->keys.r = 0;
	game->mouse.rmb = 0;
	game->mouse.lmb = 0;
	game->mouse.mm = 0;
	game->keys.space = 0;
	game->keys.show_gui = 1;
	game->server = 0;
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
	if (SDLNet_Init() == -1)
	{
		print_error_gui("SDLNet_Init: %s\n", SDLNet_GetError());
		exit(2);
	}
	game->gpu.samples = 0;
	game->quit = 0;
	game->gui_mod = 0;
	game->flag = 1;
	gui->over_gui = 0;
	gui->flag = 0;
	gui->sdl = game->sdl;
	gui->quit = 0;
	gui->fps = 0;
	gui->to_destroy = 0;
	gui->n.clients = 0;
	gui->n.str_ip = 0;
	game->mouse.x = 0;
	game->mouse.y = 0;
	game->mouse.g = 0;
	game->textures = NULL;
	game->normals = NULL;
	game->texture_list = NULL;
	game->textures_num = 0;
	game->samples_to_do = 0;
	game->vertices_list = NULL;
	game->vertices_num = 0;
	set_keys(game);
}
