/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_surface_combine.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/19 21:04:57 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 19:09:29 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl.h"

/*
**	Fucntion: combines two surfaces within renf if rectangle
**		 and only if value of src in that pixel isn't null
**	Parameters: destination surface , source surface, area to work with in
**	Return: combined surface in dst
*/

t_surface		*ft_surface_combine(t_surface *dst,\
					t_surface *src, t_rectangle *rect)
{
	size_t j;
	size_t k;

	j = rect->position.y;
	while (j < rect->position.y + rect->size.height)
	{
		k = rect->position.x;
		while (k < rect->position.x + rect->size.width)
		{
			if (src->data[k + j * src->width] != 0)
				dst->data[k + j * dst->width] = src->data[k + j * src->width];
			k++;
		}
		j++;
	}
	return (dst);
}
