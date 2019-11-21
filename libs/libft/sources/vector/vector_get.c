/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_get.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 08:44:31 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 17:52:31 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*vector_get(t_vector *v, int index)
{
	if (index >= 0 && index < v->total)
		return (v->items[index]);
	return (NULL);
}
