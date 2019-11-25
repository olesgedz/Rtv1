/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cameras.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:32:09 by lminta            #+#    #+#             */
/*   Updated: 2019/11/25 21:45:22 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cam_button(t_game *game, t_gui *gui)
{
	gui->g_b.buttonrect[5] = gui->g_b.buttonrect[3];
	gui->g_b.buttonrect[5].x += gui->g_b.buttonrect[5].w;
	gui->g_b.rects[5] = &gui->g_b.buttonrect[5];
	gui->g_b.buttons[5] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Cameras", gui->g_b.rects[5]);
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[5], 0);
	KW_SetWidgetUserData(gui->g_b.buttons[5], (void *)game);
}
