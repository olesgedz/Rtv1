/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arraymax.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 16:17:17 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/11 18:01:00 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

int		ft_arraymax(int *array, size_t length)
{
	size_t		i;
	int			max;

	if (array == NULL)
		return (0);
	i = 0;
	max = *array;
	while (i < length)
	{
		if (max < *(array + i))
			max = *(array + i);
		i++;
	}
	return (max);
}
