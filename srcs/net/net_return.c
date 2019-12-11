/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_return.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 21:33:44 by lminta            #+#    #+#             */
/*   Updated: 2019/12/11 16:34:52 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			summator(cl_float3 *dest, cl_float3 *src, int len)
{
	int	i;

	i = -1;
	while (++i < len)
	{
		dest[i].s[0] += src[i].s[0];
		dest[i].s[1] += src[i].s[1];
		dest[i].s[2] += src[i].s[2];
	}
}

static cl_float3	*fill_tmp(t_game *game, int len)
{
	cl_float3	*tmp;

	tmp = (cl_float3 *)malloc(len);
	game->cl_info->ret = cl_read(game->cl_info,
	game->cl_info->progs[0].krls[0].args[2], len, tmp);
	return (tmp);
}

static void			serv_side(t_game *game, t_gui *gui, int len)
{
	int			current;
	int			i;
	int			all;
	cl_float3	buff[WIN_W];
	cl_float3	*tmp;

	i = -1;
	game->gpu.samples *= gui->n.clients + 1;
	tmp = fill_tmp(game, len);
	while (++i < gui->n.clients)
	{
		all = 0;
		while (all < len)
		{
			current = 0;
			current = SDLNet_TCP_Recv(gui->n.client[i],
			buff, sizeof(cl_float3) * WIN_W);
			summator(game->gpu.vec_temp + current, buff,
			current / sizeof(cl_float3));
			all += current;
		}
	}
	game->cl_info->ret = cl_write(game->cl_info,
	game->cl_info->progs[0].krls[0].args[2], len, tmp);
	ft_run_kernel(game, &game->cl_info->progs[0].krls[0], WIN_W, WIN_H);
	screen_present(game, gui);
	free(tmp);
}

void				net_return(t_game *game, t_gui *gui)
{
	int		len;

	len = sizeof(cl_float3) * (int)WIN_H * (int)WIN_W;
	if (!game->server && gui->n.str_ip)
	{
		game->cl_info->ret = cl_read(game->cl_info,
	game->cl_info->progs[0].krls[0].args[2], len, game->gpu.vec_temp);
		SDLNet_TCP_Send(gui->n.tcpsock, game->gpu.vec_temp, len);
	}
	else if (game->server && gui->n.clients)
		serv_side(game, gui, len);
}
