/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_surface_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 14:15:21 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 19:09:20 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl.h"

/*
**	Fucntion: clears any surface
**	Parameters: surface
**	Return: none
*/

void	ft_surface_clear(t_surface *surface)
{
	ft_bzero(surface->data, sizeof(Uint32) * surface->width * surface->height);
}
