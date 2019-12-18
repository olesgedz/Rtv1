/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_program_init_flags.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:47:06 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 19:01:18 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int		cl_program_init_flags(t_cl_prog *program, char *flags)
{
	if (!(program->flags = ft_strdup(flags)))
		ft_malloc_err(sizeof(flags), __FUNCTION__, __FILE__, __LINE__);
	return (0);
}
