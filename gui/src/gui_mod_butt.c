/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_mod_butt.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 16:21:56 by lminta            #+#    #+#             */
/*   Updated: 2019/12/04 17:24:00 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	mod_rename(t_game *game, KW_Widget *widget)
{
	KW_Widget	*label;

	label = KW_GetButtonLabel(widget);
	if (game->gui_mod)
		KW_SetLabelText(label, "Gui mod 1");
	else
		KW_SetLabelText(label, "Gui mod 0");
}

static void	clicked_mod(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_game		*game;

	game = KW_GetWidgetUserData(widget);
	if (game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	gui = g_gui(0, 0);
	gui->game->gui_mod = !gui->game->gui_mod;
	mod_rename(gui->game, gui->g_b.buttons[6]);
}

void		gui_mod_but(t_game *game, t_gui *gui)
{
	gui->g_b.buttonrect[6] = gui->g_b.buttonrect[0];
	gui->g_b.buttonrect[6].x = (WIN_W - gui->g_b.buttonrect[6].w) / 2;
	gui->g_b.rects[6] = &gui->g_b.buttonrect[6];
	gui->g_b.buttons[6] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Cameras", gui->g_b.rects[6]);
	mod_rename(game, gui->g_b.buttons[6]);
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[6], clicked_mod);
	KW_SetWidgetUserData(gui->g_b.buttons[6], (void *)game);
}
