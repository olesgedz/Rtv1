/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cameras.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:32:09 by lminta            #+#    #+#             */
/*   Updated: 2019/11/25 22:44:35 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	clicked_cs(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_game		*game;

	game = KW_GetWidgetUserData(widget);
	if (game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	gui = g_gui(0, 0);
	gui->c_s.show = !gui->c_s.show;
	if (gui->c_s.show)
		KW_ShowWidget(gui->c_s.frame);
	else
		KW_HideWidget(gui->c_s.frame);
}

void		cam_button(t_game *game, t_gui *gui)
{
	gui->g_b.buttonrect[5] = gui->g_b.buttonrect[0];
	gui->g_b.buttonrect[5].x += gui->g_b.buttonrect[5].w;
	gui->g_b.rects[5] = &gui->g_b.buttonrect[5];
	gui->g_b.buttons[5] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Cameras", gui->g_b.rects[5]);
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[5], clicked_cs);
	KW_SetWidgetUserData(gui->g_b.buttons[5], (void *)game);
}

void		cam_rename(t_game *game, t_gui *gui)
{
	KW_Widget	*label;
	char		*buff;

	label = KW_GetButtonLabel(gui->c_s.buttons[game->cam_num]);
	buff = cam_mass_name(&game->gpu.camera[game->cam_num]);
	KW_SetLabelText(label, buff);
	free(buff);
}
