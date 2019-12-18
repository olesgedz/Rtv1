/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_program_get_by_name.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:39:35 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 19:00:58 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

t_cl_prog	*cl_program_get_by_name(t_cl_info *cl, char *name)
{
	int i;

	while (i < cl->n_progs)
	{
		if (!ft_strcmp(cl->progs[i].name, name))
			return (&cl->progs[i]);
	}
	return (NULL);
}
