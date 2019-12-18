/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraysort.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:00:14 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/11 17:43:48 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		ft_arraysort(int *array, size_t length)
{
	size_t j;
	size_t k;

	j = 0;
	k = 0;
	if (array == NULL)
		return ;
	while (j < length)
	{
		while (k < length - 1)
		{
			if (array[k] > array[k + 1])
				ft_swap_int(&(array[k]), &(array[k + 1]));
			k++;
		}
		k = 0;
		j++;
	}
}
