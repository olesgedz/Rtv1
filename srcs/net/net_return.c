/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_return.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 21:33:44 by lminta            #+#    #+#             */
/*   Updated: 2019/12/12 18:33:09 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void			summator(cl_float3 *dest, cl_float3 *src, int len)
{
	int	i;

	i = -1;
	len = len / sizeof(cl_float3);
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

static void			line_create(char *dest, char *src, int len)
{
	int	i;

	i = -1;
	while (++i < len)
		dest[i] = src[i];
}

static void			serv_side(t_game *game, t_gui *gui, int len, cl_float3 *tmp)
{
	int			current;
	int			i;
	int			all;
	char		buff[2000];
	char		*tmp_str;

	i = -1;
	game->gpu.samples *= gui->n.clients + 1;
	tmp_str = (char *)malloc(len);
	while (++i < gui->n.clients)
	{
		all = 0;
		while (all < len)
		{
			current = 0;
			current = SDLNet_TCP_Recv(gui->n.client[i], buff, 2000);
			line_create(&tmp_str[all], buff, current);
			all += current;
		}
		summator(tmp, (cl_float3 *)tmp_str, len);
	}
	game->cl_info->ret = cl_write(game->cl_info,
	game->cl_info->progs[0].krls[0].args[2], len, tmp);
	ft_run_kernel(game, &game->cl_info->progs[0].krls[0], WIN_W, WIN_H);
	screen_present(game, gui);
}

void				net_return(t_game *game, t_gui *gui)
{
	int			len;
	cl_float3	*tmp;

	len = sizeof(cl_float3) * (int)WIN_H * (int)WIN_W;
	tmp = fill_tmp(game, len);
	if (!game->server && gui->n.str_ip)
		SDLNet_TCP_Send(gui->n.tcpsock, tmp, len);
	else if (game->server && gui->n.clients)
		serv_side(game, gui, len, tmp);
	free(tmp);
}
