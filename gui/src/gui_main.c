/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:21:19 by lminta            #+#    #+#             */
/*   Updated: 2019/09/20 21:19:54 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_game	*g_game(t_game *game, int flag)
{
	static t_game	*storage = 0;

	if (flag)
		storage = game;
	return (storage);
}

void	init_kiwi(t_game *game)
{
	g_game(game, 1);
	game->gui.ed_w.backtex = load_picture(game, "gui/res/start.bmp");
	game->gui.ed_w.winrect = (KW_Rect){0, 0, WIN_W, WIN_H};
	game->gui.driver =
	KW_CreateSDL2RenderDriver(game->sdl.renderer, game->sdl.window);
	game->gui.set = KW_LoadSurface(game->gui.driver, "gui/res/tileset.png");
	game->gui.gui = KW_Init(game->gui.driver, game->gui.set);
}

void	loopa(t_game *game)
{
	while (!game->quit)
	{
		if (SDL_PollEvent(&game->ev))
			if (game->ev.type == SDL_QUIT ||
		(game->ev.type == SDL_KEYDOWN &&
		game->ev.key.keysym.sym == SDLK_ESCAPE))
			game->quit = 1;
		SDL_RenderClear(game->sdl.renderer);
		SDL_RenderCopy(game->sdl.renderer, game->gui.ed_w.backtex, 0, 0);
		KW_ProcessEvents(game->gui.gui);
		KW_Paint(game->gui.gui);
		SDL_RenderPresent(game->sdl.renderer);
	}
}

void	quit_kiwi(t_game *game)
{
	SDL_DestroyTexture(game->gui.ed_w.backtex);
	KW_DestroyWidget(game->gui.ed_w.frame, 1);
	KW_DestroyWidget(game->gui.s_s.frame, 1);
	KW_ReleaseSurface(game->gui.driver, game->gui.set);
	//KW_ReleaseRenderDriver(game->gui.driver);
	KW_Quit(game->gui.gui);
}
