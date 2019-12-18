/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_set_arg.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:56:42 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 18:59:36 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int	cl_krl_set_arg(t_cl_krl *krl, int index)
{
	int ret;

	if (krl->sizes[index])
	{
		if (krl->args[index] == NULL)
			ret = clSetKernelArg(krl->krl, index,\
			krl->sizes[index], (void*)krl->cpu_srcs[index]);
		else
		{
			ret = clSetKernelArg(krl->krl, index,\
			sizeof(cl_mem), (void*)&krl->args[index]);
		}
	}
	else
	{
		ret = clSetKernelArg(krl->krl, index,\
			sizeof(cl_mem), NULL);
	}
	return (ret);
}
