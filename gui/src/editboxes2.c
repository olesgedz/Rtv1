/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editboxes2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 21:30:38 by lminta            #+#    #+#             */
/*   Updated: 2019/12/01 19:13:37 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			radius(t_gui *gui, t_obj *obj, int *i)
{
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Radius", gui->c_o.rects[0]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->radius, gui->c_o.rects[1]);
}

void			direction(t_gui *gui, t_obj *obj, int *i)
{
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Direction", gui->c_o.rects[0]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->v.s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->v.s[1], gui->c_o.rects[2]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->v.s[2], gui->c_o.rects[3]);
}

void			position(t_gui *gui, t_obj *obj, int *i)
{
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Position", gui->c_o.rects[0]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->position.s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->position.s[1], gui->c_o.rects[2]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->position.s[2], gui->c_o.rects[3]);
}

void			prolapse(t_gui *gui, t_obj *obj, int *i)
{
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Prolapse", gui->c_o.rects[0]);
	if (obj->type == PLANE)
		gui->c_o.ed_b[(*i)++] = f_e(gui, obj->prolapse.s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->prolapse.s[1], gui->c_o.rects[2]);
}

void			savebutton(t_gui *gui, t_obj *obj)
{
	gui->c_o.buttonrect[1] = gui->c_o.buttonrect[0];
	gui->c_o.buttonrect[1].x = gui->c_o.buttonrect[1].x + gui->c_o.frect.w -
	gui->c_o.buttonrect[1].w - 10;
	gui->c_o.buttons[1] = KW_CreateButtonAndLabel(gui->gui,
	gui->c_o.frame, "Save", &gui->c_o.buttonrect[1]);
	KW_AddWidgetMouseDownHandler(gui->c_o.buttons[1], save_click);
	KW_SetWidgetUserData(gui->c_o.buttons[1], obj);
}
