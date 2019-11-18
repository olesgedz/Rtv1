/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smsht.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 19:27:34 by lminta            #+#    #+#             */
/*   Updated: 2019/11/18 21:23:41 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	obj_if(t_gui *gui, t_obj *obj)
{
	if (obj->type == PLANE)
			change_plane(gui, obj);
	else if (obj->type == CONE)
			change_cone(gui, obj);
	else if (obj->type == CYLINDER)
			change_cylin(gui, obj);
	else if (obj->type == SPHERE)
			change_sphere(gui, obj);
	else if (obj->type == TRIANGLE)
			change_trian(gui, obj);
}

void	visibility_name(KW_Widget *widget, t_obj *obj)
{
	char		*buff;
	KW_Widget	*wid;

	wid = KW_GetButtonLabel(widget);
	if (obj->is_visible)
		KW_SetLabelText(wid, "Object is visible");
	else
		KW_SetLabelText(wid, "Object is invisible");
}

void	obj_same(t_gui *gui, t_obj *obj)
{
	char	*buff;

	gui->c_o.frect = (KW_Rect){0, WIN_H - FR_ZF * 5, FR_FZ * 5, FR_ZF * 5};
	gui->c_o.frame =
	KW_CreateFrame(gui->gui, NULL, &gui->c_o.frect);
	gui->c_o.labelrect = (KW_Rect){5, 5, 100, 30};
	KW_RectHorizontallyCenterInParent(&gui->c_o.frect, &gui->c_o.labelrect);
	buff = fill_name_mass(obj, 0);
	KW_CreateLabel(gui->gui, gui->c_o.frame,
	buff, &gui->c_o.labelrect);
	free(buff);
	gui->c_o.buttonrect[0] = (KW_Rect){5, gui->c_o.frect.h - 45, FR_FZ, 40};
	gui->c_o.buttons[0] = KW_CreateButtonAndLabel(gui->gui,
	gui->c_o.frame, "tmp", &gui->c_o.buttonrect[0]);
	visibility_name(gui->c_o.buttons[0], obj);
	KW_AddWidgetMouseDownHandler(gui->c_o.buttons[0], visibility);
	KW_SetWidgetUserData(gui->c_o.buttons[0], obj);
}
