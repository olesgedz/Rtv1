/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurgan <sdurgan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:12:04 by sdurgan           #+#    #+#             */
/*   Updated: 2019/05/15 16:27:57 by sdurgan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	configure_sphere(char *map_name, t_sphere *sphere)
{
	int			fd;
	char		*line;
	int			ret;
	char		**split;

	fd = open(map_name, O_RDONLY);
	line = ft_strnew(0);
	while ((ret = get_next_line(fd, &line)) > 0)
	{
		if (ret == -1)
		{
			ft_strdel(&line);
			exit(0);
		}
		split = ft_strsplit(line, ':');
		ret = ft_atoi(split[1]);
		ft_strchr(line, 'x') ? sphere->center.x = ret : 0;
		ft_strchr(line, 'y') ? sphere->center.y = ret : 0;
		ft_strchr(line, 'z') ? sphere->center.z = ret : 0;
		ft_strchr(line, 'r') ? sphere->radius = ret : 0;
		ret = ft_2darrayclean(&split);
	}
}
