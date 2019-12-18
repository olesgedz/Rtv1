/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libcl.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 23:31:36 by olesgedz          #+#    #+#             */
/*   Updated: 2019/12/12 18:55:38 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBCL_H
# define LIBCL_H
# include "libft.h"
# include "libvect.h"
# define CL_SILENCE_DEPRECATION
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif
# define LOG_BUFSIZ 20480

typedef struct			s_cl_krl
{
	cl_kernel			krl;
	char				*name;
	cl_mem				*args;
	void				**cpu_srcs;
	size_t				*sizes;
	size_t				nargs;
}						t_cl_krl;

typedef struct			s_cl_prog
{
	char				*name;
	int					fd;
	char				*sources;
	char				*flags;
	int					n_krls;
	cl_program			program;
	t_cl_krl			*krls;
}						t_cl_prog;

typedef struct			s_cl_info
{
	cl_platform_id		pl_id;
	cl_device_id		dev_id;
	cl_context			ctxt;
	cl_command_queue	cmd_queue;
	t_cl_prog			*progs;
	int					n_progs;
	cl_uint				dev_num;
	cl_int				ret;
}						t_cl_info;

cl_int					cl_write
	(t_cl_info *cl, cl_mem mem, size_t size, void *data);
void					cl_krl_init(t_cl_krl *krl, size_t nargs);
cl_int					cl_init(t_cl_info *cl);
cl_int					cl_program_new_push(t_cl_info *cl, char *name);
cl_int					cl_krl_exec
	(t_cl_info *cl, cl_kernel krl, cl_uint work_dim, size_t *work_size);
cl_int					cl_read
	(t_cl_info *cl, cl_mem mem, size_t size, void *data);
t_cl_prog				*cl_program_get_by_name(t_cl_info *cl, char *name);
cl_int					cl_program_new_push(t_cl_info *cl, char *name);
cl_int					cl_program_init_sources(t_cl_prog *program,\
char *sources);
cl_int					cl_program_init_flags(t_cl_prog *program, char *flags);
void					cl_program_build_inf(t_cl_info *cl, t_cl_prog *prog);
cl_int					cl_prog_build(t_cl_info *cl, t_cl_prog *prog);
cl_int					cl_krl_new_push(t_cl_prog *prog, char *name);
cl_int					cl_krl_init_arg(t_cl_krl *krl,\
	cl_uint arg_index, size_t arg_size, void *arg_value);
cl_int					cl_krl_mem_create(t_cl_info *cl, t_cl_krl *krl,\
cl_uint					arg_index, cl_mem_flags flag);
cl_int					cl_krl_set_arg(t_cl_krl *krl, int index);
cl_int					cl_krl_create(t_cl_info *cl,\
t_cl_prog *prog, t_cl_krl *krl);
cl_int					cl_krl_set_all_args(t_cl_krl *krl);
cl_int					cl_program_build_all(t_cl_info *cl);
cl_int					cl_krl_write_all(t_cl_info *cl, t_cl_krl *krl);
cl_int					cl_krl_mem_release(t_cl_info *cl, t_cl_krl *krl,\
	cl_uint arg_index);
cl_int					cl_krl_mem_release_all(t_cl_info *cl, t_cl_krl *krl);

#endif
