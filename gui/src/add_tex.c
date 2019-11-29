/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_tex.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 20:53:26 by lminta            #+#    #+#             */
/*   Updated: 2019/11/29 21:50:57 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	push_tex(t_game *game, char *res)
{
	ft_texture_push(game, &(game->texture_list), res);
	game->textures =
	realloc(game->textures, sizeof(t_txture) * game->textures_num);
	get_texture(res, &(game->textures[game->textures_num - 1]), "./textures/");
	clReleaseMemObject(game->cl_info->progs[0].krls[0].args[4]);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 4,
	sizeof(t_txture) * game->textures_num, game->textures);
	cl_krl_mem_create(game->cl_info, &game->cl_info->progs[0].krls[0],
	4, CL_MEM_READ_WRITE);
	cl_krl_set_arg(&game->cl_info->progs[0].krls[0], 4);
	cl_write(game->cl_info, game->cl_info->progs[0].krls[0].args[4],
	sizeof(t_txture) * game->textures_num, game->textures);
}

void	push_normal(t_game *game, char *res)
{
	ft_normal_push(game, &(game->texture_list), res);
	game->normals =
	realloc(game->normals, sizeof(t_txture) * game->normals_num);
	get_texture(res, &(game->normals[game->normals_num - 1]), "./normals/");
	clReleaseMemObject(game->cl_info->progs[0].krls[0].args[5]);
	cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 5,
	sizeof(t_txture) * game->normals_num, game->normals);
	cl_krl_mem_create(game->cl_info, &game->cl_info->progs[0].krls[0],
	5, CL_MEM_READ_WRITE);
	cl_krl_set_arg(&game->cl_info->progs[0].krls[0], 5);
	cl_write(game->cl_info, game->cl_info->progs[0].krls[0].args[5],
	sizeof(t_txture) * game->normals_num, game->normals);
}
