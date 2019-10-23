/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vect_str_push.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:06:39 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 18:03:38 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libvect.h"
#include "libft.h"

int			vect_str_push
	(t_vect *v, char *s, size_t n)
{
	return (vect_push(v, s, ft_strlen(s), n));
}
