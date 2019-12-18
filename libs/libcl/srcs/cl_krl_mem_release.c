/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_mem_release.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:11:53 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/10 16:15:59 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int		cl_krl_mem_release(t_cl_info *cl, t_cl_krl *krl,\
	cl_uint arg_index)
{
	cl_int ret;

	ret = 0;
	if (krl->sizes[arg_index] != 0)
	{
		ret = clReleaseMemObject(krl->args[arg_index]);
	}
	return (ret);
}
