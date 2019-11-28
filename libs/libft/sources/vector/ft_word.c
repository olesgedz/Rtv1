/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/05 03:08:44 by olesgedz          #+#    #+#             */
/*   Updated: 2019/08/05 03:08:49 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

unsigned char	*ft_word(void **p, size_t *n1, void *match, size_t n2)
{
	unsigned char	*r;
	unsigned char	**s;

	s = (unsigned char **)p;
	while (*n1 && ft_memchr(match, (int)**s, n2))
	{
		(*n1)--;
		(*s)++;
	}
	r = *s;
	while (*n1 && !ft_memchr(match, (int)**s, n2))
	{
		(*n1)--;
		(*s)++;
	}
	return (r == *s ? NULL : r);
}
