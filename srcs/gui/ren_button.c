/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ren_button.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:38:36 by lminta            #+#    #+#             */
/*   Updated: 2019/12/08 18:37:58 by lminta           ###   ########.fr       */
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
	else
	{
		KW_HideWidget(gui->g_b.frame);
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
}

Uint32		samples_to_line(t_game *game, t_gui *gui, Uint32 time0)
{
	char		*buff;
	char		fps[100];
	float		time;
	static int	frames = 1;

	buff = ft_itoa(game->gpu.samples);
	free(gui->g_b.names[0]);
	gui->g_b.names[0] = ft_strjoin("Samples: ", buff);
	free(buff);
	buff = ft_strjoin(gui->g_b.names[0], "    FPS: ");
	free(gui->g_b.names[0]);
	gcvt(gui->fps, 5, fps);
	gui->g_b.names[0] = ft_strjoin(buff, fps);
	free(buff);
	gui->g_b.label = KW_GetButtonLabel(gui->g_b.buttons[3]);
	KW_SetLabelText(gui->g_b.label, gui->g_b.names[0]);
	time = (SDL_GetTicks() - time0) / 1000.;
	if (time > 3)
	{
		gui->fps = frames / time;
		time0 = SDL_GetTicks();
		frames = 1;
	}
	frames++;
	return (time0);
}

void		info_button(t_game *game, t_gui *gui)
{
	gui->g_b.buttonrect[3] = gui->g_b.buttonrect[5];
	gui->g_b.buttonrect[3].x += 2 * gui->g_b.buttonrect[3].w;
	gui->g_b.rects[3] = &gui->g_b.buttonrect[3];
	gui->g_b.buttons[3] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Objects", gui->g_b.rects[3]);
	gui->g_b.label = KW_GetButtonLabel(gui->g_b.buttons[3]);
	samples_to_line(game, gui, SDL_GetTicks());
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[3], ren_start);
	KW_SetWidgetUserData(gui->g_b.buttons[3], (void *)game);
}
