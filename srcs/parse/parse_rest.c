/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_rest.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 18:31:53 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/08 18:46:07 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	parse_rest(const cJSON *object, t_obj *obj, t_json *parse)
{
	parse->prolapse = cJSON_GetObjectItemCaseSensitive(object, "prolapse");
	if (parse->prolapse != NULL)
	{
		obj->prolapse = parse_vec2(parse->prolapse);
		if (isnan(obj->prolapse.s[0]))
			terminate("missing data of cylinder prolapse vector!\n");
	}
	else
		obj->prolapse = create_cfloat2(1.0, 1.0);
	parse->transparency = cJSON_GetObjectItemCaseSensitive(object, \
															"transparency");
	if (parse->transparency != NULL)
		obj->transparency = parse->transparency->valuedouble;
	else
		obj->transparency = 0.0;
	parse->refraction = cJSON_GetObjectItemCaseSensitive(object, "refraction");
	if (parse->refraction != NULL)
		obj->refraction = parse->refraction->valuedouble;
	else
		obj->refraction = 0.0;
	parse->negative = cJSON_GetObjectItemCaseSensitive(object, "negative");
	if (parse->negative != NULL)
		obj->is_negative = (int)parse->negative->valuedouble;
	else
		obj->is_negative = 0;
}
