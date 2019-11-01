/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:46:11 by lminta            #+#    #+#             */
/*   Updated: 2019/11/01 15:54:58 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	main_screen(t_gui *gui, t_game *game)
{
	KW_HideWidget(gui->s_s.frame);
	obj_select(gui, game->gpu.objects, game->obj_quantity);
	KW_HideWidget(gui->o_s.frame);
}

void	main_screen_free(t_gui *gui)
{
	int i;

	i = -1;
	while (gui->o_s.names[++i] && i < MAX_OBJ)
		free(gui->o_s.names[i]);
	i = -1;
	while (gui->o_s.buttons[++i] && i < MAX_OBJ)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->o_s.buttons[i], 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->o_s.buttons[i], 0);
		KW_RemoveWidgetMouseDownHandler(gui->o_s.buttons[i], 0);
	}
	if (gui->o_s.max_i > 0)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->o_s.frame, 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->o_s.frame, 0);
		KW_DestroyWidget(gui->o_s.frame, 1);
	}
}

void	quit_kiwi_main(t_gui *gui)
{
	if (gui->s_s.max_i > 0)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->s_s.frame, 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->s_s.frame, 0);
		KW_DestroyWidget(gui->s_s.frame, 1);
	}
	free(gui->g_b.names[0]);
	KW_ReleaseSurface(gui->driver, gui->set);
	KW_Quit(gui->gui);
}
