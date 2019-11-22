/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 16:02:22 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/16 14:26:17 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strnew(size_t size)
{
	char *new_str;

	new_str = NULL;
	if (size + 1 < size)
		return (NULL);
	if (!(new_str = (char *)(malloc(sizeof(char) * size + 1))))
		return (NULL);
	ft_bzero(new_str, size + 1);
	return (new_str);
}
