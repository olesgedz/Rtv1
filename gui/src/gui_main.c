/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:21:19 by lminta            #+#    #+#             */
/*   Updated: 2019/11/11 14:24:25 by lminta           ###   ########.fr       */
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

static void	in_e(t_gui *gui)
{
	KW_HideWidget(gui->ed_w.frame);
	gui->i_e.frect = gui->ed_w.frect;
	gui->i_e.frect.y += WIN_H / 3;
	gui->i_e.frect.h /= 3;
	gui->i_e.frame = KW_CreateFrame(gui->gui, NULL, &gui->i_e.frect);
	gui->i_e.rects[0] = &gui->i_e.titlerect;
	gui->i_e.weights[0] = 1;
	gui->i_e.titlerect = gui->i_e.frect;
	KW_RectCenterInParent(&gui->i_e.frect, &gui->i_e.titlerect);
	gui->i_e.label = KW_CreateLabel(gui->gui,
	gui->i_e.frame, "V GLAZA MNE SMOTRI", &gui->i_e.titlerect);
	system("say -v Yuri 'В глаза мне смотри'&");
}

void		init_kiwi(t_gui *gui)
{
	int i;

	i = -1;
	g_gui(gui, 1);
	gui->ed_w.winrect = (KW_Rect){0, 0, WIN_W, WIN_H};
	gui->driver =
	KW_CreateSDL2RenderDriver(gui->sdl.renderer, gui->sdl.window);
	gui->set = KW_LoadSurface(gui->driver, "gui/res/tileset.png");
	gui->gui = KW_Init(gui->driver, gui->set);
	while (++i < MAX_OBJ)
	{
		gui->o_s.buttons[i] = 0;
		gui->s_s.buttons[i] = 0;
		gui->o_s.names[i] = 0;
		gui->s_s.names[i] = 0;
		if (i < 30)
			gui->g_b.names[i] = 0;
	}
	gui->ed_w.show = 1;
	gui->s_s.show = 0;
	gui->o_s.show = 0;
	gui->g_b.show = 0;
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
		cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) *
		(unsigned)WIN_H * (unsigned)WIN_W, game->gpu.vec_temp);
		game->gpu.samples = 0;
		reconfigure_camera(&game->gpu.camera[game->cam_num]);
	}
	else if (KW_IsWidgetHidden(gui->ed_w.frame) != KW_TRUE &&
	!ft_strcmp(USER, getlogin()))
		in_e(gui);
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
	if (gui->i_e.frame && KW_IsWidgetHidden(gui->i_e.frame) != KW_TRUE)
		KW_HideWidget(gui->i_e.frame);
}
