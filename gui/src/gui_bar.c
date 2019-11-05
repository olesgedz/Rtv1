/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui_bar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 19:10:18 by lminta            #+#    #+#             */
/*   Updated: 2019/11/05 14:05:45 by lminta           ###   ########.fr       */
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
}
