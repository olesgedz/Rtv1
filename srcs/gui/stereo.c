/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stereo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 17:58:24 by lminta            #+#    #+#             */
/*   Updated: 2019/12/04 22:40:54 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ddd_name(KW_Widget *widget, t_cam *cam)
{
	char		*buff;
	KW_Widget	*wid;

	wid = KW_GetButtonLabel(widget);
	if (cam->stereo)
		KW_SetLabelText(wid, "ON");
	else
		KW_SetLabelText(wid, "OFF");
}

void	ddd(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_cam		*cam;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	cam = KW_GetWidgetUserData(widget);
	cam->stereo = !cam->stereo;
	ddd_name(widget, cam);
}
