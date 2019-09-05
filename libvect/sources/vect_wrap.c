/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_wrap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:06:46 by jblack-b          #+#    #+#             */
/*   Updated: 2019/09/02 20:06:50 by jblack-b         ###   ########.fr       */
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
