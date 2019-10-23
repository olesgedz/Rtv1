/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:05:28 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 18:03:06 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

int		vect_cmp(t_vect *a, t_vect *b)
{
	unsigned char	*as;
	unsigned char	*bs;

	as = a->data;
	bs = b->data;
	while ((void *)as < a->data + a->used
		&& (void *)bs < b->data + b->used
		&& *as == *bs)
	{
		as++;
		bs++;
	}
	return (as - bs);
}
