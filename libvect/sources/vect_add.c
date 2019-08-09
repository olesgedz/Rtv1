/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/25 18:39:35 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/09 13:43:15 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"
#include "libft.h"

int				vect_add
	(t_vect *v, void *data, size_t size)
{
	vect_req(v, size);
	if (!data)
	{
		ft_bzero(v->data + v->used, size);
		return (1);
	}
	ft_memcpy(v->data + v->used, data, size);
	v->used += size;
	return (1);
}
