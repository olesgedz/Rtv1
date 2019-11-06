/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ren_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:38:36 by lminta            #+#    #+#             */
/*   Updated: 2019/11/06 20:58:21 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ren_start(KW_Widget *widget, int b)
{
	t_game	*game;

	b = 0;
	game = KW_GetWidgetUserData(widget);
	if (game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	game->keys.r = !game->keys.r;
}

void		show_hide(t_game *game, t_gui *gui)
{
	game->keys.show_gui = !game->keys.show_gui;
	if (game->keys.show_gui)
	{
		KW_ShowWidget(gui->g_b.frame);
		gui->g_b.show = 1;
		if (gui->s_s.show)
			KW_ShowWidget(gui->s_s.frame);
		if (gui->o_s.show)
			KW_ShowWidget(gui->o_s.frame);
	}
	else
	{
		KW_HideWidget(gui->g_b.frame);
		KW_HideWidget(gui->s_s.frame);
		KW_HideWidget(gui->o_s.frame);
	}
}

void		semples_to_line(t_game *game, t_gui *gui)
{
	char *buff;
	char *fps;

	buff = ft_itoa(game->gpu.samples);
	free(gui->g_b.names[0]);
	gui->g_b.names[0] = ft_strjoin("Samples: ", buff);
	free(buff);
	buff = ft_strjoin(gui->g_b.names[0], "    FPS: ");
	free(gui->g_b.names[0]);
	fps = ft_itoa(gui->fps);
	gui->g_b.names[0] = ft_strjoin(buff, fps);
	free(buff);
	free(fps);
	KW_SetLabelText(gui->g_b.label, gui->g_b.names[0]);
}

void		info_button(t_game *game, t_gui *gui)
{
	gui->g_b.buttonrect[3] = gui->g_b.buttonrect[0];
	gui->g_b.buttonrect[3].x += gui->g_b.buttonrect[3].w;
	gui->g_b.rects[3] = &gui->g_b.buttonrect[3];
	gui->g_b.buttons[3] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Objects", gui->g_b.rects[3]);
	gui->g_b.label = KW_GetButtonLabel(gui->g_b.buttons[3]);
	semples_to_line(game, gui);
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[3], ren_start);
	KW_SetWidgetUserData(gui->g_b.buttons[3], (void *)game);
}
