/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_mset_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:05:59 by jblack-b          #+#    #+#             */
/*   Updated: 2019/09/02 20:06:00 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "libvect.h"

int			vect_mset_end
	(t_vect *v, unsigned char c, size_t size)
{
	return (vect_mset(v, c, size, v->used));
}
