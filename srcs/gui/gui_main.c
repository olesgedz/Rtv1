/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:21:19 by lminta            #+#    #+#             */
/*   Updated: 2019/12/10 22:47:00 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

t_gui		*g_gui(t_gui *gui, int flag)
{
	static t_gui	*storage = 0;

	if (flag)
		storage = gui;
	return (storage);
}

static void	rotator(t_game *game, t_gui *gui)
{
	static float angle = 0;

	if (angle < M_PI / 2.)
	{
		angle += M_PI / 1200.;
		game->gpu.camera[game->cam_num].direction =
		rotate(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction, M_PI / 1200.);
		game->flag = 1;
		game->cl_info->ret =
		cl_write(game->cl_info, game->cl_info->progs[0].krls->args[2],
		sizeof(cl_float3) * (unsigned)WIN_H * (unsigned)WIN_W,\
		game->gpu.vec_temp);
		cl_write(game->cl_info, game->cl_info->progs[0].krls->args[11],
		sizeof(cl_float3) * (unsigned)WIN_H * (unsigned)WIN_W,\
		game->gpu.vec_temp1);
		game->gpu.samples = 0;
		reconfigure_camera(&game->gpu.camera[game->cam_num]);
	}
}

void		loopa(t_game *game, t_gui *gui)
{
	Uint32		time;

	SDL_RenderClear(gui->sdl.renderer);
	while (!gui->quit)
	{
		time = SDL_GetTicks();
		rotator(game, gui);
		if (SDL_PollEvent(&gui->ev))
			if (gui->ev.type == SDL_QUIT ||
		(gui->ev.type == SDL_KEYDOWN &&
		gui->ev.key.keysym.sym == SDLK_ESCAPE))
				gui->quit = 1;
		ft_render(game, gui);
		screen_present(game, gui);
		time = SDL_GetTicks() - time;
		if (time < TICKS_PER_FRAME)
			SDL_Delay(TICKS_PER_FRAME - time);
	}
}
