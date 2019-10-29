/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 18:31:59 by lminta            #+#    #+#             */
/*   Updated: 2019/10/29 18:43:04 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	help_me(t_game *game, t_gui *gui)
{
	if (game->ev.type == SDL_MOUSEMOTION)
	{
		pos_check(game, gui);
		game->keys.xrel = -game->ev.motion.xrel;
		game->keys.yrel = -game->ev.motion.yrel;
		game->keys.mm = 1;
	}
}

void		mouse(t_game *game, t_gui *gui)
{
	static int	x = 0;
	static int	y = 0;
	static int	g = 0;

	if (game->ev.type == SDL_MOUSEBUTTONDOWN &&
	game->ev.button.button == SDL_BUTTON_RIGHT)
	{
		if (!gui->over_gui && (game->keys.lmb = 1))
		{
			SDL_GetMouseState(&x, &y);
			SDL_SetRelativeMouseMode(SDL_ENABLE);
			g = 0;
		}
		else
			g = 1;
	}
	else if (game->ev.type == SDL_MOUSEBUTTONUP &&
	game->ev.button.button == SDL_BUTTON_RIGHT)
	{
		if (!(game->keys.lmb = 0) && !g)
		{
			SDL_SetRelativeMouseMode(SDL_DISABLE);
			SDL_WarpMouseInWindow(game->sdl.window, x, y);
		}
	}
	else
		help_me(game, gui);
}
