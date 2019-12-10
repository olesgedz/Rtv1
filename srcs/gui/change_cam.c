/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:24:43 by lminta            #+#    #+#             */
/*   Updated: 2019/12/10 21:53:22 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		move_eb(t_gui *gui)
{
	gui->c_c.labelrect = (KW_Rect){5, 5, 1, 30};
	gui->c_c.editboxrect[0] = (KW_Rect){5, 5, 1, 30};
	gui->c_c.editboxrect[1] = (KW_Rect){5, 5, 1, 30};
	gui->c_c.editboxrect[2] = (KW_Rect){5, 5, 1, 30};
	gui->c_c.weights[0] = 1;
	gui->c_c.weights[1] = 1;
	gui->c_c.weights[2] = 1;
	gui->c_c.weights[3] = 1;
	KW_RectFillParentHorizontally(&gui->c_c.frect, gui->c_c.rects,
	gui->c_c.weights, 4, 10, KW_RECT_ALIGN_MIDDLE);
	gui->c_c.labelrect.y -= 215;
	gui->c_c.editboxrect[0].y -= 215;
	gui->c_c.editboxrect[1].y -= 215;
	gui->c_c.editboxrect[2].y -= 215;
}

static char		*cam_name(t_cam *cam)
{
	char	*number;
	char	*res;

	number = ft_itoa(cam->id);
	res = ft_strjoin("Camera ", number);
	free(number);
	return (res);
}

static void		cam_same(t_gui *gui, t_cam *cam)
{
	char	*buff;

	gui->c_c.frect = (KW_Rect){0, WIN_H - FR_ZF * 5 + 60, FR_FZ * 5 / 2,
	FR_ZF * 5 - 60};
	gui->c_c.frame =
	KW_CreateFrame(gui->gui, NULL, &gui->c_c.frect);
	gui->c_c.labelrect = (KW_Rect){5, 5, 100, 30};
	KW_RectHorizontallyCenterInParent(&gui->c_c.frect, &gui->c_c.labelrect);
	buff = cam_name(cam);
	KW_CreateLabel(gui->gui, gui->c_c.frame, buff, &gui->c_c.labelrect);
	free(buff);
	gui->c_c.buttonrect[0] = (KW_Rect){5, gui->c_c.frect.h - 45, FR_FZ, 40};
	gui->c_c.buttons[0] = KW_CreateButtonAndLabel(gui->gui,
	gui->c_c.frame, "Take control", &gui->c_c.buttonrect[0]);
	KW_AddWidgetMouseDownHandler(gui->c_c.buttons[0], take_cam);
	KW_SetWidgetUserData(gui->c_c.buttons[0], cam);
	cam_savebutton(gui, cam);
	cam_delbutton(gui, cam);
	gui->c_c.rects[0] = &gui->c_c.labelrect;
	gui->c_c.rects[1] = &gui->c_c.editboxrect[0];
	gui->c_c.rects[2] = &gui->c_c.editboxrect[1];
	gui->c_c.rects[3] = &gui->c_c.editboxrect[2];
	move_eb(gui);
}

KW_Widget		*f_c(t_gui *gui, double db, KW_Rect *rect)
{
	KW_Widget	*result;
	char		str[100];

	gcvt(db, 5, str);
	result = KW_CreateEditbox(gui->gui, gui->c_c.frame, str, rect);
	return (result);
}

void			change_cam(t_gui *gui, t_cam *cam)
{
	int i;

	i = 0;
	gui->c_c.cam_id = cam->id;
	cam_same(gui, cam);
	cam_position(gui, cam, &i);
	cam_border(gui, cam, &i);
	cam_fov(gui, cam, &i);
	cam_amb_blur(gui, cam, &i);
	cam_eff(gui, cam, &i);
}
