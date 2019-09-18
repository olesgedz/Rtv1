/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:50:13 by lminta            #+#    #+#             */
/*   Updated: 2019/09/18 22:22:26 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	mouse_mov(t_game *game, int flag)
{
	if (game->keys.lmb && game->keys.mm)
	{
		game->gpu.samples = 0;
		game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[2],
		sizeof(cl_float3) * WIN_H * WIN_W, game->gpu.vec_temp);
		rotate_horizontal(&(game->gpu.camera[game->cam_num]),
		game->gpu.camera[game->cam_num].fov / WIN_W * game->keys.xrel);
		rotate_vertical(&(game->gpu.camera[game->cam_num]),
		game->gpu.camera[game->cam_num].fov /WIN_H * -game->keys.yrel);
		reconfigure_camera(&game->gpu.camera[game->cam_num]);
		ft_render(game);
	}
	if (flag)
	{
		game->gpu.samples = 0;
		reconfigure_camera(&game->gpu.camera[game->cam_num]);
		ft_render(game);
	}
	else if (game->keys.space)
		ft_render(game);
}

static void	c_r(t_game *game, int flag)
{
	if (game->keys.e)
	{
		game->gpu.camera[game->cam_num].direction =
		rotate(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction, -M_PI / 60);
		flag = 1;
	}
	if (game->keys.z)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(game->gpu.camera[game->cam_num].normal, 0.1));
		flag = 1;
	}
	if (game->keys.x)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(game->gpu.camera[game->cam_num].normal, -0.1));
		flag = 1;
	}
	mouse_mov(game, flag);
}

static void	cam_rep(t_game *game, int flag)
{
	if (game->keys.a)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(normalize(cross(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction)), 0.1));
		flag = 1;
	}
	if (game->keys.d)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(normalize(cross(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction)), -0.1));
		flag = 1;
	}
	if (game->keys.q)
	{
		game->gpu.camera[game->cam_num].direction =
		rotate(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction, M_PI / 60);
		flag = 1;
	}
	c_r(game, flag);
}

void		camera_reposition(t_game *game)
{
	int flag;

	flag = 0;
	game->cl_info->ret =
	cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) *
	(unsigned)WIN_H * (unsigned)WIN_W, game->gpu.vec_temp);
	ERROR(game->cl_info->ret);
	if (game->keys.w)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(game->gpu.camera[game->cam_num].direction, 0.1));
		flag = 1;
	}
	if (game->keys.s)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(game->gpu.camera[game->cam_num].direction, -0.1));
		flag = 1;
	}
	cam_rep(game, flag);
}
