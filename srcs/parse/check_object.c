/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_object.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 18:47:46 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/08 20:04:31 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	parse_composed(const cJSON *composed, t_game *game,\
							t_json *parse, int id)
{
	const cJSON *object;
	const cJSON *objects;

	object = NULL;
	objects = NULL;
	parse->composed_pos = cJSON_GetObjectItemCaseSensitive(composed, \
															"position");
	parse->composed_v = cJSON_GetObjectItemCaseSensitive(composed, "dir");
	objects = cJSON_GetObjectItemCaseSensitive(composed, "objects");
	object = (objects != NULL) ? (objects)->child : NULL;
	while (object)
	{
		check_object(object, game, *parse, id);
		object = object->next;
	}
}

static void	set_type(t_obj *obj, cJSON *type)
{
	if (ft_strcmp(type->valuestring, "plane") == 0)
		obj->type = PLANE;
	else if (ft_strcmp(type->valuestring, "sphere") == 0)
		obj->type = SPHERE;
	else if (ft_strcmp(type->valuestring, "cylinder") == 0)
		obj->type = CYLINDER;
	else if (ft_strcmp(type->valuestring, "cone") == 0)
		obj->type = CONE;
	else if (ft_strcmp(type->valuestring, "triangle") == 0)
		obj->type = TRIANGLE;
	else if (ft_strcmp(type->valuestring, "paraboloid") == 0)
		obj->type = PARABOLOID;
}

static void	parse_object(const cJSON *object, t_obj *obj, \
						t_json parse, t_game *game)
{
	parse_necessary(object, obj, &parse);
	parse_facing(object, obj, &parse, game);
	parse_basis(object, obj, &parse);
	if (obj->type == TRIANGLE)
		parse_triangle_vert(object, obj, &parse);
	parse_rest(object, obj, &parse);
}

void		check_object(const cJSON *object, t_game *game, \
						t_json parse, int id)
{
	t_obj *obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->composed_pos = get_composed_pos(parse.composed_pos);
	obj->composed_v = get_composed_v(parse.composed_v);
	parse.type = cJSON_GetObjectItemCaseSensitive(object, "type");
	set_type(obj, parse.type);
	if (ft_strcmp(parse.type->valuestring, "obj3d") == 0)
	{
		free(obj);
		obj3d_parse(object, game, &parse);
		return ;
	}
	else if (ft_strcmp(parse.type->valuestring, "composed") == 0)
	{
		free(obj);
		parse_composed(object, game, &parse, id);
		return ;
	}
	obj->id = id;
	obj->is_visible = 1;
	parse_object(object, obj, parse, game);
	ft_object_push(game, obj);
}
