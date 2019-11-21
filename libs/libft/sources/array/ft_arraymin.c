/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraymin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:52:29 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/11 18:00:22 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_arraymin(int *array, size_t length)
{
	size_t	i;
	int		min;

	if (array == NULL)
		return (0);
	i = 0;
	min = *array;
	while (i < length)
	{
		if (min > *(array + i))
			min = *(array + i);
		i++;
	}
	return (min);
}
