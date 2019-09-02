/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_grow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:05:38 by jblack-b          #+#    #+#             */
/*   Updated: 2019/09/02 20:05:39 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libvect.h"
#include "malloc.h"
#include "libft.h"

int			vect_grow
	(t_vect *v, size_t n)
{
	void	*new;
	size_t	new_total;

	new_total = v->total * GROWTH_FACTOR * n;
	MALLOC(new, new_total);
	ft_memcpy(new, v->data, v->used);
	free(v->data);
	v->data = new;
	v->total = new_total;
	return (1);
}
