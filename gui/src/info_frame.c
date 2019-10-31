/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_frame.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:38:36 by lminta            #+#    #+#             */
/*   Updated: 2019/10/31 20:52:45 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		show_hide(t_game *game, t_gui *gui)
{
	game->keys.show_gui = !game->keys.show_gui;
	if (game->keys.show_gui)
	{
		KW_ShowWidget(gui->i_f.frame);
		KW_ShowWidget(gui->g_b.frame);
		gui->i_f.show = 1;
		gui->g_b.show = 1;
		if (gui->s_s.show)
			KW_ShowWidget(gui->s_s.frame);
		if (gui->o_s.show)
			KW_ShowWidget(gui->o_s.frame);
	}
	else
	{
		KW_HideWidget(gui->i_f.frame);
		KW_HideWidget(gui->g_b.frame);
		KW_HideWidget(gui->s_s.frame);
		KW_HideWidget(gui->o_s.frame);
	}
}

void		semples_to_line(t_game *game, t_gui *gui)
{
	char *buff;

	buff = ft_itoa(game->gpu.samples);
	free(gui->i_f.names);
	gui->i_f.names = ft_strjoin("Samples: ", buff);
	free(buff);
	if (!gui->i_f.label)
		gui->i_f.label = KW_CreateLabel(gui->gui, gui->i_f.frame,
	gui->i_f.names, &gui->i_f.titlerect);
	else
		KW_SetLabelText(gui->i_f.label, gui->i_f.names);
}

void		info_button(t_game *game, t_gui *gui)
{
	unsigned			test;

	gui->i_f.label = 0;
	gui->i_f.frect = (KW_Rect){10, WIN_H - 110, FR_FZ, 100};
	gui->i_f.titlerect = (KW_Rect){10, 10, FR_FZ - 20, 30};
	gui->i_f.frame = KW_CreateFrame(gui->gui, NULL, &gui->i_f.frect);
	semples_to_line(game, gui);
}
