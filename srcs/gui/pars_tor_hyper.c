/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars_tor_hyper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 19:56:43 by lminta            #+#    #+#             */
/*   Updated: 2019/12/09 20:03:18 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	tor_parse(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	parse_position(gui, obj, &i);
	parse_direction(gui, obj, &i);
	parse_radius(gui, obj, &i);
	parse_color_emission(gui, obj, &i);
	parse_refraction(gui, obj, &i);
}

void	hyper_parse(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	parse_position(gui, obj, &i);
	parse_direction(gui, obj, &i);
	parse_radius(gui, obj, &i);
	parse_color_emission(gui, obj, &i);
	parse_refraction(gui, obj, &i);
}
