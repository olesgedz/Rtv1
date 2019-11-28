/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_mset_end.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:05:59 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 18:03:21 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"

int			vect_mset_end
	(t_vect *v, unsigned char c, size_t size)
{
	return (vect_mset(v, c, size, v->used));
}
