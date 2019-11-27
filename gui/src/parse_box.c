/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_box.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:04:17 by lminta            #+#    #+#             */
/*   Updated: 2019/11/21 19:40:16 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			parse_shift(t_gui *gui, t_obj *obj, int *i)
{
	obj->shift.s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->shift.s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
}

void		parse_vert(t_gui *gui, t_obj *obj, int *i)
{
	obj->vertices[0].s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->vertices[0].s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->vertices[0].s[2] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->vertices[1].s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->vertices[1].s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->vertices[1].s[2] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->vertices[2].s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->vertices[2].s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->vertices[2].s[2] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
}

void		parse_bas(t_gui *gui, t_obj *obj, int *i)
{
	obj->basis[0].s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->basis[0].s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->basis[0].s[2] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->basis[1].s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->basis[1].s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->basis[1].s[2] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->basis[2].s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->basis[2].s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->basis[2].s[2] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
}

void		parse_text_normal(t_gui *gui, t_obj *obj, int *i)
{
	(*i)++;
	(*i)++;
	printf("textur net\n");
}

void		parse_color_emission(t_gui *gui, t_obj *obj, int *i)
{
	obj->color.s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->color.s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->color.s[2] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->emission.s[0] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->emission.s[1] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->emission.s[2] = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	obj->metalness = atof(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
}
