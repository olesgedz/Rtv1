/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:31:59 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 19:07:57 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		mouse_motion(t_game *game, t_gui *gui)
{
	pos_check(game, gui);
	game->keys.xrel = -game->ev.motion.xrel;
	game->keys.yrel = -game->ev.motion.yrel;
	game->mouse.mm = 1;
}

void		mouse_up(t_game *game)
{
	if (game->ev.button.button == SDL_BUTTON_RIGHT)
	{
		if (game->gui_mod)
			show_hide(game, g_gui(0, 0));
		if (!(game->mouse.rmb = 0) && !game->mouse.g)
		{
			SDL_SetRelativeMouseMode(SDL_DISABLE);
			SDL_WarpMouseInWindow(game->sdl.window, game->mouse.x,
			game->mouse.y);
		}
	}
	if (game->ev.button.button == SDL_BUTTON_LEFT)
		game->mouse.lmb = 0;
}

void		mouse_down(t_game *game, t_gui *gui)
{
	SDL_GetMouseState(&game->mouse.x, &game->mouse.y);
	check_ed_box_focus(game, gui, game->mouse.x, game->mouse.y);
	if (game->ev.button.button == SDL_BUTTON_RIGHT)
	{
		if (game->gui_mod)
			show_hide(game, g_gui(0, 0));
		if (!gui->over_gui && (game->mouse.rmb = 1))
		{
			SDL_SetRelativeMouseMode(SDL_ENABLE);
			game->mouse.g = 0;
		}
		else
			game->mouse.g = 1;
	}
	if (game->ev.button.button == SDL_BUTTON_LEFT)
		game->mouse.lmb = 1;
}
