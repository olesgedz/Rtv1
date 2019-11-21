/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/04 18:10:05 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/11 19:18:12 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

void		ft_putstr_fd(char const *s, int fd)
{
	if (s == NULL)
		return ;
	while (*s != '\0')
	{
		ft_putchar_fd((char)(*s), fd);
		s++;
	}
}
