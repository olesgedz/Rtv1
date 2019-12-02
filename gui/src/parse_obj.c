/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_obj.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 17:48:08 by lminta            #+#    #+#             */
/*   Updated: 2019/12/02 17:34:57 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	plane_parse(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	parse_position(gui, obj, &i);
	parse_direction(gui, obj, &i);
	parse_color_emission(gui, obj, &i);
	parse_text_normal(gui, obj, &i);
	parse_bas(gui, obj, &i);
	parse_shift(gui, obj, &i);
	parse_prolapse(gui, obj, &i);
}

void	sphere_parse(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	parse_position(gui, obj, &i);
	parse_radius(gui, obj, &i);
	parse_color_emission(gui, obj, &i);
	parse_text_normal(gui, obj, &i);
	parse_bas(gui, obj, &i);
	parse_shift(gui, obj, &i);
}

void	cylin_parse(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	parse_position(gui, obj, &i);
	parse_direction(gui, obj, &i);
	parse_radius(gui, obj, &i);
	parse_color_emission(gui, obj, &i);
	parse_text_normal(gui, obj, &i);
	parse_bas(gui, obj, &i);
	parse_shift(gui, obj, &i);
	parse_prolapse(gui, obj, &i);
}

void	cone_parse(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	parse_position(gui, obj, &i);
	parse_direction(gui, obj, &i);
	parse_radius(gui, obj, &i);
	parse_color_emission(gui, obj, &i);
	parse_text_normal(gui, obj, &i);
	parse_bas(gui, obj, &i);
	parse_shift(gui, obj, &i);
	parse_prolapse(gui, obj, &i);
}

void	trian_parse(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	parse_vert(gui, obj, &i);
	parse_color_emission(gui, obj, &i);
}
