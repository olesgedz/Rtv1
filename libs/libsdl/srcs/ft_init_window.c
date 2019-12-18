/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init_window.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:44:17 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 19:06:44 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl.h"

/*
**	Fucntion: inits window of given size
**	Parameters: sdl, width, height of the window
**	- creates sdl->surface for rendering
**	- creates sdl->texture to put image on the screen
**		!	texture can be used for rendering instead of surface
**	!	showcursor needs a parameter
**	Return: none
*/

void	ft_init_window(t_sdl *sdl, size_t win_w, size_t win_h)
{
	SDL_Init(SDL_INIT_EVERYTHING);
	sdl->win_h = win_h;
	sdl->win_w = win_w;
	sdl->surface = ft_surface_create(win_w, win_h);
	sdl->window = SDL_CreateWindow("RT",
	SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
	win_w, win_h, 0);
	sdl->renderer = SDL_CreateRenderer(sdl->window, -1,
	SDL_RENDERER_ACCELERATED);
	SDL_ShowCursor(SDL_TRUE);
	sdl->texture = SDL_CreateTexture(sdl->renderer, SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_STREAMING,
								win_w, win_h);
}
