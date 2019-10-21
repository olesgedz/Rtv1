/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 22:51:42 by lminta            #+#    #+#             */
/*   Updated: 2019/10/21 18:13:58 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ok_clicked(KW_Widget *widget, int b)
{
	t_gui	*gui;

	gui = g_gui(0, 0);
	widget = NULL;
	b = 0;
	gui->av = (char *)KW_GetEditboxText(gui->ed_w.editBox);
	gui->quit = KW_TRUE;
}

void		start_screen(t_gui *gui)
{
	gui->ed_w.backtex = load_picture(gui, "gui/res/start.bmp");
	gui->ed_w.frect = (KW_Rect){10, 10, 300, 220};
	KW_RectCenterInParent(&gui->ed_w.winrect, &gui->ed_w.frect);
	gui->ed_w.frame =
	KW_CreateFrame(gui->gui, NULL, &gui->ed_w.frect);
	gui->ed_w.titlerect = (KW_Rect){0, 10, 300, 30};
	gui->ed_w.labelrect = (KW_Rect){0, 100, 60, 30};
	gui->ed_w.editboxrect = (KW_Rect){0, 100, 100, 40};
	gui->ed_w.rects[0] = &gui->ed_w.labelrect;
	gui->ed_w.rects[1] = &gui->ed_w.editboxrect;
	gui->ed_w.weights[0] = 1;
	gui->ed_w.weights[1] = 4;
	KW_RectFillParentHorizontally(&gui->ed_w.frect,
	gui->ed_w.rects, gui->ed_w.weights, 2, 10, KW_RECT_ALIGN_MIDDLE);
	KW_CreateLabel(gui->gui, gui->ed_w.frame,
	"Enter the path to the scene", &gui->ed_w.titlerect);
	KW_CreateLabel(gui->gui, gui->ed_w.frame,
	"Path", &gui->ed_w.labelrect);
	gui->ed_w.editBox = KW_CreateEditbox(gui->gui,
	gui->ed_w.frame, "Edit me!", &gui->ed_w.editboxrect);
	gui->ed_w.buttonrect = (KW_Rect){250, 170, 40, 40};
	gui->ed_w.okbutton = KW_CreateButtonAndLabel(gui->gui,
	gui->ed_w.frame, "OK", &gui->ed_w.buttonrect);
	KW_AddWidgetMouseDownHandler(gui->ed_w.okbutton, ok_clicked);
}

char		*start_gui(t_gui *gui)
{
	init_kiwi(gui);
	start_screen(gui);
	scene_select(gui);
	loopa(gui);
	quit_kiwi(gui);
	return (gui->av);
}
