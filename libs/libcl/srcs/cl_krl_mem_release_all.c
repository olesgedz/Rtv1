/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_mem_release_all.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:17:12 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 18:58:07 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int		cl_krl_mem_release_all(t_cl_info *cl, t_cl_krl *krl)
{
	cl_int	ret;
	int		i;

	ret = 0;
	i = 0;
	while (i < krl->nargs)
	{
		ret = cl_krl_mem_release(cl, krl, i++);
	}
	return (ret);
}
