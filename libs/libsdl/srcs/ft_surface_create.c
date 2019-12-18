/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_surface_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 00:29:45 by olesgedz          #+#    #+#             */
/*   Updated: 2019/11/18 13:16:00 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl.h"

/*
**	Fucntion: creates a surface
**	Parameters: width, height os the surface
**	Return: malloced surface
*/

SDL_Surface	*ft_surface_create(int width, int height)
{
	SDL_Surface *new_surface;

	new_surface = SDL_CreateRGBSurface(0, width, height, 32,\
	RMASK, GMASK, BMASK, AMASK);
	return (new_surface);
}
