/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:53:01 by lminta            #+#    #+#             */
/*   Updated: 2019/10/23 22:44:14 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void			opencl_write_args(t_game *game)
{
	cl_krl_init(&game->kernels[0], 5);
	game->kernels[0].sizes[0] = sizeof(cl_int) * (int)WIN_H * (int)WIN_W;
	game->kernels[0].sizes[1] = sizeof(t_obj) * 3;
	game->kernels[0].sizes[2] = sizeof(cl_float3) * (int)WIN_H * (int)WIN_W;
	game->kernels[0].sizes[3] = (int)WIN_H * (int)WIN_W * sizeof(cl_ulong);
	game->kernels[0].sizes[4] = sizeof(t_txture) * game->textures_num;
	game->cl_info->ret = krl_set_args(game->cl_info->ctxt, &game->kernels[0]);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[0],\
	sizeof(cl_int) * (int)WIN_H * (int)WIN_W, game->sdl.surface->data);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[2],\
	sizeof(cl_float3) * (int)WIN_H * (int)WIN_W, game->gpu.vec_temp);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[3],\
	(int)WIN_H * (int)WIN_W * sizeof(cl_ulong), game->gpu.random);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[4],\
	sizeof(t_txture) * game->textures_num, game->textures);
}

void				opencl_init(t_game *game)
{
	int fd;

	game->kernels = ft_memalloc(sizeof(t_cl_krl) * 2);
	game->cl_info = ft_memalloc(sizeof(t_cl_info));
	game->gpu.objects = NULL;
	game->gpu.vec_temp = ft_memalloc(sizeof(cl_float3)\
	* (int)WIN_H * (int)WIN_W);
	game->gpu.random = get_random(game->gpu.random);
	game->gpu.samples = 0;
	game->cam_num = 0;
	game->gpu.camera = NULL;
	game->cl_info->krl_names = ft_memalloc(sizeof(t_vect));
	vect_init(game->cl_info->krl_names);
	vect_str_add(game->cl_info->krl_names, "render_kernel");
	cl_init(game->cl_info);
	fd = open("srcs/cl_files/main.cl", O_RDONLY);
	game->cl_info->ret = cl_prog_build(game->cl_info, game->kernels, fd,\
	"-w -I srcs/cl_files/ -I includes/cl_headers/");
	game->cl_info->ret = cl_krl_build(game->cl_info,\
	game->kernels, game->cl_info->krl_names);
	opencl_write_args(game);
}

void				opencl(t_game *game, char *argv)
{
	game->obj_quantity = 0;
	ft_memdel((void **)&game->gpu.camera);
	read_scene(argv, game);
	game->kernels[0].sizes[1] = sizeof(t_obj) * game->obj_quantity;
	game->kernels[0].args[1] = clCreateBuffer(game->cl_info->ctxt,\
	CL_MEM_READ_WRITE, game->kernels[0].sizes[1], NULL, &game->cl_info->ret);
	clSetKernelArg(game->kernels[0].krl, 1, sizeof(game->kernels[0].args[1]),
	(void*)&game->kernels[0].args[1]);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[1],\
	sizeof(t_obj) * game->obj_quantity, game->gpu.objects);
}

void				free_opencl(t_game *game)
{
	clReleaseMemObject(game->kernels[0].args[1]);
}

