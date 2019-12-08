/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_triangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:22:14 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/08 19:06:07 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3	triangle_norm(cl_float3 *vertices)
{
	cl_float3 ab;
	cl_float3 ac;

	ab = vector_diff(vertices[1], vertices[0]);
	ac = vector_diff(vertices[2], vertices[0]);
	return (normalize(cross(ab, ac)));
}

void		parse_triangle_vert(const cJSON *object, t_obj *obj, t_json *parse)
{
	parse->a = cJSON_GetObjectItemCaseSensitive(object, "a");
	obj->vertices[0] = parse_vec3(parse->a, 0);
	if (isnan(obj->vertices[0].v4[0]))
		terminate("missing data of triangle vertice!\n");
	parse->b = cJSON_GetObjectItemCaseSensitive(object, "b");
	obj->vertices[1] = parse_vec3(parse->b, 0);
	if (isnan(obj->vertices[01].v4[0]))
		terminate("missing data of triangle vertice!\n");
	parse->c = cJSON_GetObjectItemCaseSensitive(object, "c");
	obj->vertices[2] = parse_vec3(parse->c, 0);
	if (isnan(obj->vertices[2].v4[0]))
		terminate("missing data of triangle vertice!\n");
	obj->v = triangle_norm(obj->vertices);
}
