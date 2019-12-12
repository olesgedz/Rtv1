/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_gui_entrance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 20:43:52 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/10 20:47:22 by jblack-b         ###   ########.fr       */
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
	if (game->keys.show_gui && gui->n.show)
		if (x > gui->n.frect.x && x < gui->n.frect.x + gui->n.frect.w)
			if (y > gui->n.frect.y && y < gui->n.frect.y + gui->n.frect.h)
				gui->over_gui = 1;
	if (game->keys.show_gui && gui->ed_w.show)
		if (x > gui->ed_w.frect.x && x < gui->ed_w.frect.x
		+ gui->ed_w.frect.w)
			if (y > gui->ed_w.frect.y && y < gui->ed_w.frect.y
			+ gui->ed_w.frect.h)
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
