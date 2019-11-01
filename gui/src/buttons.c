/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:08:05 by lminta            #+#    #+#             */
/*   Updated: 2019/11/01 15:29:23 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char	*filename(void)
{
	FILE	*fp;
	char	*buff;
	char	*name;
	int		i;

	i = 1;
	name = ft_strdup("screens/screen_0.png");
	while ((fp = fopen(name, "r")))
	{
		buff = ft_itoa(i);
		free(name);
		name = ft_strjoin("screens/screen_", buff);
		free(buff);
		buff = ft_strjoin(name, ".png");
		free(name);
		i++;
		fclose(fp);
		name = buff;
	}
	return (name);
}

static void	shot(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_game		*game;
	SDL_Surface	*surface;
	char		*name;

	game = KW_GetWidgetUserData(widget);
	if (game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	gui = g_gui(0, 0);
	surface = SDL_CreateRGBSurface(0, WIN_W, WIN_H, 32, 0, 0, 0, 0);
	SDL_RenderReadPixels(game->sdl.renderer, NULL,
	surface->format->format, surface->pixels, surface->pitch);
	name = filename();
	IMG_SavePNG(surface, name);
	free(name);
	SDL_FreeSurface(surface);
}

static void	clicked_ss(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_game		*game;

	game = KW_GetWidgetUserData(widget);
	if (game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	gui = g_gui(0, 0);
	gui->s_s.show = !gui->s_s.show;
	if (gui->s_s.show)
		KW_ShowWidget(gui->s_s.frame);
	else
		KW_HideWidget(gui->s_s.frame);
}

static void	clicked_os(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_game		*game;

	game = KW_GetWidgetUserData(widget);
	if (game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	gui = g_gui(0, 0);
	gui->o_s.show = !gui->o_s.show;
	if (gui->o_s.show)
		KW_ShowWidget(gui->o_s.frame);
	else
		KW_HideWidget(gui->o_s.frame);
}

void	buttons(t_game *game, t_gui *gui)
{
	gui->g_b.buttonrect[0] = (KW_Rect){5, 0, FR_FZ, 40};
	gui->g_b.rects[0] = &gui->g_b.buttonrect[0];
	gui->g_b.weights[0] = 1;
	KW_RectFillParentVertically(&gui->g_b.frect,
	gui->g_b.rects, gui->g_b.weights, 1, 5);
	gui->g_b.buttons[0] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Available Scenes", gui->g_b.rects[0]);
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[0], clicked_ss);
	KW_SetWidgetUserData(gui->g_b.buttons[0], (void *)game);
	gui->g_b.buttonrect[1] = gui->g_b.buttonrect[0];
	gui->g_b.buttonrect[1].x = WIN_W - 5 - gui->g_b.buttonrect[1].w;
	gui->g_b.rects[1] = &gui->g_b.buttonrect[1];
	gui->g_b.buttons[1] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Objects in Scene", gui->g_b.rects[1]);
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[1], clicked_os);
	KW_SetWidgetUserData(gui->g_b.buttons[1], (void *)game);
	gui->g_b.buttonrect[2] = gui->g_b.buttonrect[1];
	gui->g_b.buttonrect[2].x -= gui->g_b.buttonrect[2].w;
	gui->g_b.rects[2] = &gui->g_b.buttonrect[2];
	gui->g_b.buttons[2] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Take picture", gui->g_b.rects[2]);
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[2], shot);
	KW_SetWidgetUserData(gui->g_b.buttons[2], (void *)game);
	info_button(game, gui);
}
