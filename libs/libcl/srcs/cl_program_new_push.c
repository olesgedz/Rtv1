/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_program_new_push.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:25:35 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 19:02:36 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int		cl_program_new_push(t_cl_info *cl, char *name)
{
	cl->n_progs++;
	cl->progs = ft_realloc(cl->progs, sizeof(t_cl_prog) * cl->n_progs);
	cl->progs[cl->n_progs - 1].name = ft_strdup(name);
	cl->progs[cl->n_progs - 1].krls = 0;
	cl->progs[cl->n_progs - 1].n_krls = 0;
	return (0);
}
