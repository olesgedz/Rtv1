/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_program_build_all.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 10:17:56 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 19:00:23 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int	cl_program_build_all(t_cl_info *cl)
{
	cl_int	ret;
	int		i;

	i = 0;
	while (i < cl->n_progs)
		ret = cl_prog_build(cl, &cl->progs[i++]);
	return (ret);
}
