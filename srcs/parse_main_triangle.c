/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_main_triangle.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 19:04:09 by srobert-          #+#    #+#             */
/*   Updated: 2019/09/24 18:32:17 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	triangle_color_etc(char **data, t_obj *obj)
{
	char	**vec;

	vec = ft_strsplit(data[3], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of triangle's third vertice!\n");
	obj->vertices[2] = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[4], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of triangle's color vector!\n");
	obj->color = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[5], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of triangle's emission vector!\n");
	obj->emission = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	obj->reflection = atof(data[6]);
	obj->texture = (cl_int)ft_atoi(data[7]);
	obj->v = normalize(cross(vector_diff(obj->vertices[1], obj->vertices[0]),
	vector_diff(obj->vertices[2], obj->vertices[0])));
}

void		parse_triangle(char **data, t_game *game)
{
	t_obj	*obj;
	char	**vec;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		ft_exit(0);
	obj->type = TRIANGLE;
	if (data[1] == NULL || data[2] == NULL || data[3] == NULL ||
	data[4] == NULL || data[5] == NULL || data[6] == NULL || data[7] == NULL)
		terminate("missing data of triangle: not enough arguments!\n");
	vec = ft_strsplit(data[1], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of triangle's first vertice!\n");
	obj->vertices[0] = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[2], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of triangle's second vertice!\n");
	obj->vertices[1] = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	triangle_color_etc(data, obj);
	ft_object_push(game, obj);
}

static void	obj_type(char **data, t_game *game)
{
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
}

void		read_scene(char *argv, t_game *game)
{
	int		fd;
	char	*line;
	char	**data;
	int		light_num;

	light_num = 0;
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
		obj_type(data, game);
		free(line);
	}
	close(fd);
}
