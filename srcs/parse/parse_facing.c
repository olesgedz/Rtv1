/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_facing.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 19:14:35 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/08 19:22:14 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	check_tex_and_norm(const cJSON *object, t_obj *obj, \
													t_json *parse, t_game *game)
{
	parse->texture = cJSON_GetObjectItemCaseSensitive(object, "texture");
	if (parse->texture != NULL)
	{
		obj->texture = compare_in_texture_dict(game, \
												parse->texture->valuestring);
		if (obj->texture == game->textures_num + 1)
			ft_texture_push(game, &(game->texture_list), \
												parse->texture->valuestring);
	}
	else
		obj->texture = 0;
	parse->normal = cJSON_GetObjectItemCaseSensitive(object, "normal");
	if (parse->normal != NULL)
	{
		obj->normal = compare_in_normal_dict(game, parse->normal->valuestring);
		if (obj->normal == game->normals_num + 1)
			ft_normal_push(game, &(game->normal_list), \
													parse->normal->valuestring);
	}
	else
		obj->normal = 0;
}

void		parse_facing(const cJSON *object, t_obj *obj, \
												t_json *parse, t_game *game)
{
	check_tex_and_norm(object, obj, parse, game);
	parse->emition = cJSON_GetObjectItemCaseSensitive(object, "emition");
	if (parse->emition != NULL)
	{
		obj->emission = parse_vec3(parse->emition, 0);
		if (isnan(obj->emission.v4[0]))
			terminate("missing data of obj emition vector!\n");
	}
	else
		obj->emission = create_cfloat3(0.0, 0.0, 0.0);
	parse->reflection = cJSON_GetObjectItemCaseSensitive(object, "metalness");
	if (parse->reflection != NULL)
		obj->metalness = parse->reflection->valuedouble;
	else
		obj->metalness = 0.0;
	parse->shift = cJSON_GetObjectItemCaseSensitive(object, "shift");
	if (parse->shift != NULL)
	{
		obj->shift = parse_vec2(parse->shift);
		if (isnan(obj->shift.s[0]))
			terminate("missing data of obj shift vector!\n");
	}
	else
		obj->shift = create_cfloat2(0.0, 0.0);
}
