/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_vect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:16:07 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 18:01:08 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "libgnl.h"
#include <unistd.h>

#define GNL_OPT(a) (!!(opts & a))

static int	cpy
	(t_vect *v, t_vect *line, int opts)
{
	void	*buf;

	if ((buf = ft_memchr(v->data, GNL_SEP_CHAR, v->used)))
	{
		vect_add(line, v->data, buf - v->data);
		ft_memmove(v->data, buf + 1, v->used - (buf + 1 - v->data));
		v->used -= buf + 1 - v->data;
		if (GNL_OPT(GNL_APPEND_CHAR))
			vect_mset_end(line, GNL_APPEND_CHAR, 1);
		if (GNL_OPT(GNL_STR))
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
	vect_req(v, GNL_BUFF_SIZE + GNL_OPT(GNL_STR) + GNL_OPT(GNL_APPEND));
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
