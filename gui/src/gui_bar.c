/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_bar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:10:18 by lminta            #+#    #+#             */
/*   Updated: 2019/10/29 21:30:04 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		gui_bar(t_game *game, t_gui *gui)
{
	unsigned			test;
	int					fr_sz;

	gui->g_b.label = 0;
	fr_sz = WIN_W / 50.;
	gui->g_b.weights[0] = 1;
	gui->g_b.frect = (KW_Rect){0, 0, WIN_W, fr_sz};
	gui->g_b.frame = KW_CreateFrame(gui->gui, NULL, &gui->g_b.frect);
	buttons(game, gui, fr_sz);
	//KW_AddWidgetMouseDownHandler(gui->g_b.buttons, clicked);
	//KW_SetWidgetUserData(gui->g_b.buttons[0], (void *)game);
}
