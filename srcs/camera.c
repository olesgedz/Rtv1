/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:50:13 by lminta            #+#    #+#             */
/*   Updated: 2019/10/21 18:36:57 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		pos_check(t_gui *gui)
{
	int	tx = 0;
	int	ty = 0;

	SDL_GetMouseState(&tx, &ty);
	gui->over_gui = 0;
	if (tx > gui->s_s.frect.x && tx < gui->s_s.frect.x + gui->s_s.frect.w)
		if (ty > gui->s_s.frect.y && ty < gui->s_s.frect.y + gui->s_s.frect.h)
			gui->over_gui = 1;
	if (tx > gui->o_s.frect.x && tx < gui->o_s.frect.x + gui->o_s.frect.w)
		if (ty > gui->o_s.frect.y && ty < gui->o_s.frect.y + gui->o_s.frect.h)
			gui->over_gui = 1;
	if (gui->over_gui)
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	else
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
}

static void	mouse_mov(t_game *game, t_gui *gui)
{
	if (game->keys.lmb && game->keys.mm && !gui->over_gui)
	{
		rotate_horizontal(&(game->gpu.camera[game->cam_num]),
		game->gpu.camera[game->cam_num].fov / WIN_W * game->keys.xrel);
		rotate_vertical(&(game->gpu.camera[game->cam_num]),
		game->gpu.camera[game->cam_num].fov /WIN_H * -game->keys.yrel);
		game->flag = 1;
	}
	if (game->flag)
	{
		game->cl_info->ret =
		cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) *
		(unsigned)WIN_H * (unsigned)WIN_W, game->gpu.vec_temp);
		ERROR(game->cl_info->ret);
		game->gpu.samples = 0;
		reconfigure_camera(&game->gpu.camera[game->cam_num]);
	}
	else if (gui->flag)
	{
		game->cl_info->ret =
		cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) *
		(unsigned)WIN_H * (unsigned)WIN_W, game->gpu.vec_temp);
		ERROR(game->cl_info->ret);
		game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[1],
		sizeof(t_obj) * game->obj_quantity, game->gpu.objects);
		ERROR(game->cl_info->ret);
		game->gpu.samples = 0;
		game->flag = 1;
	}
	else if (game->keys.space)
		game->flag = 1;
}

static void	c_r(t_game *game, t_gui *gui)
{
	if (game->keys.e)
	{
		game->gpu.camera[game->cam_num].direction =
		rotate(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction, (float)(-M_PI) / 60);
		game->flag = 1;
	}
	if (game->keys.z)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(game->gpu.camera[game->cam_num].normal, 0.1f));
		game->flag = 1;
	}
	if (game->keys.x)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(game->gpu.camera[game->cam_num].normal, -0.1f));
		game->flag = 1;
	}
	mouse_mov(game, gui);
}

static void	cam_rep(t_game *game, t_gui *gui)
{
	if (game->keys.a)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(normalize(cross(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction)), 0.1f));
		game->flag = 1;
	}
	if (game->keys.d)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(normalize(cross(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction)), -0.1f));
		game->flag = 1;
	}
	if (game->keys.q)
	{
		game->gpu.camera[game->cam_num].direction =
		rotate(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction, (float)(M_PI) / 60);
		game->flag = 1;
	}
	c_r(game, gui);
}

void		camera_reposition(t_game *game, t_gui *gui)
{
	if (game->keys.w)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(game->gpu.camera[game->cam_num].direction, 0.1f));
		game->flag = 1;
	}
	if (game->keys.s)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(game->gpu.camera[game->cam_num].direction, -0.1f));
		game->flag = 1;
	}
	cam_rep(game, gui);
}
