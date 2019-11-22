/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 20:13:07 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/16 14:24:54 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char		*ft_strjoin(char const *s1, char const *s2)
{
	char *new;

	new = NULL;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(new = (char *)(malloc(sizeof(char) * \
		(ft_strlen(s1) + ft_strlen(s2)) + 1))))
		return (NULL);
	ft_strcpy(new, s1);
	ft_strcpy(new + ft_strlen(s1), s2);
	return (new);
}
