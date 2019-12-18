/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 17:40:33 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/08 20:17:19 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

static	size_t			ft_toutf8(char *dest, unsigned int ch)
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

void					ft_putchar_fd(char c, int fd)
{
	char	strm[4];
	int		length;

	if ((unsigned char)c < 0x80)
		write(fd, &c, 1);
	else
	{
		length = ft_toutf8(strm, (unsigned char)c);
		if (length == 0)
			return ;
		write(fd, strm, length);
	}
}
