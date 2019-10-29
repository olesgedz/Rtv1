/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buttons.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 21:08:05 by lminta            #+#    #+#             */
/*   Updated: 2019/10/29 21:10:36 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	buttons(t_game *game, t_gui *gui)
{
	gui->g_b.buttonrect[0] = (KW_Rect){5, 0, fr_sz * 5, 40};
	gui->g_b.rects[0] = &gui->g_b.buttonrect[0];
	KW_RectFillParentVertically(&gui->g_b.frect,
	gui->g_b.rects, gui->g_b.weights, 1, 5);
	gui->g_b.buttons[0] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Available Scenes", &gui->g_b.buttonrect[0]);
	gui->g_b.buttonrect[1] = (KW_Rect){WIN_W - fr_sz * 5 - 5, 0, fr_sz * 5, 40};
	gui->g_b.rects[0] = &gui->g_b.buttonrect[1];
	KW_RectFillParentVertically(&gui->g_b.frect,
	gui->g_b.rects, gui->g_b.weights, 1, 5);
	gui->g_b.buttons[1] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Objects in Scene", &gui->g_b.buttonrect[1]);
}
