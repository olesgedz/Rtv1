/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_write_all.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:19:25 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 18:59:47 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int	cl_krl_write_all(t_cl_info *cl, t_cl_krl *krl)
{
	cl_int	ret;
	int		i;

	ret = 0;
	i = 0;
	while (i < krl->nargs)
	{
		if (krl->args[i] != NULL)
			ret = cl_write(cl, krl->args[i],\
			krl->sizes[i], krl->cpu_srcs[i]);
		i++;
	}
	return (ret);
}
