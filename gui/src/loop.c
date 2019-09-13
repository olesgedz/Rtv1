/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   loop.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 16:35:00 by lminta            #+#    #+#             */
/*   Updated: 2019/09/13 17:29:33 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"


void	loopa(t_game *game)
{
	while (!SDL_QuitRequested() && !game->quit)
	{
		SDL_RenderClear(game->sdl->renderer);
		KW_ProcessEvents(game->gui->gui);
		KW_Paint(game->gui->gui);
		SDL_RenderPresent(game->sdl->renderer);
	}
}
