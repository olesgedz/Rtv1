/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_init_arg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:52:06 by jblack-b          #+#    #+#             */
/*   Updated: 2019/11/15 17:53:53 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int  cl_krl_init_arg(t_cl_krl *krl, cl_uint arg_index, size_t arg_size,  void *arg_value)
{
	cl_int ret;

	// if (!krl->args[arg_index] || !krl->sizes[arg_index])
	// 	ft_terminate("Kernel doesn't exist.");
	krl->cpu_srcs[arg_index] = arg_value;
	krl->sizes[arg_index] = arg_size;
	krl->args[arg_index] = NULL;
	return (ret);
}