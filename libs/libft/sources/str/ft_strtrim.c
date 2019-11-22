/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/30 17:10:45 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/08 20:20:19 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char		*ft_strtrim(char const *s)
{
	char	*new;
	int		len;
	int		i;

	i = -1;
	if (s == NULL)
		return (NULL);
	len = ft_strlen(s) - 1;
	while (s[len] == ' ' || s[len] == '\t' || s[len] == '\n')
		len--;
	while (s[++i] == ' ' || s[i] == '\t' || s[i] == '\n')
		len--;
	len < 0 && (len = 0);
	if (!(new = (char *)(malloc(sizeof(char) * len + 2))))
		return (NULL);
	s += i;
	i = -1;
	while (++i < len + 1)
		new[i] = *s++;
	new[i] = '\0';
	return (new);
}
