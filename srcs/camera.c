/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:50:13 by lminta            #+#    #+#             */
/*   Updated: 2019/09/25 17:45:08 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
		game->gpu.camera[game->cam_num].direction, -M_PI / 60);
		game->flag = 1;
	}
	if (game->keys.z)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(game->gpu.camera[game->cam_num].normal, 0.1));
		game->flag = 1;
	}
	if (game->keys.x)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(game->gpu.camera[game->cam_num].normal, -0.1));
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
		game->gpu.camera[game->cam_num].direction)), 0.1));
		game->flag = 1;
	}
	if (game->keys.d)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(normalize(cross(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction)), -0.1));
		game->flag = 1;
	}
	if (game->keys.q)
	{
		game->gpu.camera[game->cam_num].direction =
		rotate(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction, M_PI / 60);
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
		mult_cfloat3(game->gpu.camera[game->cam_num].direction, 0.1));
		game->flag = 1;
	}
	if (game->keys.s)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(game->gpu.camera[game->cam_num].direction, -0.1));
		game->flag = 1;
	}
	cam_rep(game, gui);
}
