/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_new_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:50:57 by jblack-b          #+#    #+#             */
/*   Updated: 2019/11/15 17:51:26 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int		cl_krl_new_push(t_cl_prog *prog, char *name)
{
	prog->n_krls++;
	prog->krls = ft_realloc(prog->krls, sizeof(t_cl_krl) * prog->n_krls);
	prog->krls[prog->n_krls - 1].name = ft_strdup(name);
	return (0);
}
