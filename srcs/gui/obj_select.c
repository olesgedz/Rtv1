/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 19:08:02 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 19:19:54 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	first_button(gui, fill_name_mass(&objs[0]));
	while (i < num && i < MAX_OBJ)
	{
		gui->o_s.names[i] = fill_name_mass(&objs[i]);
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
