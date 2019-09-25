/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:10:38 by lminta            #+#    #+#             */
/*   Updated: 2019/09/25 18:48:45 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	mouse(t_game *game)
{
	static int	x = 0;
	static int	y = 0;
	t_gui		*gui;

	gui = g_gui(0, 0);
	if (game->ev.type == SDL_MOUSEBUTTONDOWN)
	{
		if (!gui->over_gui)
		{
			game->keys.lmb = 1;
			SDL_GetMouseState(&x, &y);
			SDL_ShowCursor(SDL_DISABLE);
		}
	}
	else if (game->ev.type == SDL_MOUSEBUTTONUP)
	{
		game->keys.lmb = 0;
		if (!gui->over_gui)
			SDL_ShowCursor(SDL_ENABLE);
	}
	else if (game->ev.type == SDL_MOUSEMOTION)
	{
		pos_check(gui);
		game->keys.xrel = -game->ev.motion.xrel;
		game->keys.yrel = -game->ev.motion.yrel;
		if (game->keys.lmb && !gui->over_gui)
			SDL_WarpMouseInWindow(game->sdl.window, x, y);
		game->keys.mm = 1;
	}
}

static void	key_switch(t_game *game)
{
	if (game->ev.key.keysym.sym == SDLK_COMMA)
	{
		game->gpu.samples = 0;
		game->cam_num--;
		if (game->cam_num < 0)
			game->cam_num = game->cam_quantity - 1;
		game->flag = 1;
	}
	else if (game->ev.key.keysym.sym == SDLK_PERIOD)
	{
		game->gpu.samples = 0;
		game->cam_num++;
		if (game->cam_num >= game->cam_quantity)
			game->cam_num = 0;
		game->flag = 1;
	}
}

static void	key_down(t_game *game)
{
	if (game->ev.key.keysym.sym == SDLK_q)
		game->keys.q = 1;
	else if (game->ev.key.keysym.sym == SDLK_w)
		game->keys.w = 1;
	else if (game->ev.key.keysym.sym == SDLK_e)
		game->keys.e = 1;
	else if (game->ev.key.keysym.sym == SDLK_a)
		game->keys.a = 1;
	else if (game->ev.key.keysym.sym == SDLK_s)
		game->keys.s = 1;
	else if (game->ev.key.keysym.sym == SDLK_d)
		game->keys.d = 1;
	else if (game->ev.key.keysym.sym == SDLK_z)
		game->keys.z = 1;
	else if (game->ev.key.keysym.sym == SDLK_x)
		game->keys.x = 1;
	else if (game->ev.key.keysym.sym == SDLK_SPACE)
		game->keys.space = 1;
	else
		key_switch(game);
}

static void	key_up(t_game *game)
{
	if (game->ev.key.keysym.sym == SDLK_q)
		game->keys.q = 0;
	else if (game->ev.key.keysym.sym == SDLK_w)
		game->keys.w = 0;
	else if (game->ev.key.keysym.sym == SDLK_e)
		game->keys.e = 0;
	else if (game->ev.key.keysym.sym == SDLK_a)
		game->keys.a = 0;
	else if (game->ev.key.keysym.sym == SDLK_s)
		game->keys.s = 0;
	else if (game->ev.key.keysym.sym == SDLK_d)
		game->keys.d = 0;
	else if (game->ev.key.keysym.sym == SDLK_z)
		game->keys.z = 0;
	else if (game->ev.key.keysym.sym == SDLK_x)
		game->keys.x = 0;
	else if (game->ev.key.keysym.sym == SDLK_SPACE)
		game->keys.space = 0;
}

void		key_check(t_game *game)
{
	game->keys.mm = 0;
	while (SDL_PollEvent(&(game->ev)))
	{
		if (game->ev.type == SDL_QUIT ||
		(game->ev.type == SDL_KEYDOWN &&
		game->ev.key.keysym.sym == SDLK_ESCAPE))
			game->quit = 1;
		else if (game->ev.type == SDL_KEYDOWN)
			key_down(game);
		else if (game->ev.type == SDL_KEYUP)
			key_up(game);
		else
			mouse(game);
	}
}
