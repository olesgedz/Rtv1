/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_wrap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/06/17 20:51:02 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/09 14:01:33 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"
#include "libft.h"
#include "malloc.h"

t_vect			*vect_wrap
	(void *data, size_t size)
{
	t_vect		*ret;

	MALLOC1_ZERO(ret);
	ret->total = size;
	ret->used = size;
	ret->data = data;
	return (ret);
}
