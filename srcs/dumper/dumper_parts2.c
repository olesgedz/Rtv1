/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_parts2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 16:13:54 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 19:00:59 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KW_scrollbox_internal.h"
#include "KW_widget_internal.h"
#include "rt.h"

void		basis_print(t_obj *obj, FILE *fp)
{
	if (obj->type == TORUS)
		fprintf(fp, "            \"tor_radius\": %.3f,\n", obj->tor_radius);
	if (!isnan(obj->v.s[0]))
		fprintf(fp, "            \"dir\": [%.3f, %.3f, %.3f],\n",
		obj->v.s[0], obj->v.s[1], obj->v.s[2]);
	fprintf(fp, "            \"x_basis\": [%.3f, %.3f, %.3f],\n",
	obj->basis[0].s[0], obj->basis[0].s[1], obj->basis[0].s[2]);
	fprintf(fp, "            \"y_basis\": [%.3f, %.3f, %.3f],\n",
	obj->basis[1].s[0], obj->basis[1].s[1], obj->basis[1].s[2]);
	fprintf(fp, "            \"z_basis\": [%.3f, %.3f, %.3f]\n",
	obj->basis[2].s[0], obj->basis[2].s[1], obj->basis[2].s[2]);
}

void		dump_cam(t_game *game, FILE *fp)
{
	int		i;
	t_cam	*cam;

	i = -1;
	fprintf(fp, "    \"cameras\":[\n");
	while (++i < game->cam_quantity)
	{
		cam = &game->gpu.camera[i];
		fprintf(fp, "        {\n");
		fprintf(fp, "            \"position\": [%.3f, %.3f, %.3f],\n",
		cam->position.s[0], cam->position.s[1], cam->position.s[2]);
		fprintf(fp, "            \"dir\": [%.3f, %.3f, %.3f],\n",
		cam->direction.s[0], cam->direction.s[1], cam->direction.s[2]);
		fprintf(fp, "            \"normal\": [%.3f, %.3f, %.3f],\n",
		cam->normal.s[0], cam->normal.s[1], cam->normal.s[2]);
		fprintf(fp, "            \"fov\": %.3f\n", cam->fov / M_PI * 180);
		if (i != game->cam_quantity - 1)
			fprintf(fp, "        },\n");
	}
	fprintf(fp, "        }\n    ]\n");
}

void		ss_free(t_gui *gui)
{
	int i;

	i = -1;
	i = -1;
	while (gui->s_s.buttons[++i] && i < MAX_OBJ)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->s_s.buttons[i], 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->s_s.buttons[i], 0);
		KW_RemoveWidgetMouseDownHandler(gui->s_s.buttons[i], 0);
	}
	if (gui->s_s.max_i > 0)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->s_s.frame, 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->s_s.frame, 0);
		KW_HideWidget(gui->s_s.frame);
		destr(gui, gui->s_s.frame);
	}
	if (gui->s_s.max_i > WIN_H / 45 - 12)
		scroll_box_free(gui, gui->s_s.frame);
}

void		scroll_box_free(t_gui *gui, KW_Widget *frame)
{
	KW_Scrollbox			*edit;

	edit = (KW_Scrollbox *)frame->privdata;
	KW_ReleaseTexture(gui->driver, edit->framerender);
	KW_RemoveWidgetKeyUpHandler(edit->hscroll, 0);
	KW_RemoveWidgetGeometryChangeHandler(edit->hscroll, 0);
	KW_RemoveWidgetTilesetChangeHandler(edit->hscroll, 0);
	KW_RemoveWidgetDragHandler(edit->hscroll, 0);
	KW_RemoveWidgetKeyUpHandler(edit->vscroll, 0);
	KW_RemoveWidgetGeometryChangeHandler(edit->vscroll, 0);
	KW_RemoveWidgetTilesetChangeHandler(edit->vscroll, 0);
	KW_RemoveWidgetDragHandler(edit->vscroll, 0);
	KW_RemoveWidgetChildrenChangeHandler(frame, 0);
	KW_RemoveWidgetKeyUpHandler(edit->inner, 0);
	KW_RemoveWidgetKeyUpHandler(edit->root, 0);
}
