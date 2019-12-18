/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_program_build_inf.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 17:48:07 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/12 19:00:52 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libcl.h"

void	cl_program_build_inf(t_cl_info *cl, t_cl_prog *prog)
{
	char		buffer[LOG_BUFSIZ];

	clGetProgramBuildInfo(prog->program, cl->dev_id, CL_PROGRAM_BUILD_LOG
			, LOG_BUFSIZ, buffer, NULL);
	write(1, buffer, ft_strlen(buffer));
}
