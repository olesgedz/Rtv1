/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_kiwi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 22:46:07 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/10 22:49:15 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		init_kiwi_r(t_gui *gui)
{
	gui->ed_w.show = 1;
	gui->s_s.show = 0;
	gui->o_s.show = 0;
	gui->c_s.show = 0;
	gui->c_c.show = 0;
	gui->g_b.show = 0;
	gui->o_t.show = 0;
	gui->c_o.show = 0;
	gui->n.show = 0;
	gui->c_c.frame = 0;
	gui->c_o.frame = 0;
}

void			init_kiwi(t_gui *gui)
{
	int i;

	i = -1;
	g_gui(gui, 1);
	gui->ed_w.winrect = (KW_Rect){0, 0, WIN_W, WIN_H};
	gui->driver =
	KW_CreateSDL2RenderDriver(gui->sdl.renderer, gui->sdl.window);
	gui->set = KW_LoadSurface(gui->driver, "gui/res/tileset.png");
	gui->gui = KW_Init(gui->driver, gui->set);
	while (++i < MAX_OBJ)
	{
		gui->o_s.buttons[i] = 0;
		gui->c_s.buttons[i] = 0;
		gui->s_s.buttons[i] = 0;
		gui->o_s.names[i] = 0;
		gui->c_s.names[i] = 0;
		gui->s_s.names[i] = 0;
		if (i < 30)
		{
			gui->g_b.names[i] = 0;
			gui->c_o.ed_b[i] = 0;
			gui->c_c.ed_b[i] = 0;
		}
	}
	init_kiwi_r(gui);
}
