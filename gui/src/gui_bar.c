/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_bar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:10:18 by lminta            #+#    #+#             */
/*   Updated: 2019/11/27 19:51:33 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	visibility(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_obj		*obj;

	b = 0;
	gui = g_gui(0, 0);
	obj = KW_GetWidgetUserData(widget);
	obj->is_visible = !obj->is_visible;
	visibility_name(widget, obj);
	gui->flag = 1;
}

void	click_create(KW_Widget *widget, int b)
{
	t_gui		*gui;
	int			num;

	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	num = *((int *)KW_GetWidgetUserData(widget));
	if (num == SPHERE)
		create_sphere(gui->game);
	else if (num == CONE)
		create_cone(gui->game);
	else if (num == TRIANGLE)
		create_triangle(gui->game);
	else if (num == CYLINDER)
		create_cylinder(gui->game);
	else if (num == PLANE)
		create_plane(gui->game);
	else if (num == 5)
		del_obj(0, gui->game);
	gui->flag = 1;
	obj_click(0, 0);
	if (num != 5)
		obj_click(gui->o_s.buttons[gui->game->obj_quantity - 1], 0);
}

void	save_click(KW_Widget *widget, int b)
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

void	del_click(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_obj		*obj;

	b = 0;
	gui = g_gui(0, 0);
	obj = KW_GetWidgetUserData(widget);
	del_obj(obj, gui->game);
	obj_click(0, 0);
	gui->flag = 1;
}

void		gui_bar(t_game *game, t_gui *gui)
{
	unsigned			test;

	gui->g_b.label = 0;
	gui->g_b.show = 1;
	gui->g_b.frect = (KW_Rect){0, 0, WIN_W, FR_FZ / 5.};
	gui->g_b.frame = KW_CreateFrame(gui->gui, NULL, &gui->g_b.frect);
	buttons(game, gui);
	cam_button(game, gui);
	info_button(game, gui);
	add_obj(game, gui);
	obj_type(game, gui);
	KW_HideWidget(gui->o_t.frame);
}
