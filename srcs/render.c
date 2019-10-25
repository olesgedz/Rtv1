/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:54:28 by lminta            #+#    #+#             */
/*   Updated: 2019/10/25 22:19:56 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void		ft_run_kernel(t_game *game, cl_kernel kernel, int w, int h)
{
	size_t global;

	game->gpu.samples += SAMPLES;
	global = WIN_W * WIN_H;
	game->cl_info->ret |= clSetKernelArg(kernel, 6, sizeof(cl_int), &w);
	ERROR(game->cl_info->ret );
	game->cl_info->ret |= clSetKernelArg(kernel, 7, sizeof(cl_int), &h);
	game->cl_info->ret |= clSetKernelArg(kernel, 8, sizeof(cl_int),
	&game->obj_quantity);
	game->cl_info->ret |= clSetKernelArg(kernel, 9, sizeof(cl_int),
	&game->gpu.samples);
	game->cl_info->ret |= clSetKernelArg(kernel, 10, sizeof(t_cam),
	&game->gpu.camera[game->cam_num]);
	ERROR(game->cl_info->ret );
	game->cl_info->ret = cl_krl_exec(game->cl_info, kernel, 1, &global);
	ERROR(game->cl_info->ret );
	clFinish(game->cl_info->cmd_queue);
	game->cl_info->ret = cl_read(game->cl_info, game->kernels->args[0],
	sizeof(cl_int) * WIN_W * WIN_H, game->sdl.surface->data);
	ERROR(game->cl_info->ret );
}

static void		ft_render(t_game *game, t_gui *gui)
{
	if (!game->flag && !gui->flag)
		return ;
	game->flag = 0;
	gui->flag = 0;
	ft_run_kernel(game, game->kernels[0].krl, WIN_W, WIN_H);
}

static void		screen_present(t_game *game, t_gui *gui)
{
	SDL_UpdateTexture(game->sdl.texture->sdl_texture, NULL,\
	game->sdl.surface->data, game->sdl.surface->width * sizeof(Uint32));
	SDL_RenderCopy(game->sdl.renderer, game->sdl.texture->sdl_texture,
	NULL, NULL);
	KW_ProcessEvents(gui->gui);
	KW_Paint(gui->gui);
	SDL_RenderPresent(game->sdl.renderer);
}

void			main_render(t_game *game, t_gui *gui)
{
	SDL_RenderClear(game->sdl.renderer);
	while (!game->quit && !gui->quit)
	{
		key_check(game);
		camera_reposition(game, gui);
		ft_render(game, gui);
		screen_present(game, gui);
	}
	game->av = gui->av;
	free_opencl(game);
}
