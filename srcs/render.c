/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:54:28 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 16:41:52 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void			ft_run_kernel(t_game *game, t_cl_krl *kernel, int w, int h)
{
	size_t	global[2];

	global[0] = WIN_W;
	global[1] = WIN_H;
	game->gpu.samples += SAMPLES;
	game->cl_info->ret |= clSetKernelArg(kernel->krl, 6, sizeof(cl_int),
	&game->obj_quantity);
	game->cl_info->ret |= clSetKernelArg(kernel->krl, 7, sizeof(cl_int),
	&game->gpu.samples);
	game->cl_info->ret |= clSetKernelArg(kernel->krl, 8, sizeof(t_cam),
	&game->gpu.camera[game->cam_num]);
	game->cl_info->ret |= clSetKernelArg(kernel->krl, 9, sizeof(int),
	&(game->keys.r));
	game->cl_info->ret = cl_krl_exec(game->cl_info, kernel->krl, 2, global);
	clFinish(game->cl_info->cmd_queue);
	game->cl_info->ret = cl_read(game->cl_info, kernel->args[0],
	sizeof(cl_int) * WIN_W * WIN_H, game->sdl.surface->pixels);
}

void			ft_render(t_game *game, t_gui *gui)
{
	if (!game->flag && !gui->flag)
		return ;
	game->flag = 0;
	gui->flag = 0;
	ft_run_kernel(game, &game->cl_info->progs[0].krls[0], WIN_W, WIN_H);
}

void			screen_present(t_game *game, t_gui *gui)
{
	SDL_UpdateTexture(game->sdl.texture, NULL,\
	game->sdl.surface->pixels, game->sdl.surface->w * sizeof(Uint32));
	SDL_RenderCopy(game->sdl.renderer, game->sdl.texture,
	NULL, NULL);
	if (!game->samples_to_do)
		KW_ProcessEvents(gui->gui);
	KW_Paint(gui->gui);
	SDL_RenderPresent(game->sdl.renderer);
}

void			main_render(t_game *game, t_gui *gui)
{
	Uint32		time0;

	time0 = SDL_GetTicks();
	SDL_RenderClear(game->sdl.renderer);
	while (!game->quit && !gui->quit)
	{
		key_check(game);
		camera_reposition(game, gui);
		ft_render(game, gui);
		screen_present(game, gui);
		time0 = samples_to_line(game, gui, time0);
		if (game->samples_to_do && game->samples_to_do <= game->gpu.samples)
		{
			game->samples_to_do = 0;
			game->keys.r = 0;
			game->mouse.lmb = 0;
			net_return(game, gui);
		}
		if (!game->samples_to_do)
			net_wait(game, gui);
		else
			game->keys.r = 1;
	}
	game->av = gui->av;
	free_opencl(game);
}
