/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_buttons.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:59:39 by lminta            #+#    #+#             */
/*   Updated: 2019/11/26 18:32:14 by lminta           ###   ########.fr       */
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

void	cam_save_click(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_obj		*obj;

	b = 0;
	gui = g_gui(0, 0);
	obj = KW_GetWidgetUserData(widget);
	if (obj->type == PLANE)
		plane_parse(gui, obj);
	else if (obj->type == CONE)
		cone_parse(gui, obj);
	else if (obj->type == CYLINDER)
		cylin_parse(gui, obj);
	else if (obj->type == SPHERE)
		sphere_parse(gui, obj);
	else if (obj->type == TRIANGLE)
		trian_parse(gui, obj);
	gui->flag = 1;
}

void	cam_del_click(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_obj		*obj;

	b = 0;
	gui = g_gui(0, 0);
	obj = KW_GetWidgetUserData(widget);
	//del_obj(obj, gui->game);
	//obj_click(0, 0);
	gui->game->flag = 1;
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
