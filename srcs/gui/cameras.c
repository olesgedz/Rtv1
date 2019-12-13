/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cameras.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:32:09 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 16:23:26 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	clicked_cs(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_game		*game;

	game = KW_GetWidgetUserData(widget);
	if (game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	gui = g_gui(0, 0);
	gui->c_s.show = !gui->c_s.show;
	if (gui->c_s.show)
	{
		KW_ShowWidget(gui->c_s.frame);
		KW_SetLabelTextColor(KW_GetButtonLabel(widget),
		(KW_Color){255, 255, 255, 255});
	}
	else
	{
		KW_HideWidget(gui->c_s.frame);
		KW_SetLabelTextColor(KW_GetButtonLabel(widget),
		(KW_Color){0, 0, 0, 0});
	}
}

void		cam_button(t_game *game, t_gui *gui)
{
	gui->g_b.buttonrect[5] = gui->g_b.buttonrect[0];
	gui->g_b.buttonrect[5].x += gui->g_b.buttonrect[5].w;
	gui->g_b.rects[5] = &gui->g_b.buttonrect[5];
	gui->g_b.buttons[5] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Cameras", gui->g_b.rects[5]);
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[5], clicked_cs);
	KW_SetWidgetUserData(gui->g_b.buttons[5], (void *)game);
}

void		cam_rename(t_game *game, t_gui *gui, int num)
{
	KW_Widget	*label;
	char		*buff;

	label = KW_GetButtonLabel(gui->c_s.buttons[num]);
	buff = cam_mass_name(game, &game->gpu.camera[num]);
	KW_SetLabelText(label, buff);
	free(buff);
}

void		pars_cam_box(t_gui *gui, t_cam *cam)
{
	int		i;
	double	fov;

	i = 0;
	cam->position.s[0] = atof(KW_GetEditboxText(gui->c_c.ed_b[i++]));
	cam->position.s[1] = atof(KW_GetEditboxText(gui->c_c.ed_b[i++]));
	cam->position.s[2] = atof(KW_GetEditboxText(gui->c_c.ed_b[i++]));
	cam->direction.s[0] = atof(KW_GetEditboxText(gui->c_c.ed_b[i++]));
	cam->direction.s[1] = atof(KW_GetEditboxText(gui->c_c.ed_b[i++]));
	cam->direction.s[2] = atof(KW_GetEditboxText(gui->c_c.ed_b[i++]));
	cam->normal.s[0] = atof(KW_GetEditboxText(gui->c_c.ed_b[i++]));
	cam->normal.s[1] = atof(KW_GetEditboxText(gui->c_c.ed_b[i++]));
	cam->normal.s[2] = atof(KW_GetEditboxText(gui->c_c.ed_b[i++]));
	i += 6;
	fov = atof(KW_GetEditboxText(gui->c_c.ed_b[i++]));
	cam->fov = fov * M_PI / 180;
	cam->ambience = atof(KW_GetEditboxText(gui->c_c.ed_b[i++]));
	if (cam->motion_blur != atof(KW_GetEditboxText(gui->c_c.ed_b[i])))
		new_mask_push(gui, cam, &i);
}

void		cam_save_click(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_cam		*cam;

	b = 0;
	gui = g_gui(0, 0);
	cam = KW_GetWidgetUserData(widget);
	pars_cam_box(gui, cam);
	cam_rename(gui->game, gui, cam->id);
	gui->game->flag = 1;
}
