/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   util.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 17:35:09 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/01 19:14:58 by lminta           ###   ########.fr       */
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
