/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj3d_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:17:38 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/08 20:26:26 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		ft_vert_push(t_game *game, cl_float3 vert)
{
	if (game->vertices_list == NULL)
		game->vertices_num = 0;
	game->vertices_list = realloc(game->vertices_list,
	sizeof(cl_float3) * (game->vertices_num + 1));
	game->vertices_list[game->vertices_num] = vert;
	game->vertices_num += 1;
}

static void	parse_vertice(char **data, t_game *game, t_json *parse, \
														const cJSON *object)
{
	cl_float3 vert;

	parse->size = cJSON_GetObjectItemCaseSensitive(object, "size");
	vert = create_cfloat3(atof(data[1]) * parse->size->valuedouble, \
							atof(data[2]) * parse->size->valuedouble, \
							atof(data[3]) * parse->size->valuedouble);
	ft_vert_push(game, vert);
}

static void	push_facing(char **data, t_game *game, t_json *parse, \
															const cJSON *object)
{
	t_obj		*obj;
	cl_float3	shift;

	obj = (t_obj*)malloc(sizeof(t_obj));
	parse->composed_pos = cJSON_GetObjectItemCaseSensitive(object, "position");
	shift = parse_vec3(parse->composed_pos, 0);
	obj->type = TRIANGLE;
	obj->vertices[0] = sum_cfloat3(game->vertices_list[ft_atoi(data[1]) - 1], \
																		shift);
	obj->vertices[1] = sum_cfloat3(game->vertices_list[ft_atoi(data[2]) - 1], \
														shift);
	obj->vertices[2] = sum_cfloat3(game->vertices_list[ft_atoi(data[3]) - 1], \
																		shift);
	obj->v = triangle_norm(obj->vertices);
	obj->id = 100;
	obj->color = create_cfloat3(1, 1, 1);
	obj->metalness = 1;
	obj->radius = 0;
	obj->emission = create_cfloat3(0, 0, 0);
	obj->is_visible = 1;
	obj->transparency = 0;
	obj->refraction = 0;
	obj->texture = 0;
	obj->normal = 0;
	ft_object_push(game, obj);
}

static void	hate_norm(const cJSON *object, t_game *game, t_json *parse, \
																	char **data)
{
	if (ft_strcmp(data[0], "v") == 0)
		parse_vertice(data, game, parse, object);
	if (ft_strcmp(data[0], "f") == 0)
		push_facing(data, game, parse, object);
	feel_free(data);
}

void		obj3d_parse(const cJSON *object, t_game *game, t_json *parse)
{
	int		fd;
	char	*line;
	char	**data;
	char	*m;

	parse->name = cJSON_GetObjectItemCaseSensitive(object, "name");
	m = ft_strjoin("./obj3d/", parse->name->valuestring);
	if ((fd = open(m, O_RDONLY)) <= 0)
		terminate("No file\n");
	free(m);
	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strlen(line) == 0)
		{
			free(line);
			continue;
		}
		prepare_data(&data, line);
		hate_norm(object, game, parse, data);
		free(line);
	}
	free(line);
	close(fd);
}
