/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:08:02 by lminta            #+#    #+#             */
/*   Updated: 2019/09/25 18:18:25 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	clicked(KW_Widget *widget, int b)
{
	t_gui	*gui;
	t_obj	*obj;

	gui = g_gui(0, 0);
	obj = KW_GetWidgetUserData(widget);
	obj->is_visible = !obj->is_visible;
	gui->flag = 1;
}

static char	*fill_name(t_obj *obj, int num)
{
	char	*number;
	char	*res;
	char	*buff;

	number = ft_itoa(num);
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
	gui->o_s.buttonrect[0].y += 10;
}

static int	scan_mass(t_gui *gui, t_obj *objs, int num)
{
	int		i;

	i = 1;
	first_button(gui, fill_name(&objs[0], 0));
	while (i < num && i < MAX_OBJ)
	{
		gui->o_s.names[i] = fill_name(&objs[i], i);
		gui->o_s.buttonrect[i] = gui->o_s.buttonrect[i - 1];
		gui->o_s.buttonrect[i].y += 45;
		if (i < 21)
			gui->o_s.frect.h += 45;
		i++;
	}
	return (i);
}

void		obj_select(t_gui *gui, t_obj *objs, int num)
{
	int					i;
	int					max_i;
	int					fr_sz;
	unsigned			test;
	KW_Widget *const	*wid_arr;

	i = -1;
	gui->o_s.weights[0] = 1;
	fr_sz = WIN_W / 10.;
	gui->o_s.frect = (KW_Rect){WIN_W - 10 - fr_sz, 10, fr_sz, 100};
	gui->o_s.titlerect = (KW_Rect){10, 10, fr_sz - 20, 30};
	gui->o_s.buttonrect[0] = (KW_Rect){0, 0, 30, 40};
	max_i = scan_mass(gui, objs, num);
	if (max_i > 21)
	{
		gui->o_s.frame = KW_CreateScrollbox(gui->gui, NULL, &gui->o_s.frect);
		wid_arr = KW_GetWidgetChildren(gui->o_s.frame, &test);
		KW_AddWidgetMouseOverHandler(wid_arr[1], &over);
		KW_AddWidgetMouseLeaveHandler(wid_arr[1], &leave);
		KW_HideWidget(wid_arr[2]);
		gui->o_s.titlerect = (KW_Rect){0, 10, fr_sz - 30, 30};
	}
	else
		gui->o_s.frame = KW_CreateFrame(gui->gui, NULL, &gui->o_s.frect);
	KW_AddWidgetMouseOverHandler(gui->o_s.frame, &over);
	KW_AddWidgetMouseLeaveHandler(gui->o_s.frame, &leave);
	gui->o_s.label = KW_CreateLabel(gui->gui, gui->o_s.frame,
	"Objects in scene", &gui->o_s.titlerect);
	KW_AddWidgetMouseOverHandler(gui->o_s.label, &over);
	KW_AddWidgetMouseLeaveHandler(gui->o_s.label, &leave);
	while (++i < max_i)
	{
		if (max_i > 21)
		gui->o_s.buttonrect[i].x -= 15;
		gui->o_s.buttons[i] = KW_CreateButtonAndLabel(gui->gui,
gui->o_s.frame, gui->o_s.names[i], &gui->o_s.buttonrect[i]);
		KW_AddWidgetMouseDownHandler(gui->o_s.buttons[i], clicked);
		KW_SetWidgetUserData(gui->o_s.buttons[i], gui->o_s.names[i]);
		KW_AddWidgetMouseOverHandler(gui->o_s.buttons[i], &over);
		KW_AddWidgetMouseLeaveHandler(gui->o_s.buttons[i], &leave);
	}
}
