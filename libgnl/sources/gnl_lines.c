/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_lines.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/20 13:44:24 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/09 14:15:15 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "malloc.h"
#include "libgnl.h"

int		gnl_lines(int fd, t_vect *lines, int opts)
{
	char	*dup;
	int		ret;
	t_vect	buf;
	t_vect	line;

	vect_init(&buf);
	vect_init(&line);
	while ((ret = gnl_vect(fd, &buf, &line, opts | GNL_STR)) == 1)
	{
		if (!line.used)
			continue ;
		MALLOC_N(dup, line.used);
		ft_memcpy(dup, line.data, line.used);
		VECT_ADD(lines, dup);
		line.used = 0;
	}
	free(line.data);
	free(buf.data);
	return (ret);
}
