/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 19:47:44 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/11 20:08:04 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

char		*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t j;
	size_t i;

	j = 0;
	i = 0;
	if (*needle == '\0')
		return ((char *)haystack);
	while (haystack[j] != '\0' && j < len)
	{
		i = 0;
		while (haystack[j + i] == needle[i]
			&& haystack[i + j] != '\0' && i + j < len)
		{
			i++;
			if (needle[i] == '\0')
				return ((char *)haystack + j);
		}
		j++;
	}
	return (NULL);
}
