/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_texture_present.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/25 18:56:24 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 19:07:49 by jblack-b         ###   ########.fr       */
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
