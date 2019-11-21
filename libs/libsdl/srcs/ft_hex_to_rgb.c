/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hex_to_rgb.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 00:57:48 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 18:54:37 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl.h"

/*
**	Fucntion: turns hex color to rgb
**	Parameters: hex color, opacity
**	Return: resulting color as (t_rgba *)
*/

t_rgba	*ft_hex_to_rgb(int hex, int a)
{
	static t_rgba rgb;

	rgb.r = (hex >> 16) & 0xFF;
	rgb.g = (hex >> 8) & 0xFF;
	rgb.b = hex & 0xFF;
	rgb.a = a;
	return (&rgb);
}
