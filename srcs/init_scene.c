/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:53:01 by lminta            #+#    #+#             */
/*   Updated: 2019/11/19 22:32:54 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

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
	game->blured = ft_surface_create(WIN_W, WIN_H);
	cl_init(game->cl_info);
	cl_program_new_push(game->cl_info, "render");
	cl_program_init_sources(&game->cl_info->progs[0], "srcs/cl_files/main.cl");
	cl_program_init_flags(&game->cl_info->progs[0], "-w -I srcs/cl_files/ -I includes/cl_headers/");
	game->cl_info->ret = cl_program_build_all(game->cl_info);

	ERROR(game->cl_info->ret);
	cl_krl_new_push(&game->cl_info->progs[0], "render_kernel");
	// cl_krl_new_push(&game->cl_info->progs[0], "gaussian_blur");
	ERROR(game->cl_info->ret);
	cl_krl_init(&game->cl_info->progs[0].krls[0], 10);
	// cl_krl_init(&game->cl_info->progs[0].krls[1], 5);
	cl_krl_create(game->cl_info, &game->cl_info->progs[0], &game->cl_info->progs[0].krls[0]);
//	cl_krl_create(game->cl_info, &game->cl_info->progs[0], &game->cl_info->progs[0].krls[1]);
}

void				opencl(t_game *game, char *argv)
{
	game->obj_quantity = 0;
	ft_memdel((void **)&game->gpu.camera);
	read_scene(argv, game);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 0, sizeof(cl_int) * WIN_H * WIN_W,\
	game->sdl.surface->pixels);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 1, sizeof(t_obj) * game->obj_quantity,\
	game->gpu.objects);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 2, sizeof(cl_float3) * (int)WIN_H * (int)WIN_W,\
	game->gpu.vec_temp);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 3, (int)WIN_H * (int)WIN_W * sizeof(cl_ulong),\
	game->gpu.random);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 4, sizeof(t_txture) * game->textures_num,\
	game->textures);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 5, sizeof(t_txture) * game->normals_num,\
	game->normals);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 6, sizeof(cl_int),\
	&game->obj_quantity);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 7, sizeof(cl_int),\
	&game->gpu.samples);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 8, sizeof(t_cam),\
	&game->gpu.camera[game->cam_num]);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 9, sizeof(cl_int),\
	&(game->keys.r));
	game->cl_info->ret = cl_krl_mem_create(game->cl_info, &game->cl_info->progs[0].krls[0], 0, CL_MEM_READ_WRITE);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_krl_mem_create(game->cl_info, &game->cl_info->progs[0].krls[0], 1, CL_MEM_READ_WRITE);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_krl_mem_create(game->cl_info, &game->cl_info->progs[0].krls[0], 2, CL_MEM_READ_WRITE);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_krl_mem_create(game->cl_info, &game->cl_info->progs[0].krls[0], 3, CL_MEM_READ_WRITE);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_krl_mem_create(game->cl_info, &game->cl_info->progs[0].krls[0], 4, CL_MEM_READ_WRITE);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_krl_mem_create(game->cl_info, &game->cl_info->progs[0].krls[0], 5, CL_MEM_READ_WRITE);
	ERROR(game->cl_info->ret);
	cl_krl_write_all(game->cl_info, &game->cl_info->progs[0].krls[0]);
	ERROR(game->cl_info->ret);
	cl_krl_set_all_args(&game->cl_info->progs[0].krls[0]);
	ERROR(game->cl_info->ret);


	// cl_krl_init_arg(&game->cl_info->progs[0].krls[1], 0, sizeof(cl_int) * WIN_H * WIN_W,\
	// game->sdl.surface->pixels);
	// cl_krl_init_arg(&game->cl_info->progs[0].krls[1], 1, sizeof(cl_int) * WIN_H * WIN_W,\
	// game->blured->pixels);
	// cl_krl_init_arg(&game->cl_info->progs[0].krls[1], 2, sizeof(cl_int),\
	// game->blured->pixels);
	// cl_krl_init_arg(&game->cl_info->progs[0].krls[1], 3, sizeof(cl_int),\
	// game->blured->pixels);
	// game->cl_info->ret = cl_krl_mem_create(game->cl_info, &game->cl_info->progs[0].krls[1], 0, CL_MEM_READ_WRITE);
	// game->cl_info->ret = cl_krl_mem_create(game->cl_info, &game->cl_info->progs[0].krls[1], 1, CL_MEM_READ_WRITE);
	// cl_krl_write_all(game->cl_info, &game->cl_info->progs[0].krls[1]);
	// ERROR(game->cl_info->ret);
	// cl_krl_set_all_args(&game->cl_info->progs[0].krls[1]);
	// ERROR(game->cl_info->ret);

}

void				free_opencl(t_game *game)
{
	// clReleaseMemObject(game->kernels[0].args[1]);
	// clReleaseMemObject(game->kernels[0].args[4]);
	// clReleaseMemObject(game->kernels[0].args[5]);
}
