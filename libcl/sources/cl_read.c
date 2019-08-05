/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_read.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 02:17:46 by qle-guen          #+#    #+#             */
/*   Updated: 2017/05/09 12:37:48 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int
	cl_read
	(t_cl_info *cl
	, cl_mem mem
	, size_t size
	, void *data)
{
	clFinish(cl->cmd_queue);
	return (clEnqueueReadBuffer(cl->cmd_queue
		, mem
		, CL_TRUE
		, 0
		, size
		, data
		, 0
		, NULL
		, NULL));
}
