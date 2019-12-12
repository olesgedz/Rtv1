/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norma_from_cam_select.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:24:37 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 18:33:08 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KW_editbox_internal.h"
#include "KW_widget_internal.h"
#include "rt.h"

static void	norma_from_cam_select_rw(t_gui *gui, int *i)
{
	*i += 1;
	while (*i < 5)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->c_c.buttons[*i], 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->c_c.buttons[*i], 0);
		KW_RemoveWidgetMouseDownHandler(gui->c_c.buttons[*i], 0);
		*i += 1;
	}
}

static void	norma_from_cam_select_w_free(t_gui *gui, int i, KW_Editbox **edit)
{
	KW_RemoveWidgetMouseUpHandler(gui->c_c.ed_b[i], 0);
	KW_RemoveWidgetMouseOverHandler(gui->c_c.ed_b[i], 0);
	KW_RemoveWidgetMouseLeaveHandler(gui->c_c.ed_b[i], 0);
	KW_RemoveWidgetFocusGainHandler(gui->c_c.ed_b[i], 0);
	KW_RemoveWidgetFocusLoseHandler(gui->c_c.ed_b[i], 0);
	KW_RemoveWidgetKeyDownHandler(gui->c_c.ed_b[i], 0);
	KW_RemoveWidgetTextInputHandler(gui->c_c.ed_b[i], 0);
	KW_RemoveWidgetMouseDownHandler(gui->c_c.ed_b[i], 0);
	*edit = (KW_Editbox *)gui->c_c.ed_b[i]->privdata;
	KW_ReleaseTexture(gui->driver, (*edit)->textrender);
}

void		norma_from_cam_select(t_gui *gui, KW_Widget *widget, KW_Widget *wid)
{
	KW_Widget	*label;
	int			i;
	KW_Editbox	*edit;

	i = -1;
	norma_from_cam_select_rw(gui, &i);
	i = -1;
	while (gui->c_c.ed_b[++i] && i < 30)
		norma_from_cam_select_w_free(gui, i, &edit);
	KW_RemoveWidgetGeometryChangeHandler(gui->c_c.frame, 0);
	KW_RemoveWidgetTilesetChangeHandler(gui->c_c.frame, 0);
	KW_HideWidget(gui->c_c.frame);
	destr(gui, gui->c_c.frame);
	i = -1;
	while (++i < 30)
		gui->c_c.ed_b[i] = 0;
	gui->c_c.frame = 0;
	if (wid && widget)
	{
		label = KW_GetButtonLabel(wid);
		if (label)
			KW_SetLabelTextColor(label, (KW_Color){0, 0, 0, 255});
	}
	gui->c_c.show = 0;
}
