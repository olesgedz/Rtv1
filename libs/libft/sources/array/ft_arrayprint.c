/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrayprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/11 17:16:08 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/11 17:59:05 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		ft_arrayprint(int *array, size_t length)
{
	size_t i;

	if (array == NULL)
		return ;
	i = 0;
	while (i < length)
	{
		ft_putnbr(array[i]);
		i++;
		if (i < length)
			ft_putstr(" ");
	}
}
