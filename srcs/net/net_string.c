/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:22:55 by lminta            #+#    #+#             */
/*   Updated: 2019/12/11 20:57:08 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*make_string(char *name, int smpls, int fd)
{
	char	buff[FILE_SIZE];
	int		len;
	char	*res;
	char	*tmp;
	char	*str_smpl;

	fd = open(name, O_RDONLY);
	len = read(fd, buff, FILE_SIZE);
	buff[len] = 0;
	res = ft_strjoin(name, "|");
	str_smpl = ft_itoa(smpls);
	tmp = ft_strjoin(res, str_smpl);
	free(res);
	free(str_smpl);
	res = ft_strjoin(tmp, "|");
	free(tmp);
	tmp = ft_strjoin(res, buff);
	free(res);
	res = ft_strjoin("|", tmp);
	free(tmp);
	str_smpl = ft_itoa(ft_strlen(res));
	tmp = ft_strjoin(str_smpl, res);
	free(res);
	free(str_smpl);
	close(fd);
	return (tmp);
}

void		net_render(KW_Widget *widget, int b)
{
	t_gui		*gui;
	int			i;

	gui = g_gui(0, 0);
	if (gui->game->ev.button.button != SDL_BUTTON_LEFT)
		return ;
	b = 0;
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
