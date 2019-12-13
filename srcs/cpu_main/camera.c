/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/18 18:50:13 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 19:04:27 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	mouse_mov_switch(t_game *game)
{
	game->cl_info->ret =
	cl_write(game->cl_info, game->cl_info->progs[0].krls[0].args[2],
	sizeof(cl_float3) * (unsigned)WIN_H * (unsigned)WIN_W, game->gpu.vec_temp);
	game->cl_info->ret =
	cl_write(game->cl_info, game->cl_info->progs[0].krls[0].args[11],
	sizeof(cl_float3) * (unsigned)WIN_H * (unsigned)WIN_W, game->gpu.vec_temp1);
	game->cl_info->ret = cl_write(game->cl_info,
	game->cl_info->progs[0].krls[0].args[1],
	sizeof(t_obj) * game->obj_quantity, game->gpu.objects);
	game->gpu.samples = 0;
	game->flag = 1;
}

static void	mouse_mov(t_game *game, t_gui *gui)
{
	if (game->flag)
	{
		game->cl_info->ret =
		cl_write(game->cl_info, game->cl_info->progs[0].krls[0].args[2],\
	sizeof(cl_float3) * (unsigned)WIN_H * (unsigned)WIN_W, game->gpu.vec_temp);
		game->cl_info->ret =
		cl_write(game->cl_info, game->cl_info->progs[0].krls[0].args[11],
	sizeof(cl_float3) * (unsigned)WIN_H * (unsigned)WIN_W, game->gpu.vec_temp1);
		game->gpu.samples = 0;
		reconfigure_camera(&game->gpu.camera[game->cam_num]);
		cam_rename(game, gui, game->cam_num);
		if (gui->c_c.show && game->keys.show_gui\
		&& game->cam_num == gui->c_c.cam_id)
		{
			gui->game->ev.button.button = SDL_BUTTON_LEFT;
			cam_click(gui->c_s.buttons[game->cam_num], 0);
			cam_click(gui->c_s.buttons[game->cam_num], 0);
		}
	}
	else if (gui->flag)
		mouse_mov_switch(game);
	else if (game->keys.space || game->keys.r)
		game->flag = 1;
}

static void	c_r(t_game *game, t_gui *gui)
{
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
	if (game->mouse.rmb && game->mouse.mm && !gui->over_gui)
	{
		rotate_horizontal(&(game->gpu.camera[game->cam_num]),
		-game->gpu.camera[game->cam_num].fov / WIN_W * game->keys.xrel);
		rotate_vertical(&(game->gpu.camera[game->cam_num]),
		-game->gpu.camera[game->cam_num].fov / WIN_H * -game->keys.yrel);
		game->flag = 1;
	}
	mouse_mov(game, gui);
}

static void	cam_rep(t_game *game, t_gui *gui)
{
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
	if (game->keys.e)
	{
		game->gpu.camera[game->cam_num].direction =
		rotate(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction, -M_PI / 60);
		game->flag = 1;
	}
	c_r(game, gui);
}

void		camera_reposition(t_game *game, t_gui *gui)
{
	if (game->keys.ed_box)
		return ;
	if (game->keys.w || (game->mouse.lmb && game->mouse.rmb))
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
	if (game->keys.a)
	{
		game->gpu.camera[game->cam_num].position =
		sum_cfloat3(game->gpu.camera[game->cam_num].position,
		mult_cfloat3(normalize(cross(game->gpu.camera[game->cam_num].normal,
		game->gpu.camera[game->cam_num].direction)), 0.1));
		game->flag = 1;
	}
	cam_rep(game, gui);
}
