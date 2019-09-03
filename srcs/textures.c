/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 15:55:58 by sbrella           #+#    #+#             */
/*   Updated: 2019/09/02 15:57:10 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void					get_texture(char *name, t_txture *texture)
{
	SDL_Surface			*surf;
	SDL_Surface			*an_surf;
	SDL_PixelFormat		*fmt;
	char				*m;

	m = ft_strjoin("./textures/", name);
	an_surf = SDL_LoadBMP(m);
	fmt = malloc(sizeof(SDL_PixelFormat));
	ft_memcpy(fmt, an_surf->format, sizeof(SDL_PixelFormat));
	fmt->BytesPerPixel = 4;
	fmt->BitsPerPixel = 32;
	surf = SDL_ConvertSurface(an_surf, fmt, an_surf->flags);
	SDL_FreeSurface(an_surf);
	free(fmt);
	texture->width = surf->w;
	texture->height = surf->h;
	if (texture->height * texture->width <= 1920 * 1080)
		ft_memcpy(texture->texture, surf->pixels, (surf->h) * surf->pitch);
	else
		exit(0);
	// SDL_FreeSurface(surf);
}
