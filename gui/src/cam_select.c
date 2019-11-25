/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cam_select.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 21:48:49 by lminta            #+#    #+#             */
/*   Updated: 2019/11/25 22:52:45 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		cum_click(KW_Widget *widget, int b)
{
	static t_cam		*cam;
	static KW_Widget	*wid = 0;
	t_gui				*gui;
	KW_Widget *label;

	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	if (gui->c_o.show == 1)
		norma_from_cam_select(gui, widget, wid);
	if (widget && (cam != KW_GetWidgetUserData(widget)))
	{
		cam = KW_GetWidgetUserData(widget);
		cam_if(gui, cam);
		wid = widget;
		KW_SetLabelTextColor(KW_GetButtonLabel(wid),
		(KW_Color){255, 255, 255, 255});
		gui->c_o.show = 1;
	}
	else
	{
		wid = 0;
		cam = 0;
	}
}

char		*cam_mass_name(t_cam *cam)
{
	char	*res;
	char	*buff;
	char	str[100];
	int		con;

	if (fabs(cam->position.s[0]) < 10 && fabs(cam->position.s[1]) < 10 &&
	fabs(cam->position.s[0]) < 10)
		con = 2;
	else
		con = 4;
	gcvt(cam->position.s[0], con, str);
	res = ft_strjoin("(", str);
	buff = ft_strjoin(res, ", ");
	free(res);
	gcvt(cam->position.s[1], con, str);
	res = ft_strjoin(buff, str);
	free(buff);
	buff = ft_strjoin(res, ", ");
	free(res);
	gcvt(cam->position.s[2], con, str);
	res = ft_strjoin(buff, str);
	free(buff);
	buff = ft_strjoin(res, ")");
	free(res);
	return (buff);
}

static void	first_button(t_gui *gui, char *name_buff)
{
	gui->c_s.names[0] = name_buff;
	gui->c_s.rects[0] = &gui->c_s.buttonrect[0];
	KW_RectFillParentHorizontally(&gui->c_s.frect,
	gui->c_s.rects, gui->c_s.weights, 1, 15,
	KW_RECT_ALIGN_MIDDLE);
}

static int	scan_mass(t_gui *gui, t_cam *cams, int num)
{
	int		i;

	i = -1;
	while (++i < MAX_OBJ)
	{
		gui->c_s.buttons[i] = 0;
		gui->c_s.names[i] = 0;
	}
	gui->c_s.weights[0] = 1;
	gui->c_s.frect = (KW_Rect){0, 25, FR_FZ, 80};
	gui->c_s.frect.x += gui->g_b.buttonrect[0].w;
	gui->c_s.buttonrect[0] = (KW_Rect){0, 0, 30, 40};
	i = 1;
	first_button(gui, cam_mass_name(&cams[0]));
	while (i < num && i < MAX_OBJ)
	{
		gui->c_s.names[i] = cam_mass_name(&cams[i]);
		gui->c_s.buttonrect[i] = gui->c_s.buttonrect[i - 1];
		gui->c_s.buttonrect[i].y += 45;
		if (i < WIN_H / 45 - 3)
			gui->c_s.frect.h += 45;
		i++;
	}
	return (i);
}

void		cam_select(t_gui *gui, t_cam *cams, int num)
{
	int					i;
	unsigned			test;
	KW_Widget *const	*wid_arr;

	gui->c_s.max_i = scan_mass(gui, cams, num);
	if ((i = -1) && gui->c_s.max_i > WIN_H / 45 - 3)
	{
		gui->c_s.frame = KW_CreateScrollbox(gui->gui, NULL, &gui->c_s.frect);
		wid_arr = KW_GetWidgetChildren(gui->c_s.frame, &test);
		KW_HideWidget(wid_arr[2]);
	}
	else
		gui->c_s.frame = KW_CreateFrame(gui->gui, NULL, &gui->c_s.frect);
	while (++i < gui->c_s.max_i)
	{
		if (gui->c_s.max_i > WIN_H / 45 - 3)
			gui->c_s.buttonrect[i].x -= 15;
		gui->c_s.buttons[i] = KW_CreateButtonAndLabel(gui->gui,
gui->c_s.frame, gui->c_s.names[i], &gui->c_s.buttonrect[i]);
		KW_AddWidgetMouseDownHandler(gui->c_s.buttons[i], cum_click);
		KW_SetWidgetUserData(gui->c_s.buttons[i], &cams[i]);
	}
}
