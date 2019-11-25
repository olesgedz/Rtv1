/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 21:38:25 by lminta            #+#    #+#             */
/*   Updated: 2019/11/25 16:47:07 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	delbutton(t_gui *gui, t_obj *obj)
{
	gui->c_o.buttonrect[2] = gui->c_o.buttonrect[0];
	gui->c_o.buttonrect[2].x += 2.5 + gui->c_o.buttonrect[0].w;
	gui->c_o.buttonrect[2].w = gui->c_o.buttonrect[1].x -
	gui->c_o.buttonrect[2].x - 2.5;
	gui->c_o.buttons[2] = KW_CreateButtonAndLabel(gui->gui,
	gui->c_o.frame, "Delete", &gui->c_o.buttonrect[2]);
	KW_AddWidgetMouseDownHandler(gui->c_o.buttons[2], del_click);
	KW_SetWidgetUserData(gui->c_o.buttons[2], obj);
}

void	del_obj(t_obj *obj, t_game *game)
{
	t_game	game_buff;
	t_obj	*buff;
	int		i;

	i = -1;
	game_buff.gpu.objects = 0;
	while (++i < game->obj_quantity)
		if ((obj && obj != &game->gpu.objects[i]) ||
		(!obj && game->gpu.objects[i].is_visible))
		{
			buff = (t_obj *)malloc(sizeof(t_obj));
			*buff = game->gpu.objects[i];
			ft_object_push(&game_buff, buff);
		}
	free(game->gpu.objects);
	game->obj_quantity = game_buff.obj_quantity;
	game->gpu.objects = game_buff.gpu.objects;
	in_cl(game);
}
