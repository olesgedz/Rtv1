/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:53:01 by lminta            #+#    #+#             */
/*   Updated: 2019/10/22 17:55:57 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	init_scene(t_game *game, char *argv)
{
	game->gpu.camera = NULL;
	read_scene(argv, game);
}

void		opencl(t_game *game, char *argv)
{
	game->kernels = ft_memalloc(sizeof(t_cl_krl) * 2);
	game->cl_info = ft_memalloc(sizeof(t_cl_info));
	game->gpuOutput = ft_memalloc(sizeof(int) * WIN_H * WIN_W);
	// game->gpu.objects = ft_memalloc(sizeof(t_obj) * 9);
	game->gpu.objects = NULL;
	game->gpu.vec_temp = ft_memalloc(sizeof(cl_float3) * WIN_H * WIN_W);
	game->gpu.random = get_random(game->gpu.random);
	game->gpu.samples = 0;
	game->cam_num = 0;
	init_scene(game, argv);
	cl_init(game->cl_info);
	ERROR(game->cl_info->ret);
	int fd = open("srcs/cl_files/main.cl", O_RDONLY);
	cl_krl_init(&game->kernels[0], 5);
	game->kernels[0].sizes[0] = sizeof(cl_int) * WIN_H * WIN_W;
	game->kernels[0].sizes[1] =  sizeof(t_obj) * game->obj_quantity;
	game->kernels[0].sizes[2] = sizeof(cl_float3) * WIN_H * WIN_W;
	game->kernels[0].sizes[3] = WIN_H * WIN_W * sizeof(cl_ulong);
	game->kernels[0].sizes[4] = sizeof(t_txture) * game->textures_num;

	t_vect names;
	vect_init(&names);
	VECT_STRADD(&names, "render_kernel");
	game->cl_info->ret = cl_krl_build(game->cl_info, game->kernels, fd, "-Werror -I srcs/cl_files/ -I includes/cl_headers/", &names);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[0], sizeof(cl_int) * WIN_H * WIN_W, game->gpuOutput);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[1], sizeof(t_obj) * game->obj_quantity, game->gpu.objects);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game->gpu.vec_temp);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[3], WIN_H * WIN_W * sizeof(cl_ulong), game->gpu.random);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[4], sizeof(t_txture) * game->textures_num, game->textures);
	ERROR(game->cl_info->ret);
}

void	free_shit(t_game *game)
{
	free(game->kernels);
	free(game->cl_info);
	free(game->gpuOutput);
	free(game->gpu.vec_temp);
	free(game->gpu.random);
	free(game->textures);
}
