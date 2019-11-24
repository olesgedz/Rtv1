/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_new_push.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:50:57 by jblack-b          #+#    #+#             */
/*   Updated: 2019/11/24 21:52:04 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int		cl_krl_new_push(t_cl_prog *prog, char *name)
{
	prog->n_krls++;
	prog->krls = realloc(prog->krls, sizeof(t_cl_krl) * prog->n_krls);
	prog->krls[prog->n_krls - 1].name = ft_strdup(name);
	return (0);
}
