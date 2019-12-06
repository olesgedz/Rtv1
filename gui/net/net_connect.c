/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 15:27:04 by lminta            #+#    #+#             */
/*   Updated: 2019/12/06 16:52:51 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	clicked_connect(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_game		*game;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	gui->n.s_c.show = !gui->n.s_c.show;
	if (gui->n.s_c.show)
		KW_ShowWidget(gui->n.s_c.frame);
	else
		KW_HideWidget(gui->n.s_c.frame);
}

void		server_client(t_game *game, t_gui *gui)
{
	gui->n.s_c.show = 0;
	gui->n.s_c.weights[0] = 1;
	gui->n.s_c.frect =
	(KW_Rect){3 * gui->g_b.buttonrect[0].w - 10, 25, FR_FZ, 125};
	gui->n.s_c.names[0] = ft_strdup("Client");
	gui->n.s_c.names[1] = ft_strdup("Server");
	gui->n.s_c.buttonrect[0] = (KW_Rect){0, 0, 30, 40};
	gui->n.s_c.rects[0] = &gui->n.s_c.buttonrect[0];
	KW_RectFillParentHorizontally(&gui->n.s_c.frect,
	gui->n.s_c.rects, gui->n.s_c.weights, 1, 15, KW_RECT_ALIGN_MIDDLE);
	gui->n.s_c.buttonrect[1] = gui->n.s_c.buttonrect[0];
	gui->n.s_c.buttonrect[1].y += 45;
	gui->n.s_c.frame = KW_CreateFrame(gui->gui, NULL, &gui->n.s_c.frect);
	gui->n.s_c.buttons[0] = KW_CreateButtonAndLabel(gui->gui,
	gui->n.s_c.frame, gui->n.s_c.names[0], &gui->n.s_c.buttonrect[0]);
	gui->n.s_c.buttons[1] = KW_CreateButtonAndLabel(gui->gui,
	gui->n.s_c.frame, gui->n.s_c.names[1], &gui->n.s_c.buttonrect[1]);
}

void		network_buttons(t_gui *gui)
{
	KW_AddWidgetMouseDownHandler(gui->n.buttons[0], clicked_connect);

}
