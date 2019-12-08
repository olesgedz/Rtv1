/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_gui.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 13:50:08 by lminta            #+#    #+#             */
/*   Updated: 2019/12/08 20:00:41 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	net_name(t_gui *gui)
{
	gui->n.weights[0] = 1;
	gui->n.frect = (KW_Rect){2 * gui->g_b.buttonrect[0].w + 5, 25, FR_FZ, 80};
	gui->n.buttonrect[0] = (KW_Rect){0, 0, 30, 40};
	gui->n.names[0] = "Connect";
	gui->n.names[1] = "Send map";
	gui->n.names[2] = "Render 10000";
}

void		net_list(t_game *game, t_gui *gui)
{
	int					i;
	unsigned			test;

	net_name(gui);
	gui->n.rects[0] = &gui->n.buttonrect[0];
	KW_RectFillParentHorizontally(&gui->n.frect,
	gui->n.rects, gui->n.weights, 1, 15, KW_RECT_ALIGN_MIDDLE);
	i = 0;
	while (++i < 3)
	{
		gui->n.buttonrect[i] = gui->n.buttonrect[i - 1];
		gui->n.buttonrect[i].y += 45;
		gui->n.frect.h += 45;
	}
	gui->n.frame = KW_CreateFrame(gui->gui, NULL, &gui->n.frect);
	i = -1;
	while (++i < 3)
		gui->n.buttons[i] = KW_CreateButtonAndLabel(gui->gui,
		gui->n.frame, gui->n.names[i], &gui->n.buttonrect[i]);
	edit_ip(gui);
	KW_HideWidget(gui->ed_w.frame);
	network_buttons(gui);
}

static void	clicked_net(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_game		*game;

	game = KW_GetWidgetUserData(widget);
	if (game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	gui = g_gui(0, 0);
	gui->n.show = !gui->n.show;
	if (gui->n.show)
	{
		KW_ShowWidget(gui->n.frame);
		KW_SetLabelTextColor(KW_GetButtonLabel(widget),
		(KW_Color){255, 255, 255, 255});
	}
	else
	{
		KW_HideWidget(gui->n.frame);
		KW_SetLabelTextColor(KW_GetButtonLabel(widget),
		(KW_Color){0, 0, 0, 0});
	}
}

void		net_butt(t_game *game, t_gui *gui)
{
	gui->g_b.buttonrect[7] = gui->g_b.buttonrect[5];
	gui->g_b.buttonrect[7].x += gui->g_b.buttonrect[3].w;
	gui->g_b.rects[7] = &gui->g_b.buttonrect[7];
	gui->g_b.buttons[7] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Network", gui->g_b.rects[7]);
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[7], clicked_net);
	KW_SetWidgetUserData(gui->g_b.buttons[7], (void *)game);
}

void	clicked_send(KW_Widget *widget, int b)
{
	t_gui		*gui;
	int			i;

	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	send_map(gui->game, gui);
	i = -1;
	while (++i < gui->n.clients)
		SDLNet_TCP_Send(gui->n.client[i], "0 smpl", 7);
}
