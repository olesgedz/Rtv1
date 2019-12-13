/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_camera.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 17:19:57 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 19:28:35 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_cam	*new_cam(void)
{
	t_cam		*cam;

	cam = (t_cam *)malloc(sizeof(t_cam));
	cam->position = create_cfloat3(0, 0, 0);
	cam->direction = create_cfloat3(0, 0, 1);
	cam->normal = create_cfloat3(0, 1, 0);
	cam->ambience = 0.1;
	cam->cartoon = 0;
	cam->sepia = 0;
	cam->motion_blur = 0;
	cam->fov = M_PI / 3;
	cam->stereo = 0;
	reconfigure_camera(cam);
	return (cam);
}

static void		add_cam_click(KW_Widget *widget, int b)
{
	t_gui		*gui;

	b = 0;
	widget = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	ft_cam_push(gui->game, new_cam());
	cam_free(gui);
	cam_screen(gui, gui->game);
	cam_click(gui->c_s.buttons[gui->game->cam_quantity - 1], 0);
}

void			add_cam_button(t_gui *gui)
{
	int	i;

	i = gui->c_s.max_i - 1;
	if (gui->c_s.max_i > WIN_H / 45 - 12)
		gui->c_s.buttonrect[i].x -= 15;
	gui->c_s.buttons[i] = KW_CreateButtonAndLabel(gui->gui,
gui->c_s.frame, gui->c_s.names[i], &gui->c_s.buttonrect[i]);
	KW_AddWidgetMouseDownHandler(gui->c_s.buttons[i], add_cam_click);
}
