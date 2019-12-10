/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_return.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 21:33:44 by lminta            #+#    #+#             */
/*   Updated: 2019/12/10 23:14:40 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	serv_side(t_game *game, t_gui *gui, int len)
{
	int		current;
	int		i;
	int		all;
	char	buff[WIN_W];

	i = -1;
	while (++i < gui->n.clients)
	{
		all = 0;
		while (all <= len)
		{
			current = 0;
			current = SDLNet_TCP_Recv(gui->n.client[i], buff, WIN_W);
			ft_memcpy(game->gpu.vec_temp1 + all, buff, current);
			all += current;
		}
	}
}

void		net_return(t_game *game, t_gui *gui)
{
	int		len;

	len = sizeof(cl_float3) * (int)WIN_H * (int)WIN_W;
	if (!game->server)
	{
		game->cl_info->ret = cl_read(game->cl_info,
	game->cl_info->progs[0].krls[0].args[2], len, game->gpu.vec_temp);
		SDLNet_TCP_Send(gui->n.tcpsock, game->gpu.vec_temp, len);
	}
	else
		serv_side(game, gui, len);
}
