/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:54:28 by lminta            #+#    #+#             */
/*   Updated: 2019/09/23 15:38:41 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

 void	ft_run_kernel(t_game *game, cl_kernel kernel)
 {
	int w = WIN_W;
	int h = WIN_H;
	size_t global = WIN_W * WIN_H;
	game->gpu.samples += SAMPLES;
	const size_t count = global;
	game->cl_info->ret |= clSetKernelArg(kernel, 5, sizeof(cl_int), &w);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 6, sizeof(cl_int), &h);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 7, sizeof(cl_int), &game->obj_quantity);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 8, sizeof(cl_int), &game->gpu.samples);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 9, sizeof(t_cam), &game->gpu.camera[game->cam_num]);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_krl_exec(game->cl_info, kernel, 1, &global);
	ERROR(game->cl_info->ret);
	clFinish(game->cl_info->cmd_queue);
	game->cl_info->ret = cl_read(game->cl_info, game->kernels->args[0], sizeof(cl_int) * count, game->gpuOutput);
	ERROR(game->cl_info->ret);
 }

void	ft_render(t_game *game)
{
	if(!game->flag)
		return ;
	game->flag = 0;
	ft_run_kernel(game, game->kernels[0].krl);
	game->sdl.surface->data =  (Uint32 *)game->gpuOutput;
}

void	poopa(t_game *game, t_gui *gui)
{
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	ft_surface_clear(game->sdl.surface);
	while(!game->quit)
	{
		key_check(game);
		camera_reposition(game);
		ft_render(game);
		// KW_ProcessEvents(gui->gui);
		// KW_Paint(gui->gui);
		ft_surface_present(&game->sdl, game->sdl.surface);
	}
}
