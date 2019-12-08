/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_srv.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/07 21:14:07 by lminta            #+#    #+#             */
/*   Updated: 2019/12/08 22:29:23 by lminta           ###   ########.fr       */
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
		free(gui->n.str_ip);
		gui->n.str_ip = 0;
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
	static char	*name = 0;
	char		*map = 0;
	char		*buff = 0;

	SDLNet_TCP_Recv(gui->n.tcpsock, message, FILE_SIZE);
	//printf("%s\n", message);
	if (!ft_strcmp(message, "ping!"))
	{
		//printf("ping\n");
		return ;
	}
	buff = ft_strdup(message);
	map = ft_strstr(buff, ".json") + 5;
	name = malloc(map - buff + 1);
	name = ft_strncpy(name, buff, map - buff);
	name[18] = 0;
	if (!(fp = fopen(name, "w")))
		exit(0);
	fprintf(fp, "%s", map);
	fclose(fp);
	free(gui->av);
	gui->av = name;
	gui->quit = 1;

	// if (!ft_strcmp(&message[ft_strlen(message) - 5], ".json"))
	// {
	// 	printf("json\n");
	// 	if (!(fp = fopen(message, "w")))
	// 		exit(0);
	// 	name = ft_strdup(message);
	// }
	// // else if (ft_strstr(message, "smpl"))
	// // {
	// // 	printf("smpls\n");
	// // 	game->samples_to_do = ft_atoi(message);
	// // }
	// else
	// {
	// 	printf("map\n");
	// 	fprintf(fp, "%s", message);
	// 	fclose(fp);
	// 	fp = 0;
	// 	free(gui->av);
	// 	gui->av = name;
	// 	gui->quit = 1;
	// }
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

void		send_map(t_game *game, t_gui *gui, char *tmp)
{
	int		i;
	int		len[2];
	int		fd;
	char	*name;
	char	buff[FILE_SIZE];

	if (!gui->game->server)
		return ;
	if (!(name = dumper(game, gui)))
		exit(0);
	i = -1;
	len[0] = strlen(name);
	fd = open(name, O_RDONLY);
	len[1] = read(fd, buff, FILE_SIZE);
	buff[len[1]] = 0;
	tmp = ft_strjoin(name, buff);
	while (++i < gui->n.clients)
	{
		SDLNet_TCP_Send(gui->n.client[i], tmp, len[0]+ len[1] + 1);
		//SDLNet_TCP_Send(gui->n.client[i], buff, len[1] + 1);
	}
	close(fd);
	free(gui->av);
	gui->av = name;
	gui->quit = 1;
}
