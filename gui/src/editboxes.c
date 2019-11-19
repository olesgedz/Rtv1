/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editboxes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:04:17 by lminta            #+#    #+#             */
/*   Updated: 2019/11/19 22:16:04 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	vert(t_gui *gui, t_obj *obj)
{
	if (obj->type != TRIANGLE)
		return ;
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	gui->c_o.edit_box[12] = f_eb(gui, obj->vertices[0].s[0], gui->c_o.rects[1]);
	gui->c_o.edit_box[13] = f_eb(gui, obj->vertices[0].s[1], gui->c_o.rects[2]);
	gui->c_o.edit_box[14] = f_eb(gui, obj->vertices[0].s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Vertices", &gui->c_o.labelrect);
	gui->c_o.edit_box[15] = f_eb(gui, obj->vertices[1].s[0], gui->c_o.rects[1]);
	gui->c_o.edit_box[16] = f_eb(gui, obj->vertices[1].s[1], gui->c_o.rects[2]);
	gui->c_o.edit_box[17] = f_eb(gui, obj->vertices[1].s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	gui->c_o.edit_box[18] = f_eb(gui, obj->vertices[2].s[0], gui->c_o.rects[1]);
	gui->c_o.edit_box[19] = f_eb(gui, obj->vertices[2].s[1], gui->c_o.rects[2]);
	gui->c_o.edit_box[20] = f_eb(gui, obj->vertices[2].s[2], gui->c_o.rects[3]);
}

void	basis(t_gui *gui, t_obj *obj)
{
	vert(gui, obj);
	if (obj->type == TRIANGLE)
		return ;
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	gui->c_o.edit_box[12] = f_eb(gui, obj->basis[0].s[0], gui->c_o.rects[1]);
	gui->c_o.edit_box[13] = f_eb(gui, obj->basis[0].s[1], gui->c_o.rects[2]);
	gui->c_o.edit_box[14] = f_eb(gui, obj->basis[0].s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Basis", &gui->c_o.labelrect);
	gui->c_o.edit_box[15] = f_eb(gui, obj->basis[1].s[0], gui->c_o.rects[1]);
	gui->c_o.edit_box[16] = f_eb(gui, obj->basis[1].s[1], gui->c_o.rects[2]);
	gui->c_o.edit_box[17] = f_eb(gui, obj->basis[1].s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	gui->c_o.edit_box[18] = f_eb(gui, obj->basis[2].s[0], gui->c_o.rects[1]);
	gui->c_o.edit_box[19] = f_eb(gui, obj->basis[2].s[1], gui->c_o.rects[2]);
	gui->c_o.edit_box[20] = f_eb(gui, obj->basis[2].s[2], gui->c_o.rects[3]);
}

void	color_emission(t_gui *gui, t_obj *obj)
{
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Color", &gui->c_o.labelrect);
	gui->c_o.edit_box[3] = f_eb(gui, obj->color.s[0], gui->c_o.rects[1]);
	gui->c_o.edit_box[4] = f_eb(gui, obj->color.s[1], gui->c_o.rects[2]);
	gui->c_o.edit_box[5] = f_eb(gui, obj->color.s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Emission", &gui->c_o.labelrect);
	gui->c_o.edit_box[6] = f_eb(gui, obj->emission.s[0], gui->c_o.rects[1]);
	gui->c_o.edit_box[7] = f_eb(gui, obj->emission.s[1], gui->c_o.rects[2]);
	gui->c_o.edit_box[8] = f_eb(gui, obj->emission.s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Reflection", &gui->c_o.labelrect);
	gui->c_o.edit_box[9] = f_eb(gui, obj->metalness, gui->c_o.rects[1]);
	gui->c_o.edit_box[10] = f_eb(gui, obj->metalness, gui->c_o.rects[2]);
	gui->c_o.edit_box[11] = f_eb(gui, obj->metalness, gui->c_o.rects[3]);
	basis(gui, obj);
}
