/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_click.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:32:32 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 17:32:58 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		scene_click(KW_Widget *widget, int b)
{
	t_gui				*gui;
	char				*name;
	static KW_Widget	*wid = 0;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->main_screen)
		if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
			return ;
	if (!widget)
	{
		wid = 0;
		return ;
	}
	name = KW_GetWidgetUserData(widget);
	free(gui->av);
	gui->av = ft_strjoin("scenes/", name);
	gui->quit = 1;
	if (wid)
		KW_SetLabelTextColor(KW_GetButtonLabel(wid), (KW_Color){0, 0, 0, 255});
	wid = widget;
	KW_SetLabelTextColor(KW_GetButtonLabel(widget),
	(KW_Color){255, 255, 255, 255});
	obj_click(0, 0);
	cam_click(0, 0);
}
