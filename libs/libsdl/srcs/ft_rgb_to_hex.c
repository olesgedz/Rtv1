/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rgb_to_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/26 00:29:46 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 19:09:23 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl.h"

/*
**	Fucntion: converts rgb color to hex
**	Parameters: (int) red channel, (int) green channel, (int) blue channel
**	Return: resulting (int) color as hex
**	! doesn't hande wrong inputs as negative or > 255
**	! no alpha opacity channel
*/

int	ft_rgb_to_hex(int r, int g, int b)
{
	return (r << 16 | g << 8 | b);
}
