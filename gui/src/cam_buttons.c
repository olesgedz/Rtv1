/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:59:39 by lminta            #+#    #+#             */
/*   Updated: 2019/12/01 19:12:58 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	take_cam(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_cam		*cam;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	cam = KW_GetWidgetUserData(widget);
	gui->game->cam_num = cam->id;
	gui->game->flag = 1;
}

void	cam_del_click(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_cam		*cam;

	b = 0;
	gui = g_gui(0, 0);
	cam = KW_GetWidgetUserData(widget);
	del_cam(cam, gui->game);
}

void	cam_delbutton(t_gui *gui, t_cam *cam)
{
	gui->c_c.buttonrect[2] = gui->c_c.buttonrect[0];
	gui->c_c.buttonrect[2].x += 2.5 + gui->c_c.buttonrect[0].w;
	gui->c_c.buttonrect[2].w = gui->c_c.buttonrect[1].x -
	gui->c_c.buttonrect[2].x - 2.5;
	gui->c_c.buttons[2] = KW_CreateButtonAndLabel(gui->gui,
	gui->c_c.frame, "Delete", &gui->c_c.buttonrect[2]);
	KW_AddWidgetMouseDownHandler(gui->c_c.buttons[2], cam_del_click);
	KW_SetWidgetUserData(gui->c_c.buttons[2], cam);
}

void	cam_savebutton(t_gui *gui, t_cam *cam)
{
	gui->c_c.buttonrect[1] = gui->c_c.buttonrect[0];
	gui->c_c.buttonrect[1].x = gui->c_c.buttonrect[1].x + gui->c_c.frect.w -
	gui->c_c.buttonrect[1].w - 10;
	gui->c_c.buttons[1] = KW_CreateButtonAndLabel(gui->gui,
	gui->c_c.frame, "Save", &gui->c_c.buttonrect[1]);
	KW_AddWidgetMouseDownHandler(gui->c_c.buttons[1], cam_save_click);
	KW_SetWidgetUserData(gui->c_c.buttons[1], cam);
}
