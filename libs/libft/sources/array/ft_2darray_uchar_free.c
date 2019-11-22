/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2darray_uchar_free.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/11 16:07:18 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 15:31:35 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_2darray_uchar_free(unsigned char ***tab)
{
	unsigned char **names;

	if (tab)
	{
		names = *tab;
		while (*names != NULL)
			free(*names++);
		free(*tab);
	}
}
