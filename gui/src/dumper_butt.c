/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_butt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 14:51:12 by lminta            #+#    #+#             */
/*   Updated: 2019/12/05 17:13:04 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

FILE	*newfile(void)
{
	FILE	*fp;
	char	*buff;
	char	*name;
	int		i;

	i = 1;
	name = ft_strdup("scenes/dump_0.json");
	while ((fp = fopen(name, "r")))
	{
		buff = ft_itoa(i);
		free(name);
		name = ft_strjoin("scenes/dump_", buff);
		free(buff);
		buff = ft_strjoin(name, ".json");
		free(name);
		i++;
		fclose(fp);
		name = buff;
	}
	fp = fopen(name, "w+");
	return (fp);
}

void	dumper(t_game *game)
{
	FILE	*fp;

	fp = newfile();
	fprintf(fp, "{\n");
	dump_scene(game, fp);
	dump_obj(game, fp);
	dump_cam(game, fp);
	fprintf(fp, "}\n");
	fclose(fp);
}

static void	clicked_dump(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_game		*game;

	game = KW_GetWidgetUserData(widget);
	if (game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	gui = g_gui(0, 0);
	dumper(game);
	ss_free(gui);
	scene_select(gui, -1, 0);
	if (!gui->s_s.show)
		KW_HideWidget(gui->s_s.frame);
}

void		dumper_butt(t_game *game, t_gui *gui)
{
	gui->g_b.buttonrect[7] = gui->g_b.buttonrect[2];
	gui->g_b.buttonrect[7].x -= gui->g_b.buttonrect[7].w;
	gui->g_b.rects[7] = &gui->g_b.buttonrect[7];
	gui->g_b.buttons[7] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Dump map", gui->g_b.rects[7]);
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[7], clicked_dump);
	KW_SetWidgetUserData(gui->g_b.buttons[7], (void *)game);
}
