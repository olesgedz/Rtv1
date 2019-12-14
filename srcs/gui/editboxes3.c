/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editboxes3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 21:58:12 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/14 14:56:38 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		text_normal_exists(t_gui *gui, t_obj *obj, int *i)
{
	if (obj->texture > 0)
		gui->c_o.ed_b[(*i)++] = KW_CreateEditbox(gui->gui, gui->c_o.frame,
			gui->game->texture_list[obj->texture - 1], gui->c_o.rects[1]);
	else if (obj->texture == -1)
	{
		gui->c_o.ed_b[(*i)++] = KW_CreateEditbox(gui->gui, gui->c_o.frame,
		"chess", gui->c_o.rects[1]);
	}
	else if (obj->texture == -2)
	{
		gui->c_o.ed_b[(*i)++] = KW_CreateEditbox(gui->gui, gui->c_o.frame,
		"perlin", gui->c_o.rects[1]);
	}
	else if (obj->texture == -3)
	{
		gui->c_o.ed_b[(*i)++] = KW_CreateEditbox(gui->gui, gui->c_o.frame,
		"wave", gui->c_o.rects[1]);
	}
}

void			text_normal(t_gui *gui, t_obj *obj, int *i)
{
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Textures", gui->c_o.rects[0]);
	if (obj->texture)
		text_normal_exists(gui, obj, i);
	else
		gui->c_o.ed_b[(*i)++] = KW_CreateEditbox(gui->gui, gui->c_o.frame,
		"No texture", gui->c_o.rects[1]);
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Normals", gui->c_o.rects[2]);
	if (obj->normal)
		gui->c_o.ed_b[(*i)++] = KW_CreateEditbox(gui->gui, gui->c_o.frame,
		gui->game->normal_list[obj->normal - 1], gui->c_o.rects[3]);
	else
		gui->c_o.ed_b[(*i)++] = KW_CreateEditbox(gui->gui, gui->c_o.frame,
		"No normal", gui->c_o.rects[3]);
}

void			sep(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_cam		*cam;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	cam = KW_GetWidgetUserData(widget);
	cam->sepia = !cam->sepia;
	sep_name(widget, cam);
}

void			gui_bar(t_game *game, t_gui *gui)
{
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
	obj_type(gui);
	KW_HideWidget(gui->o_t.frame);
	net_list(gui);
	KW_HideWidget(gui->n.frame);
}
