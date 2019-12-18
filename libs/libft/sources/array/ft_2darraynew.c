/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2darraynew.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/17 03:09:49 by olesgedz          #+#    #+#             */
/*   Updated: 2019/01/17 10:42:12 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		**ft_2darraynew(size_t y, size_t x, char c)
{
	char				**new;
	size_t				j;
	size_t				k;

	if (!(new = (char **)(malloc(sizeof(char *) * (y + 1)))))
		return (NULL);
	new[y] = NULL;
	j = 0;
	while (j < y)
	{
		if (!(new[j] = (char *)(malloc(sizeof(char ) * x + 1))))
			return (NULL);
		new[j][x] = '\0';
		k = 0;
		while (k < x)
		{
			new[j][k] = c;
			k++;
		}
		j++;
	}
	return (new);
}
