/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eff.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 21:38:08 by lminta            #+#    #+#             */
/*   Updated: 2019/12/14 18:46:07 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		del_cam_h(void)
{
	cam_free(g_gui(0, 0));
	cam_screen(g_gui(0, 0), g_gui(0, 0)->game);
	cam_click(0, 0);
}

void			del_cam(t_cam *cam, t_game *game)
{
	t_game	game_buff;
	t_cam	*buff;
	int		i;

	i = -1;
	if (game->cam_quantity <= 1)
		return ;
	game_buff.gpu.camera = 0;
	while (++i < game->cam_quantity)
		if (cam && cam != &game->gpu.camera[i])
		{
			buff = (t_cam *)malloc_exit(sizeof(t_cam));
			*buff = game->gpu.camera[i];
			ft_cam_push(&game_buff, buff);
		}
	free(game->gpu.camera);
	game->cam_quantity = game_buff.cam_quantity;
	game->gpu.camera = game_buff.gpu.camera;
	if (cam->id == game->cam_num)
	{
		game->cam_num = 0;
		game->flag = 1;
	}
	del_cam_h();
}

void			cart_name(KW_Widget *widget, t_cam *cam)
{
	KW_Widget	*wid;

	wid = KW_GetButtonLabel(widget);
	if (cam->cartoon)
		KW_SetLabelText(wid, "ON");
	else
		KW_SetLabelText(wid, "OFF");
}

void			sep_name(KW_Widget *widget, t_cam *cam)
{
	KW_Widget	*wid;

	wid = KW_GetButtonLabel(widget);
	if (cam->sepia)
		KW_SetLabelText(wid, "ON");
	else
		KW_SetLabelText(wid, "OFF");
}

void			cart(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_cam		*cam;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	cam = KW_GetWidgetUserData(widget);
	cam->cartoon = !cam->cartoon;
	cart_name(widget, cam);
}
