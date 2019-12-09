/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 20:10:09 by lminta            #+#    #+#             */
/*   Updated: 2019/12/04 22:49:48 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	change_plane(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	obj_same(gui, obj);
	position(gui, obj, &i);
	direction(gui, obj, &i);
	color_emission(gui, obj, &i);
	refraction(gui, obj, &i);
	text_normal(gui, obj, &i);
	basis(gui, obj, &i);
	shift(gui, obj, &i);
	prolapse(gui, obj, &i);
}

void	change_sphere(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	obj_same(gui, obj);
	position(gui, obj, &i);
	radius(gui, obj, &i);
	color_emission(gui, obj, &i);
	refraction(gui, obj, &i);
	text_normal(gui, obj, &i);
	basis(gui, obj, &i);
	shift(gui, obj, &i);
}

void	change_cylin(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	obj_same(gui, obj);
	position(gui, obj, &i);
	direction(gui, obj, &i);
	radius(gui, obj, &i);
	color_emission(gui, obj, &i);
	refraction(gui, obj, &i);
	text_normal(gui, obj, &i);
	basis(gui, obj, &i);
	shift(gui, obj, &i);
	prolapse(gui, obj, &i);
}

void	change_cone(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	obj_same(gui, obj);
	position(gui, obj, &i);
	direction(gui, obj, &i);
	radius(gui, obj, &i);
	color_emission(gui, obj, &i);
	refraction(gui, obj, &i);
	text_normal(gui, obj, &i);
	basis(gui, obj, &i);
	shift(gui, obj, &i);
	prolapse(gui, obj, &i);
}

void	change_trian(t_gui *gui, t_obj *obj)
{
	int i;

	i = 0;
	obj_same(gui, obj);
	vert(gui, obj, &i);
	color_emission(gui, obj, &i);
	refraction(gui, obj, &i);
}
