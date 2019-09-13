/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:21:19 by lminta            #+#    #+#             */
/*   Updated: 2019/09/13 22:46:25 by lminta           ###   ########.fr       */
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

void	ok_clicked(KW_Widget *widget, int b)
{
	t_game	*game;

	game = g_game(0, 0);
	game->av = (char *)KW_GetEditboxText(game->gui.ed_w.editBox);
	game->quit = KW_TRUE;
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

void	start_screen(t_game *game)
{
	init_kiwi(game);
	game->gui.ed_w.framerect = (KW_Rect){10, 10, 300, 220};
	KW_RectCenterInParent(&game->gui.ed_w.winrect, &game->gui.ed_w.framerect);
	game->gui.ed_w.frame =
	KW_CreateFrame(game->gui.gui, NULL, &game->gui.ed_w.framerect);
	game->gui.ed_w.titlerect = (KW_Rect){0, 10, 300, 30};
	game->gui.ed_w.labelrect = (KW_Rect){0, 100, 60, 30};
	game->gui.ed_w.editboxrect = (KW_Rect){0, 100, 100, 40};
	game->gui.ed_w.rects[0] = &game->gui.ed_w.labelrect;
	game->gui.ed_w.rects[1] = &game->gui.ed_w.editboxrect;
	game->gui.ed_w.weights[0] = 1;
	game->gui.ed_w.weights[1] = 4;
	KW_RectFillParentHorizontally(&game->gui.ed_w.framerect,
	game->gui.ed_w.rects, game->gui.ed_w.weights, 2, 10, KW_RECT_ALIGN_MIDDLE);
	KW_CreateLabel(game->gui.gui, game->gui.ed_w.frame,
	"Enter the path to the scene", &game->gui.ed_w.titlerect);
	KW_CreateLabel(game->gui.gui, game->gui.ed_w.frame,
	"Path", &game->gui.ed_w.labelrect);
	game->gui.ed_w.editBox = KW_CreateEditbox(game->gui.gui,
	game->gui.ed_w.frame, "Edit me!", &game->gui.ed_w.editboxrect);
	game->gui.ed_w.buttonrect = (KW_Rect){250, 170, 40, 40};
	game->gui.ed_w.okbutton = KW_CreateButtonAndLabel(game->gui.gui,
	game->gui.ed_w.frame, "OK", &game->gui.ed_w.buttonrect);
	KW_AddWidgetMouseDownHandler(game->gui.ed_w.okbutton, ok_clicked);
	loopa(game);
}

void	quit_kiwi(t_game *game)
{
	KW_Quit(game->gui.gui);
	KW_ReleaseSurface(game->gui.driver, game->gui.set);
	KW_ReleaseRenderDriver(game->gui.driver);
}
