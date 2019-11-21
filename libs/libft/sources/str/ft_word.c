/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 17:44:35 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 17:46:01 by lminta           ###   ########.fr       */
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
