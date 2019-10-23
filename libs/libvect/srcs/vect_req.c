/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_req.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:06:26 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 18:03:33 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"
#include "malloc.h"

int			vect_req
	(t_vect *v, size_t size)
{
	size_t	n;

	if (!v->total)
	{
		MALLOC(v->data, size);
		v->total = size;
		v->used = 0;
	}
	if (v->total >= v->used + size)
		return (1);
	if (v->total == 1)
		v->total++;
	n = 1;
	while (v->total * n * GROWTH_FACTOR < v->used + size)
		n++;
	return (vect_grow(v, size));
}
