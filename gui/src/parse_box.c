/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_box.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/19 20:04:17 by lminta            #+#    #+#             */
/*   Updated: 2019/12/01 19:12:17 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		parse_shift(t_gui *gui, t_obj *obj, int *i)
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
	char	*res;

	res = ft_strdup(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	if (ft_strcmp(res, "No texture") != 0)
	{
		obj->texture = compare_in_texture_dict(gui->game, res);
		if (obj->texture == gui->game->textures_num + 1)
			push_tex(gui->game, res);
	}
	else
		obj->texture = 0;
	free(res);
	res = ft_strdup(KW_GetEditboxText(gui->c_o.ed_b[(*i)++]));
	if (ft_strcmp(res, "No normal") != 0)
	{
		obj->normal = compare_in_normal_dict(gui->game, res);
		if (obj->normal == gui->game->normals_num + 1)
			push_normal(gui->game, res);
	}
	else
		obj->normal = 0;
	free(res);
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
