/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_fun.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 14:11:26 by lminta            #+#    #+#             */
/*   Updated: 2019/12/12 18:20:19 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static int		check_ed_box_focus_c_o(t_game *game,\
t_gui *gui, t_point *p, KW_Rect *frect)
{
	int i;

	i = -1;
	while (gui->c_o.show && gui->c_o.ed_b[++i] && i < 30)
	{
		KW_GetWidgetGeometry(gui->c_o.ed_b[i], frect);
		frect->x += gui->c_o.frect.x;
		frect->y += gui->c_o.frect.y;
		if (p->x > frect->x && p->x < frect->x + frect->w)
			if (p->y > frect->y && p->y < frect->y + frect->h)
			{
				game->keys.ed_box = 1;
				return (1);
			}
	}
	return (0);
}

static int		check_ed_box_focus_ed_b(t_game *game,\
t_gui *gui, t_point *p, KW_Rect *frect)
{
	int i;

	i = -1;
	while (gui->c_c.show && gui->c_c.ed_b[++i] && i < 30)
	{
		KW_GetWidgetGeometry(gui->c_c.ed_b[i], frect);
		frect->x += gui->c_c.frect.x;
		frect->y += gui->c_c.frect.y;
		if (p->x > frect->x && p->x < frect->x + frect->w)
			if (p->y > frect->y && p->y < frect->y + frect->h)
			{
				game->keys.ed_box = 1;
				return (1);
			}
	}
	return (0);
}

static int		check_ed_box_focus_ed_w(t_game *game,\
t_gui *gui, t_point *p, KW_Rect *frect)
{
	if (gui->ed_w.show)
	{
		KW_GetWidgetGeometry(gui->ed_w.ed_b, frect);
		frect->x += gui->ed_w.frect.x;
		frect->y += gui->ed_w.frect.y;
		if (p->x > frect->x && p->x < frect->x + frect->w)
			if (p->y > frect->y && p->y < frect->y + frect->h)
			{
				game->keys.ed_box = 1;
				return (1);
			}
	}
	return (0);
}

void			check_ed_box_focus(t_game *game, t_gui *gui, int x, int y)
{
	KW_Rect	frect;
	KW_Rect	win;
	int		i;
	t_point p;

	p.x = x;
	p.y = y;
	if (check_ed_box_focus_c_o(game, gui, &p, &frect))
		return ;
	if (check_ed_box_focus_ed_b(game, gui, &p, &frect))
		return ;
	if (check_ed_box_focus_ed_w(game, gui, &p, &frect))
		return ;
	KW_SetFocusedWidget(gui->g_b.frame);
	game->keys.ed_box = 0;
}
