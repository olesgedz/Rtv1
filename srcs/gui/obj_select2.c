/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_select2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 23:05:06 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/10 23:22:15 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static char			*fill_name_mass_switch(t_obj *obj, char *number)
{
	char	*res;

	if (obj->type == SPHERE)
		res = ft_strjoin("Sphere ", number);
	else if (obj->type == CONE)
		res = ft_strjoin("Cone ", number);
	else if (obj->type == TRIANGLE)
		res = ft_strjoin("Triangle ", number);
	else if (obj->type == CYLINDER)
		res = ft_strjoin("Cylinder ", number);
	else if (obj->type == PLANE)
		res = ft_strjoin("Plane ", number);
	else if (obj->type == PARABOLOID)
		res = ft_strjoin("Paraboloid ", number);
	else if (obj->type == TORUS)
		res = ft_strjoin("Torus ", number);
	return (res);
}

char				*fill_name_mass(t_obj *obj, int num)
{
	char	*number;
	char	*res;
	char	*buff;

	number = ft_itoa(obj->id);
	res = fill_name_mass_switch(obj, number);
	if ((int)(obj->emission.v4[0] + obj->emission.v4[1] + obj->emission.v4[2]))
	{
		buff = res;
		res = ft_strjoin("Light ", res);
		free(buff);
	}
	free(number);
	return (res);
}

static void			obj_click_ur(t_gui *gui, KW_Widget *widget,\
KW_Widget *wid, t_obj *obj)
{
	obj = KW_GetWidgetUserData(widget);
	obj_if(gui, obj);
	wid = widget;
	KW_SetLabelTextColor(KW_GetButtonLabel(wid),
	(KW_Color){255, 255, 255, 255});
	gui->c_o.show = 1;
}

void				obj_click(KW_Widget *widget, int b)
{
	static t_obj		*obj;
	static KW_Widget	*wid = 0;
	t_gui				*gui;
	KW_Widget			*label;
	t_obj				*obje;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	if (gui->c_o.show == 1)
		norma_from_obj_select(gui, widget, wid);
	if (widget && (obj != KW_GetWidgetUserData(widget)))
	{
		obj_click_ur(gui, widget, wid, obj);
	}
	else
	{
		wid = 0;
		obj = 0;
	}
}
