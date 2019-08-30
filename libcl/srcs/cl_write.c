/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_write.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/03 01:14:42 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/16 13:54:58 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int
	cl_write
	(t_cl_info *cl
	, cl_mem mem
	, size_t size
	, void *data)
{
	return (clEnqueueWriteBuffer(cl->cmd_queue
		, mem
		, CL_TRUE
		, 0
		, size
		, data
		, 0
		, NULL
		, NULL));
}
