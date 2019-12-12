/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_select.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/16 16:30:29 by lminta            #+#    #+#             */
/*   Updated: 2019/12/12 17:43:54 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	first_button(t_gui *gui, struct dirent *name_buff)
{
	gui->s_s.names[0] = ft_strdup(name_buff->d_name);
	gui->s_s.rects[0] = &gui->s_s.buttonrect[0];
	KW_RectFillParentHorizontally(&gui->s_s.frect,
	gui->s_s.rects, gui->s_s.weights, 1, 15,
	KW_RECT_ALIGN_MIDDLE);
}

static void	scan_dir_bzero(t_gui *gui, int *i)
{
	*i += 1;
	while (*i < MAX_OBJ)
	{
		gui->s_s.buttons[*i] = 0;
		gui->s_s.names[*i] = 0;
		*i += 1;
	}
}

static int	scan_dir(t_gui *gui, int i)
{
	DIR				*res;
	struct dirent	*name_buff;

	scan_dir_bzero(gui, &i);
	if (!(res = opendir("scenes")))
		return (-1);
	while ((name_buff = readdir(res)) && (name_buff->d_type != 8
	|| !ft_strstr(name_buff->d_name, ".json")))
		i = 1;
	if (name_buff && name_buff->d_type == 8 &&
	ft_strstr(name_buff->d_name, ".json"))
		first_button(gui, name_buff);
	else
		return (-1);
	while ((name_buff = readdir(res)) && i < MAX_OBJ)
		if (ft_strstr(name_buff->d_name, ".json") && name_buff->d_type == 8)
		{
			gui->s_s.names[i] = ft_strdup(name_buff->d_name);
			gui->s_s.buttonrect[i] = gui->s_s.buttonrect[i - 1];
			gui->s_s.buttonrect[i].y += 45;
			if (i++ < WIN_H / 45 - 12)
				gui->s_s.frect.h += 45;
		}
	closedir(res);
	return (i);
}

static int	param_set(t_gui *gui)
{
	gui->s_s.weights[0] = 1;
	gui->s_s.frect = (KW_Rect){5, 25, FR_FZ, 80};
	gui->s_s.buttonrect[0] = (KW_Rect){0, 0, 30, 40};
	return (scan_dir(gui, -1));
}

void		scene_select(t_gui *gui, int i, KW_Widget *const *wid_arr)
{
	unsigned			test;

	if ((gui->s_s.max_i = param_set(gui)) == -1)
		return ;
	if (gui->s_s.max_i > WIN_H / 45 - 12)
	{
		gui->s_s.frame = KW_CreateScrollbox(gui->gui, NULL, &gui->s_s.frect);
		wid_arr = KW_GetWidgetChildren(gui->s_s.frame, &test);
		KW_HideWidget(wid_arr[2]);
	}
	else
		gui->s_s.frame = KW_CreateFrame(gui->gui, NULL, &gui->s_s.frect);
	while (++i < gui->s_s.max_i)
	{
		if (gui->s_s.max_i > WIN_H / 45 - 12)
			gui->s_s.buttonrect[i].x -= 15;
		gui->s_s.buttons[i] = KW_CreateButtonAndLabel(gui->gui,
gui->s_s.frame, gui->s_s.names[i], &gui->s_s.buttonrect[i]);
		KW_AddWidgetMouseDownHandler(gui->s_s.buttons[i], scene_click);
		KW_SetWidgetUserData(gui->s_s.buttons[i], ft_strdup(gui->s_s.names[i]));
		free(gui->s_s.names[i]);
	}
}
