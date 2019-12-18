/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_add.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:05:22 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 18:03:04 by lminta           ###   ########.fr       */
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
