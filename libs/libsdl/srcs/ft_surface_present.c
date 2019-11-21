/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_surface_present.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:09:27 by jblack-b          #+#    #+#             */
/*   Updated: 2019/11/10 19:41:21 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl.h"

/*
**	Fucntion: puts the surface on the screen
**	Parameters: sdl, surface
**	Return: none
*/

void	ft_surface_present(t_sdl *sdl, SDL_Surface *surface)
{

	SDL_UpdateTexture(sdl->texture, NULL,\
		surface->pixels, surface->pitch);
	SDL_RenderCopy(sdl->renderer, sdl->texture, NULL, NULL);

	SDL_RenderPresent(sdl->renderer);
	//SDL_UpdateWindowSurface(sdl->window);
}
