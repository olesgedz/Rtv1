/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_srv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 21:14:07 by lminta            #+#    #+#             */
/*   Updated: 2019/12/08 20:29:51 by lminta           ###   ########.fr       */
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
		SDLNet_TCP_Close(gui->n.tcpsock);
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
	static FILE	*fp = 0;

	SDLNet_TCP_Recv(gui->n.tcpsock, message, FILE_SIZE);
	printf("%s\n", message);
	if (ft_strstr(message, "ping!"))
	{
		//printf("ping\n");
		return ;
	}
	if (ft_strstr(message, ".json"))
	{
		printf("json\n");
		if (!(fp = fopen(message, "w")))
			exit(0);
	}
	else if (ft_strstr(message, "smpl"))
	{
		printf("smpls\n");
		game->samples_to_do = ft_atoi(message);
	}
	else if (fp)
	{
		printf("map\n");
		fprintf(fp, "%s", message);
		fclose(fp);
		fp = 0;
		free(gui->av);
		gui->av = ft_strdup(message);
		gui->quit = 1;
	}
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

void		send_map(t_game *game, t_gui *gui)
{
	int		i;
	int		len;
	int		fd;
	char	*name;
	char	buff[FILE_SIZE];

	if (!gui->game->server)
		return ;
	if (!(name = dumper(game, gui)))
		exit(0);
	i = -1;
	len = strlen(name);
	while (++i < gui->n.clients)
		if (!(SDLNet_TCP_Send(gui->n.client[i], name, len + 1)))
			exit(0);
	fd = open(name, O_RDONLY);
	len = read(fd, buff, FILE_SIZE);
	buff[len] = 0;
	i = -1;
	while (++i < gui->n.clients)
		if (!(SDLNet_TCP_Send(gui->n.client[i], buff, len + 1)))
			exit(0);
	close(fd);
	free(gui->av);
	gui->av = name;
	gui->quit = 1;
}
