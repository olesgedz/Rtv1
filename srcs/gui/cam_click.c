/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_click.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:09:46 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 17:10:51 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cam_click(KW_Widget *widget, int b)
{
	static t_cam		*cam = 0;
	static KW_Widget	*wid = 0;
	t_gui				*gui;
	KW_Widget			*label;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	if (gui->c_c.show == 1)
		norma_from_cam_select(gui, widget, wid);
	if (widget && (cam != KW_GetWidgetUserData(widget)))
	{
		cam = KW_GetWidgetUserData(widget);
		change_cam(gui, cam);
		wid = widget;
		KW_SetLabelTextColor(KW_GetButtonLabel(wid),
		(KW_Color){255, 255, 255, 255});
		gui->c_c.show = 1;
	}
	else
	{
		wid = 0;
		cam = 0;
	}
}
