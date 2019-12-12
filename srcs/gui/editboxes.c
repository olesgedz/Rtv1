/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editboxes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:04:17 by lminta            #+#    #+#             */
/*   Updated: 2019/12/12 16:34:13 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		shift(t_gui *gui, t_obj *obj, int *i)
{
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Shift", gui->c_o.rects[0]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->shift.s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->shift.s[1], gui->c_o.rects[2]);
}

void		vert(t_gui *gui, t_obj *obj, int *i)
{
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->vertices[0].s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->vertices[0].s[1], gui->c_o.rects[2]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->vertices[0].s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Vertices", gui->c_o.rects[0]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->vertices[1].s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->vertices[1].s[1], gui->c_o.rects[2]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->vertices[1].s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->vertices[2].s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->vertices[2].s[1], gui->c_o.rects[2]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->vertices[2].s[2], gui->c_o.rects[3]);
}

void		basis(t_gui *gui, t_obj *obj, int *i)
{
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->basis[0].s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->basis[0].s[1], gui->c_o.rects[2]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->basis[0].s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Basis", gui->c_o.rects[0]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->basis[1].s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->basis[1].s[1], gui->c_o.rects[2]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->basis[1].s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->basis[2].s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->basis[2].s[1], gui->c_o.rects[2]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->basis[2].s[2], gui->c_o.rects[3]);
}

void		color_emission(t_gui *gui, t_obj *obj, int *i)
{
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Color", gui->c_o.rects[0]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->color.s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->color.s[1], gui->c_o.rects[2]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->color.s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Emission", gui->c_o.rects[0]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->emission.s[0], gui->c_o.rects[1]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->emission.s[1], gui->c_o.rects[2]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->emission.s[2], gui->c_o.rects[3]);
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Metalness", gui->c_o.rects[0]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->metalness, gui->c_o.rects[1]);
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Transparency", gui->c_o.rects[2]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->transparency, gui->c_o.rects[3]);
}
