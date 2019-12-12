/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_connect.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 15:27:04 by lminta            #+#    #+#             */
/*   Updated: 2019/12/10 18:40:41 by lminta           ###   ########.fr       */
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
	gui->ed_w.show = !gui->ed_w.show;
	if (gui->ed_w.show)
	{
		KW_ShowWidget(gui->ed_w.frame);
		KW_SetLabelTextColor(KW_GetButtonLabel(widget),
		(KW_Color){255, 255, 255, 255});
	}
	else
	{
		KW_HideWidget(gui->ed_w.frame);
		KW_SetLabelTextColor(KW_GetButtonLabel(widget),
		(KW_Color){0, 0, 0, 0});
	}
}

void		network_buttons(t_gui *gui)
{
	KW_AddWidgetMouseDownHandler(gui->n.buttons[0], clicked_connect);
	KW_AddWidgetMouseDownHandler(gui->n.buttons[1], clicked_send);
	KW_AddWidgetMouseDownHandler(gui->n.buttons[2], net_render);
	gui->n.ed_b = KW_CreateEditbox(gui->gui,
	gui->n.frame, "10000", &gui->n.buttonrect[3]);
}

static void	ok_cl(KW_Widget *widget, int b)
{
	t_gui	*gui;

	b = 0;
	widget = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	free(gui->n.str_ip);
	gui->n.str_ip = ft_strdup((char *)KW_GetEditboxText(gui->ed_w.ed_b));
	SDLNet_ResolveHost(&gui->n.ip, gui->n.str_ip, 9999);
	gui->n.tcpsock = SDLNet_TCP_Open(&gui->n.ip);
	KW_HideWidget(gui->ed_w.frame);
	gui->ed_w.show = 0;
	KW_SetLabelTextColor(KW_GetButtonLabel(gui->n.buttons[0]),
	(KW_Color){0, 0, 0, 0});
}

static void	serv_butt(t_gui *gui)
{
	gui->ed_w.buttonrect = (KW_Rect){210, 170, 80, 40};
	gui->ed_w.okbutton = KW_CreateButtonAndLabel(gui->gui,
	gui->ed_w.frame, "OK", &gui->ed_w.buttonrect);
	KW_AddWidgetMouseDownHandler(gui->ed_w.okbutton, ok_cl);
	gui->ed_w.buttonrect.x = 10;
	gui->ed_w.servbut = KW_CreateButtonAndLabel(gui->gui,
	gui->ed_w.frame, "Client", &gui->ed_w.buttonrect);
	KW_AddWidgetMouseDownHandler(gui->ed_w.servbut, server_on);
}

void		edit_ip(t_gui *gui)
{
	gui->ed_w.frect = (KW_Rect){10, 10, 300, 220};
	KW_RectCenterInParent(&gui->ed_w.winrect, &gui->ed_w.frect);
	gui->ed_w.frame =
	KW_CreateFrame(gui->gui, NULL, &gui->ed_w.frect);
	gui->ed_w.titlerect = (KW_Rect){0, 10, 300, 30};
	gui->ed_w.labelrect = (KW_Rect){0, 100, 60, 30};
	gui->ed_w.editboxrect = (KW_Rect){0, 100, 100, 40};
	gui->ed_w.rects[0] = &gui->ed_w.labelrect;
	gui->ed_w.rects[1] = &gui->ed_w.editboxrect;
	gui->ed_w.weights[0] = 1;
	gui->ed_w.weights[1] = 4;
	KW_RectFillParentHorizontally(&gui->ed_w.frect,
	gui->ed_w.rects, gui->ed_w.weights, 2, 10, KW_RECT_ALIGN_MIDDLE);
	gui->ed_w.label = KW_CreateLabel(gui->gui, gui->ed_w.frame,
	"Enter host's IP", &gui->ed_w.titlerect);
	KW_CreateLabel(gui->gui, gui->ed_w.frame,
	"IP", &gui->ed_w.labelrect);
	gui->ed_w.ed_b = KW_CreateEditbox(gui->gui,
	gui->ed_w.frame, "localhost", &gui->ed_w.editboxrect);
	serv_butt(gui);
}
