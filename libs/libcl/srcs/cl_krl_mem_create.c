/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_mem_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:54:48 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 18:57:52 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int	cl_krl_mem_create(t_cl_info *cl, t_cl_krl *krl,\
cl_uint arg_index, cl_mem_flags flag)
{
	cl_int ret;

	if (krl->sizes[arg_index] != 0)
	{
		krl->args[arg_index] = clCreateBuffer(cl->ctxt, flag,
		krl->sizes[arg_index], NULL, &ret);
	}
	return (ret);
}
