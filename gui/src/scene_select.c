/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:30:29 by lminta            #+#    #+#             */
/*   Updated: 2019/09/16 18:37:56 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <dirent.h>

static void	clicked(KW_Widget *widget, int b)
{
	t_game	*game;
	char	*name;

	game = g_game(0, 0);
	name = KW_GetWidgetUserData(widget);
	game->av = ft_strjoin("scenes/", name);
	game->quit = 1;
}

static void	first_button(t_game *game, struct dirent	*name_buff)
{
	game->gui.s_s.names[0] = name_buff->d_name;
	game->gui.s_s.rects[0] = &game->gui.s_s.buttonrect[0];
	KW_RectFillParentHorizontally(&game->gui.ed_w.framerect,
	game->gui.s_s.rects, game->gui.s_s.weights, 1, 10,
	KW_RECT_ALIGN_MIDDLE);
	game->gui.s_s.buttonrect[0].y -= 45;
}

static int	scan_dir(t_game *game)
{
	DIR				*res;
	struct dirent	*name_buff;
	int				i;

	i = 1;
	if (!(res = opendir("scenes")))
		return (-1);
	name_buff = readdir(res);
	while (name_buff && name_buff->d_type != 8)
		name_buff = readdir(res);
	if (name_buff->d_type == 8)
		first_button(game, name_buff);
	else
		return (-1);
	while ((name_buff = readdir(res)) && i < MAX_SC)
	{
		game->gui.s_s.names[i] = name_buff->d_name;
		game->gui.s_s.buttonrect[i] = game->gui.s_s.buttonrect[i - 1];
		game->gui.s_s.buttonrect[i].y += 45;
		game->gui.s_s.framerect.h += 45;
		i++;
	}
	return (i);
}

void		scene_select(t_game *game)
{
	int		i;
	int		max_i;

	i = -1;
	game->gui.s_s.weights[0] = 1;
	game->gui.s_s.framerect = (KW_Rect){10, 10, 300, 100};
	game->gui.s_s.titlerect = (KW_Rect){0, 10, 300, 30};
	game->gui.s_s.buttonrect[0] = (KW_Rect){0, 0, 30, 40};
	if ((max_i = scan_dir(game)) == -1)
		return ;
	game->gui.s_s.frame =
	KW_CreateFrame(game->gui.gui, NULL, &game->gui.s_s.framerect);
	KW_CreateLabel(game->gui.gui, game->gui.s_s.frame,
	"Availible scenes", &game->gui.s_s.titlerect);
	while (++i < max_i)
		game->gui.s_s.buttons[i] = KW_CreateButtonAndLabel(game->gui.gui,
game->gui.s_s.frame, game->gui.s_s.names[i], &game->gui.s_s.buttonrect[i]);
	i = -1;
	while (++i < max_i)
	{
		KW_AddWidgetMouseDownHandler(game->gui.s_s.buttons[i], clicked);
		KW_SetWidgetUserData(game->gui.s_s.buttons[i], game->gui.s_s.names[i]);
	}
}
