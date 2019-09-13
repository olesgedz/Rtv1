/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:21:19 by lminta            #+#    #+#             */
/*   Updated: 2019/09/13 22:52:57 by lminta           ###   ########.fr       */
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
	game->gui.ed_w.winrect = (KW_Rect){0, 0, WIN_W, WIN_H};
	SDL_SetRenderDrawColor(game->sdl.renderer, 100, 100, 200, 1);
	game->gui.driver =
	KW_CreateSDL2RenderDriver(game->sdl.renderer, game->sdl.window);
	game->gui.set = KW_LoadSurface(game->gui.driver, "gui/res/tileset.png");
	game->gui.gui = KW_Init(game->gui.driver, game->gui.set);
}

void	loopa(t_game *game)
{
	while (!SDL_QuitRequested() && !game->quit)
	{
		SDL_RenderClear(game->sdl.renderer);
		KW_ProcessEvents(game->gui.gui);
		KW_Paint(game->gui.gui);
		SDL_RenderPresent(game->sdl.renderer);
	}
}

void	quit_kiwi(t_game *game)
{
	KW_Quit(game->gui.gui);
	KW_ReleaseSurface(game->gui.driver, game->gui.set);
	KW_ReleaseRenderDriver(game->gui.driver);
}
