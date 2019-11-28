/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/23 18:53:30 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/16 13:33:06 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

size_t		ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t i;
	size_t j;
	size_t src_ln;
	size_t dts_ln;

	i = 0;
	j = 0;
	dts_ln = ft_strlen(dst);
	src_ln = ft_strlen(src);
	if (size <= dts_ln)
		return (src_ln + size);
	while (dst[i] != '\0' && i < size - 1)
		i++;
	while (i < size - 1 && src[j] != '\0')
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dts_ln + src_ln);
}
