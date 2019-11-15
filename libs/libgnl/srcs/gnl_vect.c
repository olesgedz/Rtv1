/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_vect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:16:07 by jblack-b          #+#    #+#             */
/*   Updated: 2019/11/08 00:50:55 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libgnl.h"
#include <unistd.h>

static int	cpy
	(t_vect *v, t_vect *line, int opts)
{
	void	*buf;

	if ((buf = ft_memchr(v->data, GNL_SEP_CHAR, v->used)))
	{
		vect_add(line, v->data, buf - v->data);
		ft_memmove(v->data, buf + 1, v->used - (buf + 1 - v->data));
		v->used -= buf + 1 - v->data;
		if ((!!(opts & '\n')))
			vect_mset_end(line, GNL_APPEND_CHAR, 1);
		if ((!!(opts & 1)))
			vect_mset_end(line, '\0', 1);
		return (1);
	}
	return (0);
}

int			gnl_vect
	(int fd, t_vect *v, t_vect *line, int opts)
{
	int		ret;

	if (v->data && (ret = cpy(v, line, opts)))
		return (ret);
	vect_req(v, GNL_BUFF_SIZE + (!!(opts & 1)) + (!!(opts & 2)));
	ret = read(fd, v->data + v->used, GNL_BUFF_SIZE);
	if (ret < 0)
		return (ret);
	if (!ret)
	{
		if (!v->used)
			return (0);
		vect_add(line, v->data, v->used);
		v->used = 0;
		return (1);
	}
	v->used += ret;
	return (gnl_vect(fd, v, line, opts));
}
