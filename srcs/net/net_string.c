/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:22:55 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 19:13:21 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char		*make_string(char *name, int smpls, int fd)
{
	char	buff[FILE_SIZE];
	int		len;
	char	*res[3];

	fd = open(name, O_RDONLY);
	len = read(fd, buff, FILE_SIZE);
	buff[len] = 0;
	res[0] = ft_strjoin(name, "|");
	res[2] = ft_itoa(smpls);
	res[1] = ft_strjoin(res[0], res[2]);
	free(res[0]);
	free(res[2]);
	res[0] = ft_strjoin(res[1], "|");
	free(res[1]);
	res[1] = ft_strjoin(res[0], buff);
	free(res[0]);
	res[0] = ft_strjoin("|", res[1]);
	free(res[1]);
	res[2] = ft_itoa(ft_strlen(res[0]));
	res[1] = ft_strjoin(res[2], res[0]);
	free(res[0]);
	free(res[2]);
	close(fd);
	return (res[1]);
}

void		net_render(KW_Widget *widget, int b)
{
	t_gui		*gui;
	int			i;

	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
	widget = 0;
	i = ft_atoi(KW_GetEditboxText(gui->n.ed_b));
	send_map(gui->game, gui, 0, i);
	gui->game->samples_to_do = i;
}

void		client_side_free(t_gui *gui, char **buff, FILE *fp)
{
	fclose(fp);
	free(gui->av);
	scene_select(gui, -1, 0);
	scene_click(0, 0);
	if (!gui->s_s.show)
		KW_HideWidget(gui->s_s.frame);
	gui->av = buff[1];
	gui->quit = 1;
	free(buff[0]);
	free(buff[2]);
	free(buff[3]);
	free(buff);
}
