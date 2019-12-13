/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hilfefunktionen.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 14:51:09 by lminta            #+#    #+#             */
/*   Updated: 2019/12/10 21:42:49 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "errno.h"

cl_ulong	*get_random(cl_ulong *random)
{
	int i;

	i = -1;
	if (!(random = ft_memalloc(sizeof(cl_ulong) * (int)WIN_H * (int)WIN_W)))
		ft_exit(0);
	srand(time(NULL));
	while (++i < WIN_H * WIN_W)
		random[i] = rand() | (cl_ulong)rand() << 32;
	return (random);
}

int			compare_in_texture_dict(t_game *game, char *texture_name)
{
	int i;

	i = 0;
	if (ft_strcmp(texture_name, "chess") == 0)
		return (-1);
	if (ft_strcmp(texture_name, "perlin") == 0)
		return (-2);
	if (game->texture_list == NULL)
		return (game->textures_num + 1);
	while (i < game->textures_num)
	{
		if (ft_strcmp(game->texture_list[i], texture_name) == 0)
			return (i + 1);
		i++;
	}
	return (game->textures_num + 1);
}

int			compare_in_normal_dict(t_game *game, char *normal_name)
{
	int i;

	i = 0;
	if (ft_strcmp(normal_name, "wave") == 0)
		return (-1);
	if (game->normal_list == NULL)
		return (game->normals_num + 1);
	while (i < game->normals_num)
	{
		if (ft_strcmp(game->normal_list[i], normal_name) == 0)
			return (i + 1);
		i++;
	}
	return (game->normals_num + 1);
}

cl_float3	get_composed_pos(cJSON *composed_pos)
{
	cl_float3 composed_pos_f;

	if (composed_pos != NULL)
	{
		composed_pos_f = parse_vec3(composed_pos, 0);
		if (isnan(composed_pos_f.v4[0]))
			terminate("missing data of position of composed object!\n");
	}
	else
		composed_pos_f = create_cfloat3(0.0, 0.0, 0.0);
	return (composed_pos_f);
}

cl_float3	get_composed_v(cJSON *composed_v)
{
	cl_float3 composed_v_f;

	if (composed_v != NULL)
	{
		composed_v_f = parse_vec3(composed_v, 0);
		if (isnan(composed_v_f.v4[0]))
			terminate("missing data of direction of composed object!\n");
	}
	else
		composed_v_f = create_cfloat3(0.0, 0.0, 0.0);
	return (composed_v_f);
}
