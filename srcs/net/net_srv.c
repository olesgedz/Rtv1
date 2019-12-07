/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_srv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 21:14:07 by lminta            #+#    #+#             */
/*   Updated: 2019/12/07 23:00:06 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	server_on(KW_Widget *widget, int b)
{
	t_gui		*gui;
	KW_Widget	*wid;
	static int	i = 0;

	wid = KW_GetButtonLabel(widget);
	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	gui->game->server = !gui->game->server;
	if (gui->game->server)
	{
		KW_SetLabelText(wid, "Server");
		if ((SDLNet_ResolveHost(&gui->n.ip, NULL, 9999)) == -1)
			exit(0);
		if (!(gui->n.server = SDLNet_TCP_Open(&gui->n.ip)))
			exit(0);
	}
	else
	{
		KW_SetLabelText(wid, "Client");
		SDLNet_TCP_Close(gui->n.server);
		while (gui->n.clients)
			SDLNet_TCP_Close(gui->n.client[--gui->n.clients]);
		KW_SetLabelText(gui->ed_w.label, "Enter host's IP");
	}
}

void	net_wait(t_game *game, t_gui *gui)
{
	char	*buff;
	char	*ita;

	if (!gui->game->server)
		return ;
	gui->n.client[gui->n.clients] = SDLNet_TCP_Accept(gui->n.server);
	if (gui->n.client[gui->n.clients] && gui->n.clients < MAX_CL)
	{
		gui->n.clients++;
		ita = ft_itoa(gui->n.clients);
		buff = ft_strjoin("Connected - ", ita);
		free(ita);
		KW_SetLabelText(gui->ed_w.label, buff);
		free(buff);
		//gui->n.remoteip = SDLNet_TCP_GetPeerAddress(gui->n.client);
	}
}
