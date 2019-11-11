/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:53:01 by lminta            #+#    #+#             */
/*   Updated: 2019/11/10 20:25:07 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			opencl_write_args(t_game *game)
{
	cl_krl_init(&game->kernels[0], 6);
	ERROR(game->cl_info->ret );
	game->kernels[0].sizes[0] = sizeof(cl_int) * (int)WIN_H * (int)WIN_W;
	game->kernels[0].sizes[1] = sizeof(t_obj) * 3;     // fix this
	game->kernels[0].sizes[2] = sizeof(cl_float3) * (int)WIN_H * (int)WIN_W;
	game->kernels[0].sizes[3] = (int)WIN_H * (int)WIN_W * sizeof(cl_ulong);
	game->kernels[0].sizes[4] = sizeof(t_txture) * 3;   //fix this
	game->kernels[0].sizes[5] = sizeof(t_txture) * 3;
	game->cl_info->ret = krl_set_args(game->cl_info->ctxt, &game->kernels[0]);
	ERROR(game->cl_info->ret );
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[0],\
	sizeof(cl_int) * (int)WIN_H * (int)WIN_W, game->sdl.surface->pixels);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[2],\
	sizeof(cl_float3) * (int)WIN_H * (int)WIN_W, game->gpu.vec_temp);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[3],\
	(int)WIN_H * (int)WIN_W * sizeof(cl_ulong), game->gpu.random);
	ERROR(game->cl_info->ret );
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
	ERROR(game->cl_info->ret );
	opencl_write_args(game);
	ERROR(game->cl_info->ret );
}

void				opencl(t_game *game, char *argv)
{
	game->obj_quantity = 0;
	ft_memdel((void **)&game->gpu.camera);
	read_scene(argv, game);
	game->kernels[0].sizes[1] = sizeof(t_obj) * game->obj_quantity;
	game->kernels[0].sizes[4] = sizeof(t_txture)  * game->textures_num;
	game->kernels[0].sizes[5] = sizeof(t_txture) * game->normals_num;
	if (game->kernels[0].sizes[1] != 0)
		game->kernels[0].args[1] = clCreateBuffer(game->cl_info->ctxt,\
		CL_MEM_READ_WRITE, game->kernels[0].sizes[1], NULL, &game->cl_info->ret);
	if (game->kernels[0].sizes[4] != 0)
		game->kernels[0].args[4] = clCreateBuffer(game->cl_info->ctxt,\
		CL_MEM_READ_WRITE, game->kernels[0].sizes[4], NULL, &game->cl_info->ret);
	if (game->kernels[0].sizes[5] != 0)
		game->kernels[0].args[5] = clCreateBuffer(game->cl_info->ctxt,\
		CL_MEM_READ_WRITE, game->kernels[0].sizes[5], NULL, &game->cl_info->ret);
	clSetKernelArg(game->kernels[0].krl, 1, sizeof(game->kernels[0].args[1]),
	(void*)&game->kernels[0].args[1]);
	ERROR(game->cl_info->ret );
	clSetKernelArg(game->kernels[0].krl, 4, sizeof(game->kernels[0].args[4]),
	(void*)&game->kernels[0].args[4]);
	ERROR(game->cl_info->ret );
	clSetKernelArg(game->kernels[0].krl, 5, sizeof(game->kernels[0].args[5]),
	(void*)&game->kernels[0].args[5]);
	ERROR(game->cl_info->ret );
	if (game->kernels[0].sizes[1] != 0)
		game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[1],\
		sizeof(t_obj) * game->obj_quantity, game->gpu.objects);
	if (game->kernels[0].sizes[4] != 0)
		game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[4],\
		sizeof(t_txture) * game->textures_num, game->textures);
	if (game->kernels[0].sizes[5] != 0)
		game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[5],\
		sizeof(t_txture) * game->normals_num, game->normals);
	ERROR(game->cl_info->ret );
}

void				free_opencl(t_game *game)
{
	clReleaseMemObject(game->kernels[0].args[1]);
	clReleaseMemObject(game->kernels[0].args[4]);
	clReleaseMemObject(game->kernels[0].args[5]);
}

