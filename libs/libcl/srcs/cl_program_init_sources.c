/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_program_init_sources.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:45:02 by jblack-b          #+#    #+#             */
/*   Updated: 2019/11/15 17:46:15 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

cl_int cl_program_init_sources(t_cl_prog *program, char *sources)
{
	if (!(program->sources = ft_strdup(sources)))
		ft_malloc_err(sizeof(sources), __FUNCTION__ , __FILE__, __LINE__);
	return (0);
} 