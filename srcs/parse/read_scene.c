/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 18:07:07 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/14 18:50:44 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static t_json	prepare_scene(char *argv, t_game *game)
{
	FILE	*fp;
	char	buffer[462144];
	t_json	json;

	fp = fopen(argv, "r");
	if (!fp || ft_strcmp(&argv[ft_strlen(argv) - 5], ".json") != 0)
		terminate("fuck you and your file!\n");
	fread(buffer, 462144, 1, fp);
	json.json = cJSON_Parse(buffer);
	if (json.json == NULL || buffer[0] != '{')
		terminate("\nsomething wrong with .json file, \
please check that commas on right positions\n");
	json.composed_pos = NULL;
	json.composed_v = NULL;
	json.object = NULL;
	json.objects = NULL;
	free(game->textures);
	free(game->normals);
	return (json);
}

void			read_scene(char *argv, t_game *game)
{
	t_json	json;
	int		id;

	id = 0;
	json = prepare_scene(argv, game);
	check_scene(json, game);
	json.objects = cJSON_GetObjectItemCaseSensitive(json.json, "objects");
	json.object = (json.objects != NULL) ? (json.objects)->child : NULL;
	while (json.object)
	{
		check_object(json.object, game, json, id++);
		json.object = json.object->next;
	}
	id = -1;
	game->textures = (t_txture*)malloc_exit(sizeof(t_txture) *
	game->textures_num);
	while (++id < game->textures_num)
		get_texture(game->texture_list[id], &(game->textures[id]), \
		"./textures/");
	game->normals = (t_txture*)malloc_exit(sizeof(t_txture) *
	game->normals_num);
	id = -1;
	while (++id < game->normals_num)
		get_texture(game->normal_list[id], &(game->normals[id]), "./normals/");
	cJSON_Delete(json.json);
}
