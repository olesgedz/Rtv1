/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:35:09 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/08 20:28:17 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void free_list(t_game *game)
{
    int i;
    i = -1;
    while (++i < game->textures_num)
        free(game->texture_list[i]);
    free(game->texture_list);
    i = -1;
    while (++i < game->normals_num)
        free(game->normal_list[i]);
    free(game->normal_list);
}

void prepare_data(char ***data, char *line)
{
	data[0] = ft_strsplit(line, '\t');
	if (data[0][1] == NULL)
	{
		feel_free(data[0]);
		data[0] = ft_strsplit(line, ' ');
	}
}
