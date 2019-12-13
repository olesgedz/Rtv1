/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norma_from_cam_select.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 18:24:37 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/13 16:24:54 by lminta           ###   ########.fr       */
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

void		new_mask_push(t_gui *gui, t_cam *cam, int *i)
{
	cam->motion_blur = atof(KW_GetEditboxText(gui->c_c.ed_b[(*i)++]));
	free(gui->game->mask);
	gui->game->mask = create_blur_mask(cam->motion_blur, &cam->mask_size);
	gui->game->mask_size = cam->mask_size;
	clReleaseMemObject(gui->game->cl_info->progs[0].krls[0].args[12]);
	cl_krl_init_arg(&gui->game->cl_info->progs[0].krls[0], 12,
	sizeof(float) * (gui->game->mask_size * 2 + 1) *
	(gui->game->mask_size * 2 + 1), gui->game->mask);
	cl_krl_mem_create(gui->game->cl_info, &gui->game->cl_info->progs[0].krls[0],
	12, CL_MEM_READ_WRITE);
	cl_krl_set_arg(&gui->game->cl_info->progs[0].krls[0], 12);
	cl_write(gui->game->cl_info, gui->game->cl_info->progs[0].krls[0].
	args[12], sizeof(float) * (gui->game->mask_size * 2 + 1) *
	(gui->game->mask_size * 2 + 1), gui->game->mask);
}
