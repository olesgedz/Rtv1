/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_blur_mask.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 21:08:49 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/14 18:49:02 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	mask_fill(float *mask, int *mask_size_pointer, int mask_size,
int sum)
{
	int	cntr;

	cntr = -1;
	while (++cntr < (mask_size * 2 + 1) * (mask_size * 2 + 1))
		mask[cntr] = mask[cntr] / sum;
	*mask_size_pointer = mask_size;
}

float		*create_blur_mask(float sigma, int *mask_size_pointer)
{
	int		mask_size;
	float	*mask;
	float	sum;
	int		cntr[2];
	float	temp;

	mask_size = (int)ceil(3.0f * sigma);
	mask = (float*)malloc_exit(sizeof(float) * (mask_size * 2 + 1) *
	(mask_size * 2 + 1));
	sum = 0.0f;
	cntr[0] = -mask_size - 1;
	while (++cntr[0] < mask_size + 1)
	{
		cntr[1] = -mask_size - 1;
		while (++cntr[1] < mask_size + 1)
		{
			temp = exp(-((float)(cntr[0] * cntr[0] + cntr[1] * cntr[1]) /
			(2 * sigma * sigma)));
			sum += temp;
			mask[cntr[0] + mask_size + (cntr[1] + mask_size) *
			(mask_size * 2 + 1)] = temp;
		}
	}
	mask_fill(mask, mask_size_pointer, mask_size, sum);
	return (mask);
}

void		*malloc_exit(size_t len)
{
	void	*res;

	if (!(res = malloc(len)))
		terminate("Malloc ne ok\n");
	return (res);
}
