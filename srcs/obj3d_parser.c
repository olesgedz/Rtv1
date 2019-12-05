/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj3d_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 20:17:38 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/05 19:51:57 by srobert-         ###   ########.fr       */
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



static void parse_vertice(char **data, t_game *game, t_json *parse)
{
    cl_float3 vert;
    vert = create_cfloat3(atof(data[1]) * parse->size->valuedouble, atof(data[2]) * parse->size->valuedouble, atof(data[3]) * parse->size->valuedouble);
    ft_vert_push(game, vert);
}

static void push_facing(char **data, t_game *game, t_json *parse)
{
    t_obj *obj;

    obj = (t_obj*)malloc(sizeof(t_obj));
    obj->type = TRIANGLE;
    obj->vertices[0] = game->vertices_list[ft_atoi(data[1]) - 1];
    obj->vertices[1] = game->vertices_list[ft_atoi(data[2]) - 1];
    obj->vertices[2] = game->vertices_list[ft_atoi(data[3]) - 1];
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

static void debug(t_game *game)
{
    int i  = -1;

    while(++i < game->vertices_num)
    {
        printf("vertice == %f, %f, %f\n", game->vertices_list[i].v4[0], game->vertices_list[i].v4[1], game->vertices_list[i].v4[2]);
    }
}

void obj3d_parse(const cJSON *object, t_game *game, t_json *parse)
{
    int fd;
    char *line;
    char **data;
    char *m;
    parse->name = cJSON_GetObjectItemCaseSensitive(object, "name");
    parse->size = cJSON_GetObjectItemCaseSensitive(object, "size");
    parse->composed_pos = cJSON_GetObjectItemCaseSensitive(object, "position");
    m = ft_strjoin("./obj3d/", parse->name->valuestring);
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
            parse_vertice(data, game, parse);
        if (ft_strcmp(data[0], "f") == 0)
            push_facing(data, game, parse);
        feel_free(data);
        free(line);
    }
    // free(data);
    close(fd);
}
