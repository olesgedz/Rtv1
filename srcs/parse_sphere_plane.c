/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere_plane.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 17:06:57 by lminta            #+#    #+#             */
/*   Updated: 2019/09/24 18:01:10 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	plane_color_etc(char **data, t_obj *obj)
{
	char	**vec;

	vec = ft_strsplit(data[3], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of plane color vector!\n");
	obj->color = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[4], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of plane emission vector!\n");
	obj->emission = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	obj->reflection = (cl_float)atof(data[5]);
	obj->texture = (cl_int)ft_atoi(data[6]);
}

void		parse_plane(char **data, t_game *game)
{
	t_obj	*obj;
	char	**vec;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		ft_exit(0);
	obj->type = PLANE;
	if (data[1] == NULL || data[2] == NULL || data[3] == NULL ||
	data[4] == NULL || data[5] == NULL || data[6] == NULL)
		terminate("missing data of plane: not enough arguments!\n");
	vec = ft_strsplit(data[1], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of plane start pos vector!\n");
	obj->position = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[2], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of plane dir vector!\n");
	obj->v = normalize(create_cfloat3(atof(vec[0]),
	atof(vec[1]), atof(vec[2])));
	feel_free(vec);
	plane_color_etc(data, obj);
	ft_object_push(game, obj);
}

static void	sphere_color_etc(char **data, t_obj *obj)
{
	char	**vec;

	vec = ft_strsplit(data[2], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of sphere color vector!\n");
	obj->color = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[3], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of emission vector!\n");
	obj->emission = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	obj->radius = atof(data[4]);
	obj->reflection = (cl_float)atof(data[5]);
	obj->texture = (cl_int)ft_atoi(data[6]);
}

void		parse_sphere(char **data, t_game *game)
{
	t_obj	*obj;
	char	**vec;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		ft_exit(0);
	obj->type = SPHERE;
	if (data[1] == NULL || data[2] == NULL || data[3] == NULL ||
	data[4] == NULL || data[5] == NULL || data[6] == NULL)
		terminate("missing data of sphere: not enough arguments!\n");
	vec = ft_strsplit(data[1], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of plane start pos vector!\n");
	obj->position = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	sphere_color_etc(data, obj);
	ft_object_push(game, obj);
}
