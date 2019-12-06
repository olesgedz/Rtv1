/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_obj.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/14 18:45:37 by lminta            #+#    #+#             */
/*   Updated: 2019/12/04 21:49:09 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	clicked_ot(KW_Widget *widget, int b)
{
	t_gui		*gui;
	t_game		*game;

	game = KW_GetWidgetUserData(widget);
	if (game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	gui = g_gui(0, 0);
	gui->o_t.show = !gui->o_t.show;
	if (gui->o_t.show)
		KW_ShowWidget(gui->o_t.frame);
	else
		KW_HideWidget(gui->o_t.frame);
}

static char	*fill_name(int num)
{
	char *res;

	if (num == SPHERE)
		res = ft_strdup("Sphere");
	else if (num == CYLINDER)
		res = ft_strdup("Cylinder");
	else if (num == CONE)
		res = ft_strdup("Cone");
	else if (num == PLANE)
		res = ft_strdup("Plane");
	else if (num == TRIANGLE)
		res = ft_strdup("Triangle");
	else if (num == TORUS)
		res = ft_strdup("Torus");
	else if (num == PARABOLOID)
		res = ft_strdup("Paraboloid");
	else if (num == 7)
		res = ft_strdup("Delete invisible");
	return (res);
}

static int	scan_mass(t_gui *gui)
{
	int		i;

	i = -1;
	gui->o_t.weights[0] = 1;
	gui->o_t.frect = (KW_Rect){WIN_W - 5 - FR_FZ - gui->g_b.buttonrect[4].w,
	25, FR_FZ, 80};
	gui->o_t.buttonrect[0] = (KW_Rect){0, 0, 30, 40};
	i = 1;
	gui->o_t.names[0] = fill_name(0);
	gui->o_t.rects[0] = &gui->o_t.buttonrect[0];
	KW_RectFillParentHorizontally(&gui->o_t.frect,
	gui->o_t.rects, gui->o_t.weights, 1, 15,
	KW_RECT_ALIGN_MIDDLE);
	while (i < 8)
	{
		gui->o_t.names[i] = fill_name(i);
		gui->o_t.buttonrect[i] = gui->o_t.buttonrect[i - 1];
		gui->o_t.buttonrect[i].y += 45;
		if (i < WIN_H / 45 - 3)
			gui->o_t.frect.h += 45;
		i++;
	}
	return (8);
}

void		obj_type(t_game *game, t_gui *gui)
{
	int					i;
	int					*mas;
	unsigned			test;
	KW_Widget *const	*wid_arr;

	mas = (int *)malloc(sizeof(int) * 8);
	gui->o_t.max_i = scan_mass(gui);
	if ((i = -1) && gui->o_t.max_i > WIN_H / 45 - 3)
	{
		gui->o_t.frame = KW_CreateScrollbox(gui->gui, NULL, &gui->o_t.frect);
		wid_arr = KW_GetWidgetChildren(gui->o_t.frame, &test);
		KW_HideWidget(wid_arr[2]);
	}
	else
		gui->o_t.frame = KW_CreateFrame(gui->gui, NULL, &gui->o_t.frect);
	while (++i < gui->o_t.max_i)
	{
		gui->o_t.buttons[i] = KW_CreateButtonAndLabel(gui->gui,
gui->o_t.frame, gui->o_t.names[i], &gui->o_t.buttonrect[i]);
		KW_AddWidgetMouseDownHandler(gui->o_t.buttons[i], click_create);
		*mas = i;
		KW_SetWidgetUserData(gui->o_t.buttons[i], mas++);
	}
}

void		add_obj(t_game *game, t_gui *gui)
{
	gui->g_b.buttonrect[4] = gui->g_b.buttonrect[1];
	gui->g_b.buttonrect[4].x -= gui->g_b.buttonrect[4].w;
	gui->g_b.rects[4] = &gui->g_b.buttonrect[4];
	gui->g_b.buttons[4] = KW_CreateButtonAndLabel(gui->gui,
	gui->g_b.frame, "Add object", gui->g_b.rects[4]);
	KW_AddWidgetMouseDownHandler(gui->g_b.buttons[4], &clicked_ot);
	KW_SetWidgetUserData(gui->g_b.buttons[4], (void *)game);
}
