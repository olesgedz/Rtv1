/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:11:26 by lminta            #+#    #+#             */
/*   Updated: 2019/12/01 19:14:34 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	check_change_windows(t_game *game, t_gui *gui, int x, int y)
{
	if (game->keys.show_gui && gui->c_o.show)
		if (x > gui->c_o.frect.x && x < gui->c_o.frect.x + gui->c_o.frect.w)
			if (y > gui->c_o.frect.y && y < gui->c_o.frect.y + gui->c_o.frect.h)
				gui->over_gui = 1;
	if (game->keys.show_gui && gui->c_c.show)
		if (x > gui->c_c.frect.x && x < gui->c_c.frect.x + gui->c_c.frect.w)
			if (y > gui->c_c.frect.y && y < gui->c_c.frect.y + gui->c_c.frect.h)
				gui->over_gui = 1;
}

void		check_gui_entrance(t_game *game, t_gui *gui, int x, int y)
{
	if (game->keys.show_gui && gui->s_s.show)
		if (x > gui->s_s.frect.x && x < gui->s_s.frect.x + gui->s_s.frect.w)
			if (y > gui->s_s.frect.y && y < gui->s_s.frect.y + gui->s_s.frect.h)
				gui->over_gui = 1;
	if (game->keys.show_gui && gui->o_s.show)
		if (x > gui->o_s.frect.x && x < gui->o_s.frect.x + gui->o_s.frect.w)
			if (y > gui->o_s.frect.y && y < gui->o_s.frect.y + gui->o_s.frect.h)
				gui->over_gui = 1;
	if (game->keys.show_gui && gui->g_b.show)
		if (x > gui->g_b.frect.x && x < gui->g_b.frect.x + gui->g_b.frect.w)
			if (y > gui->g_b.frect.y && y < gui->g_b.frect.y + gui->g_b.frect.h)
				gui->over_gui = 1;
	if (game->keys.show_gui && gui->o_t.show)
		if (x > gui->o_t.frect.x && x < gui->o_t.frect.x + gui->o_t.frect.w)
			if (y > gui->o_t.frect.y && y < gui->o_t.frect.y + gui->o_t.frect.h)
				gui->over_gui = 1;
	if (game->keys.show_gui && gui->c_s.show)
		if (x > gui->c_s.frect.x && x < gui->c_s.frect.x + gui->c_s.frect.w)
			if (y > gui->c_s.frect.y && y < gui->c_s.frect.y + gui->c_s.frect.h)
				gui->over_gui = 1;
	check_change_windows(game, gui, x, y);
}

void		check_ed_box_focus(t_game *game, t_gui *gui, int x, int y)
{
	KW_Rect	frect;
	KW_Rect	win;
	int		i;

	i = -1;
	while (gui->c_o.ed_b[++i] && i < 30)
	{
		KW_GetWidgetGeometry(gui->c_o.ed_b[i], &frect);
		frect.x += gui->c_o.frect.x;
		frect.y += gui->c_o.frect.y;
		if (x > frect.x && x < frect.x + frect.w)
			if (y > frect.y && y < frect.y + frect.h)
			{
				game->keys.ed_box = 1;
				return ;
			}
	}
	i = -1;
	while (gui->c_c.ed_b[++i] && i < 30)
	{
		KW_GetWidgetGeometry(gui->c_c.ed_b[i], &frect);
		frect.x += gui->c_c.frect.x;
		frect.y += gui->c_c.frect.y;
		if (x > frect.x && x < frect.x + frect.w)
			if (y > frect.y && y < frect.y + frect.h)
			{
				game->keys.ed_box = 1;
				return ;
			}
	}
	KW_SetFocusedWidget(gui->g_b.frame);
	game->keys.ed_box = 0;
}
