/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/26 18:57:25 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/08 20:19:50 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static int		ft_strstrcmp(char *s1, char *s2)
{
	size_t i;

	i = 0;
	while ((unsigned char)s1[i] == (unsigned char)s2[i]
		&& (unsigned char)s1[i] != '\0' && (unsigned char)s2[i] != '\0')
		i++;
	if (i == ft_strlen(s2))
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

char			*ft_strstr(const char *haystack, const char *needle)
{
	if (*needle == '\0')
		return ((char *)haystack);
	while (*haystack != '\0')
	{
		if (ft_strstrcmp((char *)haystack, (char *)needle) == 0)
		{
			return ((char *)haystack);
		}
		haystack++;
	}
	return (NULL);
}
