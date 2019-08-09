/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/11 15:18:43 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/19 16:22:04 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int
	cl_init
	(t_cl_info *cl)
{
	cl_int	ret;

	if ((ret = clGetPlatformIDs(1, &cl->pl_id, NULL)) != CL_SUCCESS)
		return (ret);
	if ((ret = clGetDeviceIDs(cl->pl_id
		, CL_DEVICE_TYPE_GPU
		, 1
		, &cl->dev_id
		, &cl->dev_num)) != CL_SUCCESS)
		return (ret);
	cl->ctxt = clCreateContext(NULL, 1, &cl->dev_id, NULL, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	cl->cmd_queue = clCreateCommandQueue(cl->ctxt, cl->dev_id
		, CL_QUEUE_PROFILING_ENABLE, &ret);
	return (ret);
}
