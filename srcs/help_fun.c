/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:11:26 by lminta            #+#    #+#             */
/*   Updated: 2019/11/22 14:17:11 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	check_gui_entrance(t_game *game, t_gui *gui, int x, int y)
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
	if (game->keys.show_gui && gui->c_o.show)
		if (x > gui->c_o.frect.x && x < gui->c_o.frect.x + gui->c_o.frect.w)
			if (y > gui->c_o.frect.y && y < gui->c_o.frect.y + gui->c_o.frect.h)
				gui->over_gui = 1;
	if (game->keys.show_gui && gui->o_t.show)
		if (x > gui->o_t.frect.x && x < gui->o_t.frect.x + gui->o_t.frect.w)
			if (y > gui->o_t.frect.y && y < gui->o_t.frect.y + gui->o_t.frect.h)
				gui->over_gui = 1;
}
