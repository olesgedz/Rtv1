/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 15:55:58 by sbrella           #+#    #+#             */
/*   Updated: 2019/11/07 20:23:00 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	ya_kostil(SDL_PixelFormat *fmt)
{
	fmt->BytesPerPixel = 4;
	fmt->BitsPerPixel = 32;
	fmt->Rmask = BMASK;//RMASK;
	fmt->Gmask = GMASK;//GMASK;
	fmt->Bmask = RMASK;//BMASK;
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
	an_surf = SDL_CreateRGBSurface(0, CL_DEVICE_IMAGE2D_MAX_HEIGHT,
	CL_DEVICE_IMAGE2D_MAX_WIDTH, 32, RMASK, GMASK, BMASK, AMASK);
	SDL_BlitScaled(surf, NULL, an_surf, NULL);
	ft_memdel((void **)&fmt);
	texture->width = an_surf->w;
	texture->height = an_surf->h;
	if (texture->height * texture->width <= CL_DEVICE_IMAGE2D_MAX_HEIGHT * CL_DEVICE_IMAGE2D_MAX_WIDTH)
		ft_memcpy(texture->texture, an_surf->pixels, (an_surf->h) * an_surf->pitch);
	else
		exit(0);
	// SDL_FreeSurface(surf);
	// SDL_FreeSurface(an_surf);
}
