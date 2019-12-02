/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyse_dienstprogramme.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/25 17:05:04 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/01 19:14:24 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "errno.h"

cl_float3	parse_vec3(cJSON *vec)
{
	t_json parse;

	parse.x = cJSON_GetArrayItem(vec, 0);
	parse.y = cJSON_GetArrayItem(vec, 1);
	parse.z = cJSON_GetArrayItem(vec, 2);
	if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
		return (create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble));
	else
		return (create_cfloat3(NAN, 0.0, 0.0));
}

cl_float2	parse_vec2(cJSON *vec)
{
	t_json parse;

	parse.x = cJSON_GetArrayItem(vec, 0);
	parse.y = cJSON_GetArrayItem(vec, 1);
	if (parse.x != NULL && parse.y != NULL)
		return (create_cfloat2(parse.x->valuedouble, parse.y->valuedouble));
	else
		return (create_cfloat2(NAN, 0.0));
}
