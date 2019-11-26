/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 21:38:08 by lminta            #+#    #+#             */
/*   Updated: 2019/11/26 21:53:41 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cart_name(KW_Widget *widget, t_cam *cam)
{
	char		*buff;
	KW_Widget	*wid;

	wid = KW_GetButtonLabel(widget);
	if (cam->cartoon)
		KW_SetLabelText(wid, "ON");
	else
		KW_SetLabelText(wid, "OFF");
}

void		sep_name(KW_Widget *widget, t_cam *cam)
{
	char		*buff;
	KW_Widget	*wid;

	wid = KW_GetButtonLabel(widget);
	if (cam->sepia)
		KW_SetLabelText(wid, "ON");
	else
		KW_SetLabelText(wid, "OFF");
}

void	cart(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_cam		*cam;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	cam = KW_GetWidgetUserData(widget);
	cam->cartoon = !cam->cartoon;
	cart_name(widget, cam);
	gui->game->flag = 1;
}

void	sep(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_cam		*cam;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	cam = KW_GetWidgetUserData(widget);
	cam->sepia = !cam->sepia;
	sep_name(widget, cam);
	gui->game->flag = 1;
}
