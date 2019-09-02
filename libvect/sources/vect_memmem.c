/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_memmem.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:05:54 by jblack-b          #+#    #+#             */
/*   Updated: 2019/09/02 20:05:54 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libvect.h"

void	*vect_memmem(t_vect *a, unsigned char *s, size_t n)
{
	size_t				i;
	unsigned char		*s1;

	s1 = a->data;
	while ((void *)s1 + n < a->data + a->used)
	{
		i = 0;
		while (i < n && s1[i] == s[i])
			i++;
		if (i == n)
			return (s1);
		s1++;
		s++;
	}
	return (NULL);
}
