/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_bar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:10:18 by lminta            #+#    #+#             */
/*   Updated: 2019/12/06 14:38:04 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	visibility(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_obj		*obj;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
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
	else if (num == CYLINDER)
		create_cylinder(gui->game);
	else if (num == CONE)
		create_cone(gui->game);
	else if (num == PLANE)
		create_plane(gui->game);
	else if (num == TRIANGLE)
		create_triangle(gui->game);
	else if (num == TORUS)
		create_tor(gui->game);
	else if (num == PARABOLOID)
		create_hyper(gui->game);
	else if (num == 7)
		del_obj(0, gui->game);
	gui->flag = 1;
	obj_click(0, 0);
	if (num < 7)
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
	else if (obj->type == PARABOLOID)
		hyper_parse(gui, obj);
	else if (obj->type == TORUS)
		tor_parse(gui, obj);
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
	gui->g_b.frect = (KW_Rect){0, 0, WIN_W, 38};
	gui->g_b.frame = KW_CreateFrame(gui->gui, NULL, &gui->g_b.frect);
	buttons(game, gui);
	cam_button(game, gui);
	info_button(game, gui);
	add_obj(game, gui);
	gui_mod_but(game, gui);
	dumper_butt(game, gui);
	net_butt(game, gui);
	obj_type(game, gui);
	KW_HideWidget(gui->o_t.frame);
	net_list(game, gui);
	KW_HideWidget(gui->n.frame);
}
