/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:46:11 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 18:56:57 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cam_free(t_gui *gui)
{
	int i;

	i = -1;
	while (gui->c_s.names[++i] && i < MAX_OBJ)
		free(gui->c_s.names[i]);
	i = -1;
	while (gui->c_s.buttons[++i] && i < MAX_OBJ)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->c_s.buttons[i], 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->c_s.buttons[i], 0);
		KW_RemoveWidgetMouseDownHandler(gui->c_s.buttons[i], 0);
	}
	if (gui->c_s.max_i > 0)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->c_s.frame, 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->c_s.frame, 0);
		KW_HideWidget(gui->c_s.frame);
		destr(gui, gui->c_s.frame);
	}
	if (gui->c_s.max_i > WIN_H / 45 - 12)
		scroll_box_free(gui, gui->c_s.frame);
}

void		cam_screen(t_gui *gui, t_game *game)
{
	cam_select(gui, game->gpu.camera, game->cam_quantity);
	if (!gui->c_s.show)
		KW_HideWidget(gui->c_s.frame);
}

void		main_screen(t_gui *gui, t_game *game)
{
	obj_select(gui, game->gpu.objects, game->obj_quantity);
	if (!gui->o_s.show)
		KW_HideWidget(gui->o_s.frame);
}

void		main_screen_free(t_gui *gui)
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
		KW_HideWidget(gui->o_s.frame);
		destr(gui, gui->o_s.frame);
	}
	if (gui->o_s.max_i > WIN_H / 45 - 12)
		scroll_box_free(gui, gui->o_s.frame);
}

void		quit_kiwi_main(t_gui *gui)
{
	if (gui->s_s.max_i > WIN_H / 45 - 12)
		scroll_box_free(gui, gui->s_s.frame);
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
