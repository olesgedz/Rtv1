/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_screen.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 22:51:42 by lminta            #+#    #+#             */
/*   Updated: 2019/10/22 20:08:47 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	ok_clicked(KW_Widget *widget, int b)
{
	t_gui	*gui;

	b = 0;
	widget = 0;
	gui = g_gui(0, 0);
	gui->av = ft_strdup((char *)KW_GetEditboxText(gui->ed_w.edit_box));
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
	gui->ed_w.edit_box = KW_CreateEditbox(gui->gui,
	gui->ed_w.frame, "Edit me!", &gui->ed_w.editboxrect);
	gui->ed_w.buttonrect = (KW_Rect){250, 170, 40, 40};
	gui->ed_w.okbutton = KW_CreateButtonAndLabel(gui->gui,
	gui->ed_w.frame, "OK", &gui->ed_w.buttonrect);
	KW_AddWidgetMouseDownHandler(gui->ed_w.okbutton, ok_clicked);
}

/*
**	KW_RemoveWidgetGeometryChangeHandler(gui->ed_w.frame, 0);
**	KW_RemoveWidgetTilesetChangeHandler(gui->ed_w.frame, 0);
**	KW_DestroyWidget(gui->ed_w.frame, 1);
*/

char		*start_gui(t_gui *gui)
{
	start_screen(gui);
	scene_select(gui, -1, 0);
	loopa(gui);
	SDL_DestroyTexture(gui->ed_w.backtex);
	KW_HideWidget(gui->ed_w.frame);
	return (gui->av);
}
