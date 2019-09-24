/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone_cyl.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 17:56:31 by lminta            #+#    #+#             */
/*   Updated: 2019/09/24 18:07:26 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	cylinder_color_etc(char **data, t_obj *obj)
{
	char	**vec;

	vec = ft_strsplit(data[3], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder color vector!\n");
	obj->color = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[4], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder emission vector!\n");
	obj->emission = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	obj->radius = atof(data[5]);
	obj->reflection = (cl_float)atof(data[6]);
	obj->texture = (cl_int)ft_atoi(data[7]);
}

void		parse_cylinder(char **data, t_game *game)
{
	t_obj	*obj;
	char	**vec;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		ft_exit(0);
	obj->type = CYLINDER;
	if (data[1] == NULL || data[2] == NULL || data[3] == NULL ||
	data[4] == NULL || data[5] == NULL || data[6] == NULL || data[7] == NULL)
		terminate("missing data of cylinder: not enough arguments!\n");
	vec = ft_strsplit(data[1], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder start pos vector!\n");
	obj->position = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[2], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder dir vector!\n");
	obj->v = normalize(create_cfloat3(atof(vec[0]),
	atof(vec[1]), atof(vec[2])));
	feel_free(vec);
	cylinder_color_etc(data, obj);
	ft_object_push(game, obj);
}

static void	cone_color_etc(char **data, t_obj *obj)
{
	char	**vec;

	vec = ft_strsplit(data[3], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder color vector!\n");
	obj->color = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[4], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder emission vector!\n");
	obj->emission = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	obj->radius = atof(data[5]);
	obj->reflection = (cl_float)atof(data[6]);
	obj->texture = (cl_int)ft_atoi(data[7]);
}

void		parse_cone(char **data, t_game *game)
{
	t_obj	*obj;
	char	**vec;

	if (!(obj = (t_obj*)malloc(sizeof(t_obj))))
		ft_exit(0);
	obj->type = CONE;
	if (data[1] == NULL || data[2] == NULL || data[3] == NULL ||
	data[4] == NULL || data[5] == NULL || data[6] == NULL || data[7] == NULL)
		terminate("missing data of cylinder: not enough arguments!\n");
	vec = ft_strsplit(data[1], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder start pos vector!\n");
	obj->position = create_cfloat3(atof(vec[0]), atof(vec[1]), atof(vec[2]));
	feel_free(vec);
	vec = ft_strsplit(data[2], ',');
	if (vec[0] == NULL || vec[1] == NULL || vec[2] == NULL)
		terminate("missing data of cylinder dir vector!\n");
	obj->v = normalize(create_cfloat3(atof(vec[0]),
	atof(vec[1]), atof(vec[2])));
	feel_free(vec);
	cone_color_etc(data, obj);
	ft_object_push(game, obj);
}
