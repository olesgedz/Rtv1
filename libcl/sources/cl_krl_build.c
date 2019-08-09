/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_build.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsouchet <bsouchet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/02 22:17:19 by qle-guen          #+#    #+#             */
/*   Updated: 2017/03/01 21:51:37 by bsouchet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "malloc.h"
#include "libgnl.h"
#include "libcl.h"

#define LOG_BUFSIZ 20480

static cl_int
	krl_set_args
	(cl_context ctxt
	, t_cl_krl *krl)
{
	cl_int		ret;
	size_t		i;

	i = 0;
	while (i < krl->nargs)
	{
		krl->args[i] = clCreateBuffer(ctxt, 0, krl->sizes[i], NULL, &ret);
		if (ret != CL_SUCCESS)
			return (ret);
		if ((ret = CL_KRL_ARG(krl->krl, i, krl->args[i])) != CL_SUCCESS)
			return (ret);
		i++;
	}
	return (CL_SUCCESS);
}

static void
	krl_get_opts
	(t_vect *build_line
	, char **krlname
	, char **opts)
{
	char	**split;

	split = (char **)VSPLIT(*build_line, ":");
	*krlname = ft_strdup(split[0]);
	*opts = ft_strdup(split[1]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
}

static void
	krl_source_free
	(t_vect lines
	, char *krlname
	, char *opts)
{
	size_t	i;

	free(krlname);
	free(opts);
	i = 0;
	while (i < lines.used / 8)
	{
		free(((char **)lines.data)[i]);
		i++;
	}
	free(lines.data);
}

cl_int
	cl_krl_build
	(t_cl_info *cl
	, t_cl_krl *krl
	, int fd
	, t_vect *build_line)
{
	char		*krlname;
	char		*opts;
	char		buffer[LOG_BUFSIZ];
	cl_int		ret;
	t_vect		lines;

	krl_get_opts(build_line, &krlname, &opts);
	vect_init(&lines);
	gnl_lines(fd, &lines, GNL_APPEND_CHAR);
	cl->prog = clCreateProgramWithSource(cl->ctxt, lines.used / sizeof(void *),
		(const char **)lines.data, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	if ((ret = clBuildProgram(cl->prog,
		cl->dev_num, &cl->dev_id, opts, NULL, NULL)) != CL_SUCCESS)
	{
		clGetProgramBuildInfo(cl->prog, cl->dev_id, CL_PROGRAM_BUILD_LOG
			, LOG_BUFSIZ, buffer, NULL);
		write(1, buffer, ft_strlen(buffer));
		return (ret);
	}
	if (!(krl->krl = clCreateKernel(cl->prog, krlname, &ret)))
		return (ret);
	krl_source_free(lines, krlname, opts);
	return (krl_set_args(cl->ctxt, krl));
}
