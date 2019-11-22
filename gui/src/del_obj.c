/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 21:38:25 by lminta            #+#    #+#             */
/*   Updated: 2019/11/22 22:10:55 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	delbutton(t_gui *gui, t_obj *obj)
{
	gui->c_o.buttonrect[2].x = gui->c_o.buttonrect[0] + ;
	gui->c_o.buttonrect[2].x = gui->c_o.buttonrect[1].x + gui->c_o.frect.w -
	gui->c_o.buttonrect[2].w - 10;
	gui->c_o.buttons[1] = KW_CreateButtonAndLabel(gui->gui,
	gui->c_o.frame, "Delete", &gui->c_o.buttonrect[1]);
	KW_AddWidgetMouseDownHandler(gui->c_o.buttons[1], save_click);
	KW_SetWidgetUserData(gui->c_o.buttons[1], obj);
}

void	del_obj(t_obj *obj, t_game *game)
{
	t_game	game_buff;
	int		i;

	i = -1;
	game_buff.gpu.objects = 0;
	while (++i < game->obj_quantity)
		if ((obj && obj != &game->gpu.objects[i]) ||
		(!obj && game->gpu.objects[i].is_visible))
			ft_object_push(&game_buff, &game->gpu.objects[i]);
	game->obj_quantity = game_buff.obj_quantity;
	game->gpu.objects = game_buff.gpu.objects;
	in_cl(game);
}
