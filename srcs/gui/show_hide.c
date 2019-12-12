/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_hide.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:25:34 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 17:44:20 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		show_gui(t_game *game, t_gui *gui)
{
	KW_ShowWidget(gui->g_b.frame);
	gui->g_b.show = 1;
	if (gui->s_s.show)
		KW_ShowWidget(gui->s_s.frame);
	if (gui->o_t.show)
		KW_ShowWidget(gui->o_t.frame);
	if (gui->o_s.show)
		KW_ShowWidget(gui->o_s.frame);
	if (gui->c_s.show)
		KW_ShowWidget(gui->c_s.frame);
	if (gui->c_o.show)
		KW_ShowWidget(gui->c_o.frame);
	if (gui->c_c.show)
		KW_ShowWidget(gui->c_c.frame);
	if (gui->n.show)
		KW_ShowWidget(gui->n.frame);
	if (gui->ed_w.show)
		KW_ShowWidget(gui->ed_w.frame);
}

static void		hide_gui(t_game *game, t_gui *gui)
{
	KW_HideWidget(gui->g_b.frame);
	gui->g_b.show = 0;
	KW_HideWidget(gui->s_s.frame);
	KW_HideWidget(gui->o_s.frame);
	KW_HideWidget(gui->o_t.frame);
	KW_HideWidget(gui->c_s.frame);
	KW_HideWidget(gui->n.frame);
	KW_HideWidget(gui->ed_w.frame);
	if (gui->c_o.frame)
		KW_HideWidget(gui->c_o.frame);
	if (gui->c_c.frame)
		KW_HideWidget(gui->c_c.frame);
}

void			show_hide(t_game *game, t_gui *gui)
{
	game->keys.show_gui = !game->keys.show_gui;
	if (game->keys.show_gui)
		show_gui(game, gui);
	else
		hide_gui(game, gui);
}
