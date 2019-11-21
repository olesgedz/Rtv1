/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_present.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:56:24 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 19:10:32 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl.h"

/*
**	Fucntion: puts texture on the screen,  when writing to texture is needed
**	Parameters: sdl, texture
**	Return: pointer to array of pixel that texture consist of
*/

void	ft_texture_present(t_sdl *sdl, t_texture *texture)
{
	SDL_UnlockTexture(texture->sdl_texture);
	SDL_RenderCopy(sdl->renderer, texture->sdl_texture, NULL, NULL);
	SDL_RenderPresent(sdl->renderer);
}
