/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj3d_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:17:38 by srobert-          #+#    #+#             */
/*   Updated: 2019/11/21 16:44:30 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void        ft_object_push(t_game *game, t_obj *object)
{
	if (game->gpu.objects == NULL)
		game->obj_quantity = 0;
	object->is_visible = 1;
	game->gpu.objects = ft_realloc(game->gpu.objects,
	sizeof(t_obj) * (game->obj_quantity + 1));
	game->gpu.objects[game->obj_quantity] = *object;
	game->obj_quantity += 1;
	free(object);
}



static void parse_vertice(char **data, t_game *game)
{
	cl_float3 vert;

	vert = create_cfloat3(atof(data[1]), atof(data[2]), atof(data[3]));
	ft_vec_push();
}




void obj3d_parse(const char *name, t_game *game)
{
	int fd;
	char *line;
	char **data;
	char *m;

	m = ft_strjoin("./obj3d/", name);
	if ((fd = open(m, O_RDONLY)) <= 0)
		terminate("fuck you\n");
	while (get_next_line(fd, &line))
	{
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue;
		}
		data = ft_strsplit(line, '\t');
		if (data[1] == NULL)
		{
			feel_free(data);
			data = ft_strsplit(line, ' ');
		}
		if (ft_strcmp(data[0], "v") == 0)
			parse_vertice(data, game);
		feel_free(data);
		free(line);
	}
	free(data);
	close(fd);
}
