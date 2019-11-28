/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 18:49:58 by lminta            #+#    #+#             */
/*   Updated: 2019/11/27 16:16:45 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			cam_border(t_gui *gui, t_cam *cam, int *i)
{
	gui->c_c.labelrect.y += 30;
	gui->c_c.editboxrect[0].y += 30;
	gui->c_c.editboxrect[1].y += 30;
	gui->c_c.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_c.frame, "Border X", gui->c_c.rects[0]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->border_x.s[0], gui->c_c.rects[1]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->border_x.s[1], gui->c_c.rects[2]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->border_x.s[2], gui->c_c.rects[3]);
	gui->c_c.labelrect.y += 30;
	gui->c_c.editboxrect[0].y += 30;
	gui->c_c.editboxrect[1].y += 30;
	gui->c_c.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_c.frame, "Border Y", gui->c_c.rects[0]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->border_y.s[0], gui->c_c.rects[1]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->border_y.s[1], gui->c_c.rects[2]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->border_y.s[2], gui->c_c.rects[3]);
}

void			cam_position(t_gui *gui, t_cam *cam, int *i)
{
	gui->c_c.labelrect.y += 30;
	gui->c_c.editboxrect[0].y += 30;
	gui->c_c.editboxrect[1].y += 30;
	gui->c_c.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_c.frame, "Position", gui->c_c.rects[0]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->position.s[0], gui->c_c.rects[1]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->position.s[1], gui->c_c.rects[2]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->position.s[2], gui->c_c.rects[3]);
	gui->c_c.labelrect.y += 30;
	gui->c_c.editboxrect[0].y += 30;
	gui->c_c.editboxrect[1].y += 30;
	gui->c_c.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_c.frame, "Direction", gui->c_c.rects[0]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->direction.s[0], gui->c_c.rects[1]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->direction.s[1], gui->c_c.rects[2]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->direction.s[2], gui->c_c.rects[3]);
	gui->c_c.labelrect.y += 30;
	gui->c_c.editboxrect[0].y += 30;
	gui->c_c.editboxrect[1].y += 30;
	gui->c_c.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_c.frame, "Normal", gui->c_c.rects[0]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->normal.s[0], gui->c_c.rects[1]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->normal.s[1], gui->c_c.rects[2]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->normal.s[2], gui->c_c.rects[3]);
}

void			cam_fov(t_gui *gui, t_cam *cam, int *i)
{
	gui->c_c.labelrect.y += 30;
	gui->c_c.editboxrect[0].y += 30;
	gui->c_c.editboxrect[1].y += 30;
	gui->c_c.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_c.frame, "FOV", gui->c_c.rects[0]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->fov, gui->c_c.rects[1]);
}

void			cam_amb_blur(t_gui *gui, t_cam *cam, int *i)
{
	gui->c_c.labelrect.y += 30;
	gui->c_c.editboxrect[0].y += 30;
	gui->c_c.editboxrect[1].y += 30;
	gui->c_c.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_c.frame, "Ambience", gui->c_c.rects[0]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->ambience, gui->c_c.rects[1]);
	KW_CreateLabel(gui->gui, gui->c_c.frame, "Motion blur", gui->c_c.rects[2]);
	gui->c_c.ed_b[(*i)++] = f_c(gui, cam->motion_blur, gui->c_c.rects[3]);
}

void			cam_eff(t_gui *gui, t_cam *cam, int *i)
{
	gui->c_c.labelrect.y += 30;
	gui->c_c.editboxrect[0].y += 30;
	gui->c_c.editboxrect[1].y += 30;
	gui->c_c.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_c.frame, "Cartoon", gui->c_c.rects[0]);
	gui->c_c.buttons[3] = KW_CreateButtonAndLabel(gui->gui,
	gui->c_c.frame, "test1", gui->c_c.rects[1]);
	cart_name(gui->c_c.buttons[3], cam);
	KW_AddWidgetMouseDownHandler(gui->c_c.buttons[3], cart);
	KW_SetWidgetUserData(gui->c_c.buttons[3], cam);
	KW_CreateLabel(gui->gui, gui->c_c.frame, "Sepia", gui->c_c.rects[2]);
	gui->c_c.buttons[4] = KW_CreateButtonAndLabel(gui->gui,
	gui->c_c.frame, "test2", gui->c_c.rects[3]);
	sep_name(gui->c_c.buttons[4], cam);
	KW_AddWidgetMouseDownHandler(gui->c_c.buttons[4], sep);
	KW_SetWidgetUserData(gui->c_c.buttons[4], cam);
}
