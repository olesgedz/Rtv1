/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:37:51 by lminta            #+#    #+#             */
/*   Updated: 2019/11/21 21:04:11 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	click_create(KW_Widget *widget, int b)
{
	t_gui		*gui;

	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	
}
