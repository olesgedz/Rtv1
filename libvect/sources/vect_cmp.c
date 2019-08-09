/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_cmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/23 01:11:13 by qle-guen          #+#    #+#             */
/*   Updated: 2016/12/23 01:25:24 by qle-guen         ###   ########.fr       */
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
