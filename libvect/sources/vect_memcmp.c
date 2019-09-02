/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_memcmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:05:49 by jblack-b          #+#    #+#             */
/*   Updated: 2019/09/02 20:05:49 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libvect.h"

int		vect_memcmp(t_vect *a, unsigned char *s, size_t n)
{
	size_t			i;
	unsigned char	*s1;

	i = 0;
	s1 = a->data;
	while (*s1 == *s
		&& (void *)s1 < a->data + a->used
		&& *s
		&& n)
	{
		s1++;
		s++;
		n++;
	}
	return (*s - *s1);
}
