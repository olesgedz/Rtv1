/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_basis.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:47:46 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/08 19:13:25 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	plane_basis(const cJSON *object, t_obj *obj, t_json *parse)
{
	parse->x_basis = cJSON_GetObjectItemCaseSensitive(object, "x_basis");
	if (parse->x_basis != NULL)
		obj->basis[0] = parse_vec3(parse->x_basis, 1);
	else
	{
		if (obj->v.s[0] != 0.0f || obj->v.s[1] != 0.0f)
			obj->basis[0] = normalize(create_cfloat3(obj->v.s[1], \
													-obj->v.s[0], 0));
		else
			obj->basis[0] = create_cfloat3(0.0f, 1.0f, 0.0f);
	}
	parse->y_basis = cJSON_GetObjectItemCaseSensitive(object, "y_basis");
	if (parse->y_basis != NULL)
		obj->basis[1] = parse_vec3(parse->y_basis, 1);
	else
		obj->basis[1] = cross(obj->v, obj->basis[0]);
	parse->z_basis = cJSON_GetObjectItemCaseSensitive(object, "z_basis");
	if (parse->z_basis != NULL)
		obj->basis[2] = parse_vec3(parse->z_basis, 1);
	else
		obj->basis[2] = cross(obj->basis[0], obj->basis[1]);
}

static void	sphere_basis(const cJSON *object, t_obj *obj, t_json *parse)
{
	parse->x_basis = cJSON_GetObjectItemCaseSensitive(object, "x_basis");
	if (parse->x_basis != NULL)
		obj->basis[0] = parse_vec3(parse->x_basis, 1);
	else
		obj->basis[0] = create_cfloat3(1.0, 0.0, 0.0);
	parse->y_basis = cJSON_GetObjectItemCaseSensitive(object, "y_basis");
	if (parse->y_basis != NULL)
		obj->basis[1] = parse_vec3(parse->y_basis, 1);
	else
		obj->basis[1] = create_cfloat3(0.0, 1.0, 0.0);
	parse->z_basis = cJSON_GetObjectItemCaseSensitive(object, "z_basis");
	if (parse->z_basis != NULL)
		obj->basis[2] = parse_vec3(parse->z_basis, 1);
	else
		obj->basis[2] = cross(obj->basis[0], obj->basis[1]);
}

static void	cylinder_basis(const cJSON *object, t_obj *obj, t_json *parse)
{
	parse->x_basis = cJSON_GetObjectItemCaseSensitive(object, "x_basis");
	if (parse->x_basis != NULL)
		obj->basis[0] = parse_vec3(parse->x_basis, 1);
	else
	{
		if (obj->v.s[0] != 0.0f || obj->v.s[1] != 0.0f)
			obj->basis[0] = normalize(create_cfloat3(obj->v.s[1], \
													-obj->v.s[0], 0));
		else
			obj->basis[0] = create_cfloat3(0.0f, 1.0f, 0.0f);
	}
	parse->y_basis = cJSON_GetObjectItemCaseSensitive(object, "y_basis");
	if (parse->y_basis != NULL)
		obj->basis[1] = parse_vec3(parse->y_basis, 1);
	else
		obj->basis[1] = cross(obj->basis[0], obj->v);
	parse->z_basis = cJSON_GetObjectItemCaseSensitive(object, "z_basis");
	if (parse->z_basis != NULL)
		obj->basis[2] = parse_vec3(parse->z_basis, 1);
	else
		obj->basis[2] = create_cfloat3(0.0, 0.0, 1.0);
}

void		parse_basis(const cJSON *object, t_obj *obj, t_json *parse)
{
	if (obj->type == SPHERE)
		sphere_basis(object, obj, parse);
	else if (obj->type == CYLINDER)
		cylinder_basis(object, obj, parse);
	else
		plane_basis(object, obj, parse);
}
