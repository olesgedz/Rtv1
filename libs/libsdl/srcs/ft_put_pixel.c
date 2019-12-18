/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_pixel.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/08 20:04:54 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 19:06:58 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl.h"

/*
**	Fucntion: puts a pixel on the surface
**	Parameters: surface, coordinates on the surface as t_point
**	Return: none
**	! Don't use it, writting it "inline"(in the code) saves a lot of resources
**	? should it use inline prefix? need to test that
*/

void			ft_put_pixel(SDL_Surface *surface, t_point *p, int color)
{
	*(((Uint32 *)surface->pixels) + (p->x + p->y * surface->w)) = color;
}
