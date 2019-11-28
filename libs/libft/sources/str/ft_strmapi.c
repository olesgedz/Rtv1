/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 19:30:23 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/15 01:56:17 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static char		ft_u_striteri(char *s, char (*f)(unsigned int, char))
{
	int i;

	i = 0;
	if (s)
		while (*s)
		{
			*s = f(i, *s);
			s++;
			i++;
		}
	return (*s);
}

char			*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char *new;

	if (s == NULL || f == NULL)
		return (NULL);
	if (!(new = (char *)(malloc(sizeof(char) * ft_strlen(s) + 1))))
		return (NULL);
	ft_strcpy(new, s);
	ft_u_striteri(new, f);
	return (new);
}
