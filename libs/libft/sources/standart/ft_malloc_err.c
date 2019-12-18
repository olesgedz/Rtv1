/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc_err.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 18:39:35 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/09 16:40:45 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "malloc.h"
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

static void	put_size(size_t size)
{
	size_t	pow;
	char	c;

	if (!size)
	{
		write(2, "0", 1);
		return ;
	}
	pow = 1;
	while (pow < size)
		pow *= 10;
	pow /= 10;
	while (size)
	{
		c = size / pow;
		size -= pow * c;
		pow /= 10;
		c += '0';
		write(2, &c, 1);
	}
}

void		ft_malloc_err
	(size_t size, const char *func, const char *file, int line)
{
	static char	*malloc_err1 = "failed to allocate ";
	static char	*malloc_err2 = " bytes\n";
	static char	*malloc_err3 = "failed to allocate n > UINT_MAX bytes\n";

	write(2, file, ft_strlen((char *)file));
	write(2, ", line ", ft_strlen(", line "));
	put_size((size_t)line);
	write(2, " in function ", ft_strlen(" in function "));
	write(2, func, ft_strlen((char *)func));
	write(2, ": ", 2);
	if (size > UINT_MAX)
		write(2, malloc_err3, ft_strlen(malloc_err3));
	else
	{
		write(2, malloc_err1, ft_strlen(malloc_err1));
		put_size(size);
		write(2, malloc_err2, ft_strlen(malloc_err2));
	}
	exit(1);
}
