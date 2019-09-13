/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:04:09 by srobert-          #+#    #+#             */
/*   Updated: 2019/09/13 17:08:53 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "errno.h"
// void ft_object_push(t_game *game, t_object *object)
// {
//     if (game->main_objs.figures == NULL)
//         game->main_objs.figures_num = 0;
//     game->main_objs.figures = realloc(game->main_objs.figures, sizeof(t_object) * (game->main_objs.figures_num + 1));
//     game->main_objs.figures[game->main_objs.figures_num] = *object;
//     game->main_objs.figures_num += 1;
// }

void	terminate(char *s)
{
	if (errno == 0)
		ft_putendl_fd(s, 2);
	else
		perror(s);
	exit(1);
}

void feel_free(char **str)
{
    int i;

    i = -1;
    while (str[++i] != NULL)
        free(str[i]);
}

void ft_object_push(t_game *game, t_obj *object)
{
	if (game->gpu->objects == NULL)
		game->obj_quantity = 0;
	game->gpu->objects = ft_realloc(game->gpu->objects, sizeof(t_obj) * (game->obj_quantity + 1));
	game->gpu->objects[game->obj_quantity] = *object;
	game->obj_quantity += 1;
}

void ft_cam_push(t_game *game, t_cam *cam)
{
	if (game->gpu->camera == NULL)
		game->cam_quantity = 0;
	game->gpu->camera = ft_realloc(game->gpu->camera, sizeof(t_obj) * (game->cam_quantity + 1));
	game->gpu->camera[game->cam_quantity] = *cam;
	game->cam_quantity += 1;
}

static void parse_plane(char **data, t_game *game)
{
	cl_float3 position;
	cl_float3 color;
	cl_float3 emition;
	cl_int texture;
	cl_float reflection;
	cl_float3 v;
	char **vec;

	if (data[1] == NULL || data[2] == NULL || data[3] == NULL || data[4] == NULL || data[5] == NULL || data[6] == NULL)
		terminate("missing data of plane: not enough arguments!\n");
	vec = ft_strsplit(data[1], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of plane start pos vector!\n");
	position = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[2], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of plane dir vector!\n");
	v = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[3], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of plane color vector!\n");
	color = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[4], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of plane emition vector!\n");
	emition = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	free(vec);
	reflection = (cl_float)atof(data[5]);
	texture = (cl_int)ft_atoi(data[6]);
	ft_object_push(game, add_plane(position, color, emition, texture, reflection, v));
}

static void parse_sphere(char **data, t_game *game)
{
	cl_float3 position;
	cl_float3 color;
	cl_float3 emition;
	cl_int texture;
	cl_float reflection;
	float     radius;
	char		**vec;

	if (data[1] == NULL || data[2] == NULL || data[3] == NULL || data[4] == NULL || data[5] == NULL || data[6] == NULL)
		terminate("missing data of sphere: not enough arguments!\n");
	vec = ft_strsplit(data[1], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of plane start pos vector!\n");
	position = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[2], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of sphere color vector!\n");
	color = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[3], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of emition vector!\n");
	emition = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	free(vec);
	radius = atof(data[4]);
	reflection = (cl_float)atof(data[5]);
	texture = (cl_int)ft_atoi(data[6]);
	ft_object_push(game, add_sphere(position, radius, color, emition, texture, reflection));
}

static void parse_cylinder(char **data, t_game *game)
{
	cl_float3 position;
	cl_float3 color;
	cl_float3 emition;
	cl_float3 v;
	cl_int texture;
	cl_float reflection;
	float     radius;
	char		**vec;

	if (data[1] == NULL || data[2] == NULL || data[3] == NULL || data[4] == NULL || data[5] == NULL || data[6] == NULL || data[7] == NULL)
		terminate("missing data of cylinder: not enough arguments!\n");
	vec = ft_strsplit(data[1], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder start pos vector!\n");
	position = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[2], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder dir vector!\n");
	v = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[3], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder color vector!\n");
	color = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[4], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder emition vector!\n");
	emition = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	free(vec);
	radius = atof(data[5]);
	reflection = (cl_float)atof(data[6]);
	texture = (cl_int)ft_atoi(data[7]);
	ft_object_push(game, add_cylinder(position, radius, color, emition, texture, reflection, v));
}

static void parse_cone(char **data, t_game *game)
{
	cl_float3 position;
	cl_float3 color;
	cl_float3 emition;
	cl_float3 v;
	cl_int texture;
	cl_float reflection;
	float     radius;
	char		**vec;

	if (data[1] == NULL || data[2] == NULL || data[3] == NULL || data[4] == NULL || data[5] == NULL || data[6] == NULL || data[7] == NULL)
		terminate("missing data of cylinder: not enough arguments!\n");
	vec = ft_strsplit(data[1], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder start pos vector!\n");
	position = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[2], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder dir vector!\n");
	v = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[3], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder color vector!\n");
	color = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[4], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder emition vector!\n");
	emition = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	free(vec);
	radius = atof(data[5]);
	reflection = (cl_float)atof(data[6]);
	texture = (cl_int)ft_atoi(data[7]);
	ft_object_push(game, add_cone(position, radius, color, emition, texture, reflection, v));
}

void parse_cam(char **data, t_game *game)
{
    char **vec;
	cl_float3 position;
	cl_float3 v;
	cl_float3 normal;

    if (data[1] == NULL || data[2] == NULL || data[3] == NULL)
        terminate("missing data of cam: not enough arguments!\n");
    vec = ft_strsplit(data[1], ',');
    if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
        terminate("missing data of cam pos vector!\n");
    position = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
    feel_free(vec);
    vec = ft_strsplit(data[2], ',');
    if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
        terminate("missing data of cam dir vector!\n");
    v = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
    feel_free(vec);
    vec = ft_strsplit(data[3], ',');
    if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
        terminate("missing data of cam norm vector!\n");
    normal = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
    feel_free(vec);
    free(vec);
	ft_cam_push(game, add_cam(position, v, normal));
}

static void parse_triangle(char **data, t_game *game)
{
    char        **vec;
    cl_float3    *vertices;
	cl_float3 color;
	cl_float3 emition;
	cl_float3 v;
	cl_int texture;
	cl_float reflection;

    vertices = (cl_float3*)malloc(sizeof(cl_float3) * 3);
    if (data[1] == NULL || data[2] == NULL || data[3] == NULL || data[4] == NULL || data[5] == NULL || data[6] == NULL || data[7] == NULL)
        terminate("missing data of triangle: not enough arguments!\n");
    vec = ft_strsplit(data[1], ',');
    if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
        terminate("missing data of triangle's first vertice!\n");
    vertices[0] = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
    feel_free(vec);
    vec = ft_strsplit(data[2], ',');
    if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
        terminate("missing data of triangle's second vertice!\n");
	vertices[1] = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
    feel_free(vec);
    vec = ft_strsplit(data[3], ',');
    if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
        terminate("missing data of triangle's third vertice!\n");
    vertices[2] = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
    feel_free(vec);
	vec = ft_strsplit(data[4], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
        terminate("missing data of triangle's color vector!\n");
	color = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[5], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
        terminate("missing data of triangle's emition vector!\n");
	emition = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
    free(vec);
	reflection = atof(data[6]);
	texture = (cl_int)ft_atoi(data[7]);
	ft_object_push(game, add_triangle(vertices, color, emition, texture, reflection));
}

void read_scene(char *argv, t_game *game)
{
	int fd;
	char *line;
	char **data;
	int light_num;

	light_num = 0;
	printf("%s\n", argv);
	if ((fd = open(argv, O_RDONLY)) <= 0)
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
		if (ft_strcmp(data[0], "PLANE") == 0)
			parse_plane(data, game);
		else if (ft_strcmp(data[0], "SPHERE") == 0)
			parse_sphere(data, game);
		else if (ft_strcmp(data[0], "CYLINDER") == 0)
			parse_cylinder(data, game);
		else if (ft_strcmp(data[0], "CONE") == 0)
			parse_cone(data, game);
		else if (ft_strcmp(data[0], "CAM") == 0)
		    parse_cam(data, game);
		else if (ft_strcmp(data[0], "TRIANGLE") == 0)
		    parse_triangle(data, game);
		feel_free(data);
		free(line);
	}
	free(data);
	close(fd);
}
