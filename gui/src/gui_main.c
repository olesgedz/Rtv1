/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:21:19 by lminta            #+#    #+#             */
/*   Updated: 2019/09/24 21:42:37 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_gui	*g_gui(t_gui *gui, int flag)
{
	static t_gui	*storage = 0;

	if (flag)
		storage = gui;
	return (storage);
}

void	init_kiwi(t_gui *gui)
{
	g_gui(gui, 1);
	gui->ed_w.backtex = load_picture(gui, "gui/res/start.bmp");
	gui->ed_w.winrect = (KW_Rect){0, 0, WIN_W, WIN_H};
	gui->driver =
	KW_CreateSDL2RenderDriver(gui->sdl.renderer, gui->sdl.window);
	gui->set = KW_LoadSurface(gui->driver, "gui/res/tileset.png");
	gui->gui = KW_Init(gui->driver, gui->set);
}

void	loopa(t_gui *gui)
{
	SDL_RenderClear(gui->sdl.renderer);
	while (!gui->quit)
	{
		if (SDL_PollEvent(&gui->ev))
			if (gui->ev.type == SDL_QUIT ||
		(gui->ev.type == SDL_KEYDOWN &&
		gui->ev.key.keysym.sym == SDLK_ESCAPE))
				gui->quit = 1;
		SDL_RenderCopy(gui->sdl.renderer, gui->ed_w.backtex, 0, 0);
		KW_ProcessEvents(gui->gui);
		KW_Paint(gui->gui);
		SDL_RenderPresent(gui->sdl.renderer);
	}
}

void	quit_kiwi(t_gui *gui)
{
	SDL_DestroyTexture(gui->ed_w.backtex);
	KW_DestroyWidget(gui->ed_w.frame, 1);
	KW_DestroyWidget(gui->s_s.frame, 1);
	KW_ReleaseSurface(gui->driver, gui->set);
	//KW_ReleaseRenderDriver(gui->driver);
	KW_Quit(gui->gui);
}
