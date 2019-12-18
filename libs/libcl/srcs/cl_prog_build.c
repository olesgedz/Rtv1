/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_prog_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:49:37 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 19:03:45 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"
#include "libgnl.h"
#include <fcntl.h>

static void		prog_source_free(t_vect *lines)
{
	size_t	i;

	i = 0;
	while (i < lines->used / 8)
	{
		free(((char **)lines->data)[i]);
		i++;
	}
	free(lines->data);
}

cl_int			cl_prog_build(t_cl_info *cl, t_cl_prog *prog)
{
	cl_int		ret;
	t_vect		*lines;

	lines = ft_memalloc(sizeof(t_vect));
	vect_init(lines);
	if ((prog->fd = open(prog->sources, O_RDONLY)) < 3)
		ft_terminate("Can't open file\n");
	gnl_lines(prog->fd, lines, GNL_APPEND_CHAR);
	prog->program = clCreateProgramWithSource(cl->ctxt,
	lines->used / sizeof(void *),
	(const char **)lines->data, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	if ((ret = clBuildProgram(prog->program,
		cl->dev_num, &cl->dev_id, prog->flags, NULL, NULL)) != CL_SUCCESS)
	{
		cl_program_build_inf(cl, prog);
		return (ret);
	}
	prog_source_free(lines);
	ft_memdel((void**)&lines);
	return (ret);
}
