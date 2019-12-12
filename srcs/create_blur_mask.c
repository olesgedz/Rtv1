/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_blur_mask.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 21:08:49 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/12 23:02:30 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

float	*create_blur_mask(float sigma, int * mask_size_pointer)
{
	int mask_size;
	float *mask;

	mask_size = (int)ceil(3.0f*sigma);
	mask = (float*)malloc(sizeof(float) * (mask_size*2+1)*(mask_size*2+1));
	float sum = 0.0f;
	for(int a = -mask_size; a < mask_size+1; a++) {
		for(int b = -mask_size; b < mask_size+1; b++) {
			float temp = exp(-((float)(a*a+b*b) / (2*sigma*sigma)));
			sum += temp;
			mask[a+mask_size+(b+mask_size)*(mask_size*2+1)] = temp;
		}
	}
	for(int i = 0; i < (mask_size*2+1)*(mask_size*2+1); i++)
		mask[i] = mask[i] / sum;
	*mask_size_pointer = mask_size;
	return mask;
}
