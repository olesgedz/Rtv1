/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_set_all_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:12:06 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 18:58:23 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int	cl_krl_set_all_args(t_cl_krl *krl)
{
	cl_int	ret;
	int		i;

	ret = 0;
	i = 0;
	while (i < krl->nargs)
	{
		ret = cl_krl_set_arg(krl, i++);
		if (ret != 0)
			break ;
	}
	return (ret);
}
