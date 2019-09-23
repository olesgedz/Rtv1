/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:46:11 by lminta            #+#    #+#             */
/*   Updated: 2019/09/23 17:27:17 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	main_screen(t_gui *gui)
{
	scene_select(gui);
}

void	quit_kiwi_main(t_gui *gui)
{
	KW_DestroyWidget(gui->s_s.frame, 1);
	KW_ReleaseSurface(gui->driver, gui->set);
	//KW_ReleaseRenderDriver(gui->driver);
	KW_Quit(gui->gui);
}
