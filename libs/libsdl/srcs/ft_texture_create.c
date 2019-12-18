/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 20:46:40 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 19:10:01 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl.h"

/*
**	Fucntion: creates a texture, used to put surface on the sreen
**	Parameters: sdl, width, height of texture (window)
**	Return: malloced texture
*/

t_texture	*ft_texture_create(t_sdl *sdl, int width, int height)
{
	t_texture	*new_texture;

	new_texture = ft_memalloc(sizeof(t_texture));
	new_texture->sdl_texture = SDL_CreateTexture(sdl->renderer,
								SDL_PIXELFORMAT_ARGB8888,
								SDL_TEXTUREACCESS_STREAMING,
								width, height);
	new_texture->width = width;
	new_texture->height = height;
	return (new_texture);
}
