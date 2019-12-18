/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 03:24:13 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 17:37:14 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_memprint(void *s, size_t n)
{
	size_t i;

	i = 0;
	while (i < n)
	{
		if (ft_isprint(((char *)s)[i]))
			ft_putchar(((char *)s)[i]);
		else
			ft_putchar('.');
		i++;
	}
}
