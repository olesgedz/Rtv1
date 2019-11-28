/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_create.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:57:21 by jblack-b          #+#    #+#             */
/*   Updated: 2019/11/15 17:57:37 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int				cl_krl_create(t_cl_info *cl, t_cl_prog *prog, t_cl_krl *krl)
{
	cl_int			ret;

	krl->krl =  clCreateKernel(prog->program, krl->name, &ret); 
	return (ret);
}