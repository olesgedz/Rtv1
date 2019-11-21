/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_exec.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 23:32:05 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 18:08:28 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"
#include "malloc.h"

cl_int
	cl_krl_exec
	(t_cl_info *cl
	, cl_kernel krl
	, cl_uint work_dim
	, size_t *work_size)
{
	return (clEnqueueNDRangeKernel(cl->cmd_queue
		, krl, work_dim, NULL, work_size, NULL, 0, NULL, NULL));
}
