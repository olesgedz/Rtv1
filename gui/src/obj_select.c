/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:08:02 by lminta            #+#    #+#             */
/*   Updated: 2019/12/03 19:38:09 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		obj_click(KW_Widget *widget, int b)
{
	static t_obj		*obj;
	static KW_Widget	*wid = 0;
	t_gui				*gui;
	KW_Widget *label;
	t_obj	*obje;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	if (gui->c_o.show == 1)
		norma_from_obj_select(gui, widget, wid);
	if (widget && (obj != KW_GetWidgetUserData(widget)))
	{
		obj = KW_GetWidgetUserData(widget);
		obj_if(gui, obj);
		wid = widget;
		KW_SetLabelTextColor(KW_GetButtonLabel(wid),
		(KW_Color){255, 255, 255, 255});
		gui->c_o.show = 1;
	}
	else
	{
		wid = 0;
		obj = 0;
	}
}

char		*fill_name_mass(t_obj *obj, int num)
{
	char	*number;
	char	*res;
	char	*buff;

	number = ft_itoa(obj->id);
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
	else if (obj->type == HYPERBOLOID)
		res = ft_strjoin("Hyperboloid ", number);
	else if (obj->type == TORUS)
		res = ft_strjoin("Torus ", number);
	if ((int)(obj->emission.v4[0] + obj->emission.v4[1] + obj->emission.v4[2]))
	{
		buff = res;
		res = ft_strjoin("Light ", res);
		free(buff);
	}
	free(number);
	return (res);
}

static void	first_button(t_gui *gui, char *name_buff)
{
	gui->o_s.names[0] = name_buff;
	gui->o_s.rects[0] = &gui->o_s.buttonrect[0];
	KW_RectFillParentHorizontally(&gui->o_s.frect,
	gui->o_s.rects, gui->o_s.weights, 1, 15,
	KW_RECT_ALIGN_MIDDLE);
}

static int	scan_mass(t_gui *gui, t_obj *objs, int num)
{
	int		i;

	i = -1;
	while (++i < MAX_OBJ)
	{
		gui->o_s.buttons[i] = 0;
		gui->o_s.names[i] = 0;
	}
	gui->o_s.weights[0] = 1;
	gui->o_s.frect = (KW_Rect){WIN_W - 5 - FR_FZ, 25, FR_FZ, 80};
	gui->o_s.buttonrect[0] = (KW_Rect){0, 0, 30, 40};
	i = 1;
	first_button(gui, fill_name_mass(&objs[0], 0));
	while (i < num && i < MAX_OBJ)
	{
		gui->o_s.names[i] = fill_name_mass(&objs[i], i);
		gui->o_s.buttonrect[i] = gui->o_s.buttonrect[i - 1];
		gui->o_s.buttonrect[i].y += 45;
		if (i < WIN_H / 45 - 12)
			gui->o_s.frect.h += 45;
		i++;
	}
	return (i);
}

void		obj_select(t_gui *gui, t_obj *objs, int num)
{
	int					i;
	unsigned			test;
	KW_Widget *const	*wid_arr;

	gui->o_s.max_i = scan_mass(gui, objs, num);
	if ((i = -1) && gui->o_s.max_i > WIN_H / 45 - 12)
	{
		gui->o_s.frame = KW_CreateScrollbox(gui->gui, NULL, &gui->o_s.frect);
		wid_arr = KW_GetWidgetChildren(gui->o_s.frame, &test);
		KW_HideWidget(wid_arr[2]);
	}
	else
		gui->o_s.frame = KW_CreateFrame(gui->gui, NULL, &gui->o_s.frect);
	while (++i < gui->o_s.max_i)
	{
		if (gui->o_s.max_i > WIN_H / 45 - 12)
			gui->o_s.buttonrect[i].x -= 15;
		gui->o_s.buttons[i] = KW_CreateButtonAndLabel(gui->gui,
gui->o_s.frame, gui->o_s.names[i], &gui->o_s.buttonrect[i]);
		KW_AddWidgetMouseDownHandler(gui->o_s.buttons[i], obj_click);
		KW_SetWidgetUserData(gui->o_s.buttons[i], &objs[i]);
	}
}
