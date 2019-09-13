/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_main.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:21:19 by lminta            #+#    #+#             */
/*   Updated: 2019/09/13 18:31:18 by lminta           ###   ########.fr       */
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

KW_bool quit = KW_FALSE;
void OKClicked(KW_Widget * widget, int b)
{
	t_game	*game;

	game = g_game(0, 0);
	game->av = (char *)KW_GetEditboxText(game->gui->editBox);
	game->quit = KW_TRUE;
}

void	init_kiwi(t_game *game)
{
	game->gui->driver =
	KW_CreateSDL2RenderDriver(game->sdl->renderer, game->sdl->window);
	game->gui->set = KW_LoadSurface(game->gui->driver, "gui/res/tileset.png");
	game->gui->gui = KW_Init(game->gui->driver, game->gui->set);
}

void	start_screen(t_game *game)
{
	KW_Rect windowrect = {0, 0, WIN_W, WIN_H};
	SDL_SetRenderDrawColor(game->sdl->renderer, 100, 100, 200, 1);
	init_kiwi(game);
	/* Create the top-level framve */

	KW_Rect framerect = { .x = 10, .y = 10, .w = 300, .h = 220 };
	KW_RectCenterInParent(&windowrect, &framerect);
	KW_Widget * frame = KW_CreateFrame(game->gui->gui, NULL, &framerect);

	/* Create the title, label and edibox widgets */
	KW_Rect titlerect = { .x = 0, .y = 10, .w = 300, .h = 30 };
	KW_Rect labelrect = { .y = 100, .w = 60, .h = 30 };
	KW_Rect editboxrect = { .y = 100, .w = 100, .h = 40 };
	KW_Rect * rects[] = { &labelrect, &editboxrect };
	unsigned weights[] = { 1, 4 };
	KW_RectFillParentHorizontally(&framerect, rects, weights, 2, 10, KW_RECT_ALIGN_MIDDLE);
	KW_CreateLabel(game->gui->gui, frame, "Editbox example", &titlerect);
	KW_CreateLabel(game->gui->gui, frame, "Label", &labelrect);
	game->gui->editBox = KW_CreateEditbox(game->gui->gui, frame, "Edit me!", &editboxrect);
	KW_Rect buttonrect = { .x = 250, .y = 170, .w = 40, .h = 40 };
	KW_Widget * okbutton = KW_CreateButtonAndLabel(game->gui->gui, frame, "OK", &buttonrect);
	KW_AddWidgetMouseDownHandler(okbutton, OKClicked);
	loopa(game);
}

void	quit_kiwi(t_game *game)
{
	KW_Quit(game->gui->gui);
	KW_ReleaseSurface(game->gui->driver, game->gui->set);
	KW_ReleaseRenderDriver(game->gui->driver);
}
