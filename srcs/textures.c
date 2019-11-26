/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 15:55:58 by sbrella           #+#    #+#             */
/*   Updated: 2019/11/26 21:27:06 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ya_kostil(SDL_PixelFormat *fmt)
{
	fmt->BytesPerPixel = 4;
	fmt->BitsPerPixel = 32;
	fmt->Rmask = RMASK;//RMASK;
	fmt->Gmask = GMASK;//GMASK;
	fmt->Bmask = BMASK;//BMASK;
	fmt->Amask = AMASK;//AMASK;
}

void		get_texture(char *name, t_txture *texture, char *path)
{
	SDL_Surface			*surf;
	SDL_Surface			*an_surf;
	SDL_PixelFormat		*fmt;
	char				*m;

	m = ft_strjoin(path, name);
	an_surf = IMG_Load(m);
	ft_strdel(&m);
	if (an_surf == NULL)
		return ;
	fmt = malloc(sizeof(SDL_PixelFormat));
	ft_memcpy(fmt, an_surf->format, sizeof(SDL_PixelFormat));
	ya_kostil(fmt);
	surf = SDL_ConvertSurface(an_surf, fmt, an_surf->flags);
	SDL_FreeSurface(an_surf);
	ft_memdel((void **)&fmt);
	texture->width = surf->w;
	texture->height = surf->h;
	if (texture->height * texture->width <= 4096 * 2048)
		ft_memcpy(texture->texture, surf->pixels, (surf->h) * surf->pitch);
	else
		exit(0);
	SDL_FreeSurface(surf);
}
