/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/28 16:23:23 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/08 20:11:54 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		*ft_memalloc(size_t size)
{
	void	*new;
	size_t	i;

	i = 0;
	new = NULL;
	if (!(new = (void *)malloc(size)))
		return (NULL);
	ft_bzero(new, size);
	return (new);
}
