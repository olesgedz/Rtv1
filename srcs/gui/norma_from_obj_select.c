/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norma_from_obj_select.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:46:49 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 18:23:47 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "KW_editbox_internal.h"
#include "KW_widget_internal.h"

static void		norma_from_obj_select_free(t_gui *gui, int i, KW_Editbox **edit)
{
	KW_RemoveWidgetMouseUpHandler(gui->c_o.ed_b[i], 0);
	KW_RemoveWidgetMouseOverHandler(gui->c_o.ed_b[i], 0);
	KW_RemoveWidgetMouseLeaveHandler(gui->c_o.ed_b[i], 0);
	KW_RemoveWidgetFocusGainHandler(gui->c_o.ed_b[i], 0);
	KW_RemoveWidgetFocusLoseHandler(gui->c_o.ed_b[i], 0);
	KW_RemoveWidgetKeyDownHandler(gui->c_o.ed_b[i], 0);
	KW_RemoveWidgetTextInputHandler(gui->c_o.ed_b[i], 0);
	KW_RemoveWidgetMouseDownHandler(gui->c_o.ed_b[i], 0);
	*edit = (KW_Editbox *)gui->c_o.ed_b[i]->privdata;
	KW_ReleaseTexture(gui->driver, (*edit)->textrender);
}

static void		norma_from_obj_handlers(t_gui *gui)
{
	KW_RemoveWidgetGeometryChangeHandler(gui->c_o.frame, 0);
	KW_RemoveWidgetTilesetChangeHandler(gui->c_o.frame, 0);
	KW_HideWidget(gui->c_o.frame);
	destr(gui, gui->c_o.frame);
}

static void		norma_from_obj_r_w(t_gui *gui, int i)
{
	KW_RemoveWidgetGeometryChangeHandler(gui->c_o.buttons[i], 0);
	KW_RemoveWidgetTilesetChangeHandler(gui->c_o.buttons[i], 0);
	KW_RemoveWidgetMouseDownHandler(gui->c_o.buttons[i], 0);
}

void			norma_from_obj_select(t_gui *gui,\
KW_Widget *widget, KW_Widget *wid)
{
	KW_Widget	*label;
	int			i;
	KW_Editbox	*edit;

	i = -1;
	while (++i < 3)
		norma_from_obj_r_w(gui, i);
	i = -1;
	while (gui->c_o.ed_b[++i] && i < 30)
		norma_from_obj_select_free(gui, i, &edit);
	norma_from_obj_handlers(gui);
	i = -1;
	while (++i < 30)
		gui->c_o.ed_b[i] = 0;
	gui->c_o.frame = 0;
	if (wid && widget)
	{
		label = KW_GetButtonLabel(wid);
		if (label)
			KW_SetLabelTextColor(label, (KW_Color){0, 0, 0, 255});
	}
	gui->c_o.show = 0;
}
