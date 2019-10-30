/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_button.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:38:36 by lminta            #+#    #+#             */
/*   Updated: 2019/10/30 14:44:22 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		show_hide(t_game *game, t_gui *gui)
{
	game->keys.show_gui = !game->keys.show_gui;
	if (game->keys.show_gui)
	{
		KW_ShowWidget(gui->i_b.frame);
		KW_ShowWidget(gui->o_s.frame);
		KW_ShowWidget(gui->s_s.frame);
	}
	else
	{
		KW_HideWidget(gui->i_b.frame);
		KW_HideWidget(gui->o_s.frame);
		KW_HideWidget(gui->s_s.frame);
	}
}

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

static void	clicked(KW_Widget *widget, int b)
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

void		semples_to_line(t_game *game, t_gui *gui)
{
	char *buff;

	buff = ft_itoa(game->gpu.samples);
	free(gui->i_b.names);
	gui->i_b.names = ft_strjoin("Samples: ", buff);
	free(buff);
	if (!gui->i_b.label)
		gui->i_b.label = KW_CreateLabel(gui->gui, gui->i_b.frame,
	gui->i_b.names, &gui->i_b.titlerect);
	else
		KW_SetLabelText(gui->i_b.label, gui->i_b.names);
}

void		info_button(t_game *game, t_gui *gui)
{
	unsigned			test;
	int					fr_sz;

	gui->i_b.label = 0;
	fr_sz = WIN_W / 10.;
	gui->i_b.weights[0] = 1;
	gui->i_b.frect = (KW_Rect){10, WIN_H - 110, fr_sz, 100};
	gui->i_b.titlerect = (KW_Rect){10, 10, fr_sz - 20, 30};
	gui->i_b.buttonrect = (KW_Rect){0, 0, 30, 40};
	gui->i_b.rects[0] = &gui->i_b.buttonrect;
	KW_RectFillParentHorizontally(&gui->i_b.frect,
	gui->i_b.rects, gui->i_b.weights, 1, 15,
	KW_RECT_ALIGN_MIDDLE);
	gui->i_b.buttonrect.y += 10;
	gui->i_b.frame = KW_CreateFrame(gui->gui, NULL, &gui->i_b.frect);
	semples_to_line(game, gui);
	gui->i_b.buttons = KW_CreateButtonAndLabel(gui->gui,
gui->i_b.frame, "Take picture", &gui->i_b.buttonrect);
	KW_AddWidgetMouseDownHandler(gui->i_b.buttons, clicked);
	KW_SetWidgetUserData(gui->i_b.buttons, (void *)game);
}
