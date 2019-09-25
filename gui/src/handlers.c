/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handlers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 17:34:53 by lminta            #+#    #+#             */
/*   Updated: 2019/09/25 18:21:17 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	over(KW_Widget *widget, int b)
{
	t_gui	*gui;

	SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	gui = g_gui(0, 0);
	gui->over_gui = 1;
}

void	leave(KW_Widget *widget, int b)
{
	t_gui	*gui;

	gui = g_gui(0, 0);
	if (gui->main_screen)
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
	gui->over_gui = 0;
}
