/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/03 14:37:38 by olesgedz          #+#    #+#             */
/*   Updated: 2019/04/09 21:08:41 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static size_t		ft_toutf8(char *dest, int ch)
{
	if (ch < 0x800)
	{
		dest[0] = (ch >> 6) | 0xC0;
		dest[1] = (ch & 0x3F) | 0x80;
		return (2);
	}
	if (ch < 0x10000)
	{
		dest[0] = (ch >> 12) | 0xE0;
		dest[1] = ((ch >> 6) & 0x3F) | 0x80;
		dest[2] = (ch & 0x3F) | 0x80;
		return (3);
	}
	if (ch < 0x110000)
	{
		dest[0] = (ch >> 18) | 0xF0;
		dest[1] = ((ch >> 12) & 0x3F) | 0x80;
		dest[2] = ((ch >> 6) & 0x3F) | 0x80;
		dest[3] = (ch & 0x3F) | 0x80;
		return (4);
	}
	return (0);
}

/*
** (unsigned char)c < 0x80
*/

void				ft_putchar(int c)
{
	char	strm[4];
	int		length;

	if (c < 0x80)
		write(1, &c, 1);
	else
	{
		length = ft_toutf8(strm, c);
		if (length == 0)
			return ;
		write(1, strm, length);
	}
}
