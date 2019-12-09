/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_srv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 21:14:07 by lminta            #+#    #+#             */
/*   Updated: 2019/12/09 17:16:58 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		server_on(KW_Widget *widget, int b)
{
	t_gui		*gui;
	KW_Widget	*wid;

	wid = KW_GetButtonLabel(widget);
	b = 0;
	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	gui->game->server = !gui->game->server;
	if (gui->game->server)
	{
		KW_SetLabelText(wid, "Server");
		// free(gui->n.str_ip);
		// gui->n.str_ip = 0;
		// SDLNet_TCP_Close(gui->n.tcpsock);
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

static void	client_side(t_game *game, t_gui *gui)
{
	char		message[FILE_SIZE];
	FILE		*fp;
	char		**buff;

	SDLNet_TCP_Recv(gui->n.tcpsock, message, FILE_SIZE);
	if (!ft_strcmp(message, "ping!"))
		return ;
	buff = ft_strsplit(message, '|');
	if (!(fp = fopen(buff[0], "w")))
		exit(0);
	game->samples_to_do = ft_atoi(buff[1]);
	fprintf(fp, "%s", buff[2]);
	fclose(fp);
	free(gui->av);
	gui->av = buff[0];
	gui->quit = 1;
	free(buff[1]);
	free(buff[2]);
	free(buff);
}

void		send_ping(t_game *game, t_gui *gui)
{
	int	i;

	i = 0;
	while (i < gui->n.clients)
	{
		SDLNet_TCP_Send(gui->n.client[i], "ping!", 6);
		i++;
	}
}

void		net_wait(t_game *game, t_gui *gui)
{
	char	*buff;
	char	*ita;

	if (!gui->game->server && gui->n.str_ip)
		client_side(game, gui);
	else if (gui->game->server)
	{
		gui->n.client[gui->n.clients] = SDLNet_TCP_Accept(gui->n.server);
		send_ping(game, gui);
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
}

void		send_map(t_game *game, t_gui *gui, char *tmp, int smpls)
{
	int		i;
	int		len;
	char	*name;

	if (!gui->game->server)
		return ;
	if (!(name = dumper(game, gui)))
		exit(0);
	i = -1;
	tmp = make_string(name, smpls, 0);
	len = ft_strlen(tmp);
	while (++i < gui->n.clients)
		SDLNet_TCP_Send(gui->n.client[i], tmp, len + 1);
	free(tmp);
	free(gui->av);
	gui->av = name;
	gui->quit = 1;
}
