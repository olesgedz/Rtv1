/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/10 17:02:19 by jblack-b          #+#    #+#             */
/*   Updated: 2019/08/10 17:05:46 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

char		*read_file(int fd, size_t *size)
{
	char	*tmp;
	char	*res;
	ssize_t	num;
	char	buf[256];

	res = (char *)malloc(sizeof(char));
	res[0] = '\0';
	if (res < 0)
		return (NULL);
	while ((num = read(fd, buf, 255)) > 0)
	{
		buf[num] = '\0';
		tmp = res;
		res = ft_strjoin(res, buf);
		free(tmp);
	}
	if (size)
		*size = ft_strlen(res);
	return (res);
}
