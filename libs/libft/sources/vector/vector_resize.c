/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_resize.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/18 08:53:30 by olesgedz          #+#    #+#             */
/*   Updated: 2019/11/24 21:52:04 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	vector_resize(t_vector *v, int capacity)
{
	void **items;

	items = realloc(v->items, sizeof(void *) * capacity);
	if (items)
	{
		v->items = items;
		v->capacity = capacity;
	}
}
