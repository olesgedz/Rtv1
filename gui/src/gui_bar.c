/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_bar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:10:18 by lminta            #+#    #+#             */
/*   Updated: 2019/10/31 19:28:07 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		gui_bar(t_game *game, t_gui *gui)
{
	unsigned			test;

	gui->g_b.label = 0;
	gui->g_b.show = 1;
	gui->g_b.frect = (KW_Rect){0, 0, WIN_W, FR_FZ / 5.};
	gui->g_b.frame = KW_CreateFrame(gui->gui, NULL, &gui->g_b.frect);
	buttons(game, gui);
	//KW_AddWidgetMouseDownHandler(gui->g_b.buttons, clicked);
	//KW_SetWidgetUserData(gui->g_b.buttons[0], (void *)game);
}
