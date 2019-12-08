/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_necessary.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:23:53 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/08 19:25:35 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_necessary(const cJSON *object, t_obj *obj, t_json *parse)
{
	parse->position = cJSON_GetObjectItemCaseSensitive(object, "position");
	obj->position = parse_vec3(parse->position, 0);
	if (isnan(obj->position.v4[0]) && obj->type != TRIANGLE)
		terminate("missing data of obj position!\n");
	obj->position = sum_cfloat3(obj->position, obj->composed_pos);
	parse->v = cJSON_GetObjectItemCaseSensitive(object, "dir");
	obj->v = parse_vec3(parse->v, 0);
	if (isnan(obj->v.v4[0]) && obj->type != SPHERE && obj->type != TRIANGLE)
		terminate("missing data of obj dir !\n");
	obj->v = normalize(sum_cfloat3(obj->v, obj->composed_v));
	parse->color = cJSON_GetObjectItemCaseSensitive(object, "color");
	obj->color = parse_vec3(parse->color, 0);
	if (isnan(obj->color.v4[0]))
		terminate("missing data of obj color vector!\n");
	parse->radius = cJSON_GetObjectItemCaseSensitive(object, "radius");
	if (parse->radius != NULL)
		obj->radius = parse->radius->valuedouble;
	else if (obj->type != PLANE && obj->type != TRIANGLE)
		terminate("missing data of obj radius!\n");
	parse->tor_radius = cJSON_GetObjectItemCaseSensitive(object, \
																"tor radius");
	if (parse->tor_radius != NULL)
		obj->tor_radius = parse->tor_radius->valuedouble;
	else
		obj->tor_radius = 0.1;
}
