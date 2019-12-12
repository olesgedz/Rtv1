/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/06 19:16:12 by srobert-          #+#    #+#             */
/*   Updated: 2019/12/09 21:22:25 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void		set_default_tex(t_game *game)
{
	game->global_tex_id = compare_in_texture_dict(game, "sun.jpg");
	if (game->global_tex_id == game->textures_num + 1)
	{
		game->global_tex_id--;
		ft_texture_push(game, &(game->texture_list), "sun.jpg");
	}
}

static void		check_global_tex(cJSON *scene, t_game *game)
{
	cJSON *global_texture;

	global_texture = cJSON_GetObjectItemCaseSensitive(scene, "global texture");
	if (global_texture != NULL)
	{
		game->global_tex_id = compare_in_texture_dict(game, \
		global_texture->valuestring);
		if (game->global_tex_id == game->textures_num + 1)
		{
			game->global_tex_id--;
			ft_texture_push(game, &(game->texture_list), \
			global_texture->valuestring);
		}
	}
	else
		set_default_tex(game);
}

static t_filter	check_filter(cJSON *scene, t_json parse)
{
	t_filter filter;

	parse.ambience = cJSON_GetObjectItemCaseSensitive(scene, "ambiance");
	filter.ambiance = parse.ambience != NULL ? \
	parse.ambience->valuedouble : 0.1;
	parse.cartoon = cJSON_GetObjectItemCaseSensitive(scene, "cartoon");
	filter.cartoon = parse.cartoon != NULL ? \
	(int)parse.cartoon->valuedouble : 0;
	parse.sepia = cJSON_GetObjectItemCaseSensitive(scene, "sepia");
	filter.sepia = parse.sepia != NULL ? (int)parse.sepia->valuedouble : 0;
	parse.stereo = cJSON_GetObjectItemCaseSensitive(scene, "stereo");
	filter.stereo = parse.stereo != NULL ? \
	(int)parse.stereo->valuedouble : 0;
	parse.motion_blur = cJSON_GetObjectItemCaseSensitive(scene, "motion blur");
	filter.motion_blur = parse.motion_blur != NULL ? \
	parse.motion_blur->valuedouble : 0;
	return (filter);
}

static t_filter	filter_default(void)
{
	t_filter filter;

	filter.ambiance = 0.1;
	filter.cartoon = 0;
	filter.sepia = 0;
	filter.stereo = 0;
	filter.motion_blur = 0;
	return (filter);
}

void			check_scene(t_json parse, t_game *game)
{
	t_filter	filter;
	cJSON		*scene;

	scene = cJSON_GetObjectItemCaseSensitive(parse.json, "scene");
	if (scene != NULL)
	{
		check_global_tex(scene, game);
		filter = check_filter(scene, parse);
	}
	else
	{
		set_default_tex(game);
		filter = filter_default();
	}
	parse.music = cJSON_GetObjectItemCaseSensitive(scene, "music");
	if (parse.music != NULL)
		game->music = parse.music->string;
	parse.cameras = cJSON_GetObjectItemCaseSensitive(parse.json, "cameras");
	parse.camera = (parse.cameras != NULL) ? (parse.cameras)->child : NULL;
	while (parse.camera)
	{
		check_cam(parse, game, &filter);
		parse.camera = parse.camera->next;
	}
}
