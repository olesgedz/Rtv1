/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dumper_parts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 15:13:55 by lminta            #+#    #+#             */
/*   Updated: 2019/12/13 19:47:23 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		dump_scene(t_game *game, FILE *fp)
{
	t_cam *cam;

	cam = &game->gpu.camera[game->cam_num];
	fprintf(fp, "    \"scene\":{\n");
	fprintf(fp, "        \"global texture\": \"%s\",\n", game->texture_list[0]);
	fprintf(fp, "        \"ambiance\": %.3f,\n", cam->ambience);
	fprintf(fp, "        \"cartoon\": %d,\n", cam->cartoon);
	fprintf(fp, "        \"motion blur\": %.3f,\n", cam->motion_blur);
	fprintf(fp, "        \"sepia\": %d,\n", cam->sepia);
	fprintf(fp, "        \"stereo\": %d\n", cam->stereo);
	fprintf(fp, "    },\n\n");
}

static void	print_type(int num, FILE *fp)
{
	if (num == SPHERE)
		fprintf(fp, "            \"type\": \"sphere\",\n");
	else if (num == CYLINDER)
		fprintf(fp, "            \"type\": \"cylinder\",\n");
	else if (num == CONE)
		fprintf(fp, "            \"type\": \"cone\",\n");
	else if (num == PLANE)
		fprintf(fp, "            \"type\": \"plane\",\n");
	else if (num == TRIANGLE)
		fprintf(fp, "            \"type\": \"triangle\",\n");
	else if (num == TORUS)
		fprintf(fp, "            \"type\": \"torus\",\n");
	else if (num == PARABOLOID)
		fprintf(fp, "            \"type\": \"paraboloid\",\n");
}

static void	tex_obj_print(t_obj *obj, FILE *fp, t_game *game)
{
	fprintf(fp, "            \"position\": [%.3f, %.3f, %.3f],\n",
	obj->position.s[0], obj->position.s[1], obj->position.s[2]);
	fprintf(fp, "            \"radius\": %.3f,\n", obj->radius);
	if (obj->type == TORUS)
		fprintf(fp, "            \"tor radius\": %f,\n", obj->tor_radius);
	if (obj->texture > 0)
		fprintf(fp, "            \"texture\": \"%s\",\n",
		game->texture_list[obj->texture - 1]);
	else if (obj->texture == -1)
		fprintf(fp, "            \"texture\": \"chess\",\n");
	else if (obj->texture == -2)
		fprintf(fp, "            \"texture\": \"perlin\",\n");
	fprintf(fp, "            \"prolapse\": [%.3f, %.3f],\n",
	obj->prolapse.s[0], obj->prolapse.s[1]);
	fprintf(fp, "            \"shift\": [%.3f, %.3f],\n",
	obj->shift.s[0], obj->shift.s[1]);
	if (obj->normal > 0)
		fprintf(fp, "            \"normal\": \"%s\",\n",
		game->normal_list[obj->normal - 1]);
	else if (obj->normal == -1)
		fprintf(fp, "            \"normal\": \"wave\",\n");
	basis_print(obj, fp);
}

static void	vert_print(t_obj *obj, FILE *fp)
{
	fprintf(fp, "            \"a\": [%.3f, %.3f, %.3f],\n",
	obj->vertices[0].s[0], obj->vertices[0].s[1], obj->vertices[0].s[2]);
	fprintf(fp, "            \"b\": [%.3f, %.3f, %.3f],\n",
	obj->vertices[1].s[0], obj->vertices[1].s[1], obj->vertices[1].s[2]);
	fprintf(fp, "            \"c\": [%.3f, %.3f, %.3f]\n",
	obj->vertices[2].s[0], obj->vertices[2].s[1], obj->vertices[2].s[2]);
}

void		dump_obj(t_game *game, FILE *fp)
{
	int		i;
	t_obj	*obj;

	i = -1;
	fprintf(fp, "    \"objects\":[\n");
	while (++i < (int)game->obj_quantity)
	{
		obj = &game->gpu.objects[i];
		fprintf(fp, "        {\n");
		print_type(obj->type, fp);
		fprintf(fp, "            \"transparency\": %.3f,\n", obj->transparency);
		fprintf(fp, "            \"metalness\": %.3f,\n", obj->metalness);
		fprintf(fp, "            \"refraction\": %.3f,\n", obj->refraction);
		fprintf(fp, "            \"color\": [%.3f, %.3f, %.3f],\n",
		obj->color.s[0], obj->color.s[1], obj->color.s[2]);
		fprintf(fp, "            \"emition\": [%.3f, %.3f, %.3f],\n",
		obj->emission.s[0], obj->emission.s[1], obj->emission.s[2]);
		if (obj->type != TRIANGLE)
			tex_obj_print(obj, fp, game);
		else
			vert_print(obj, fp);
		if (i != (int)game->obj_quantity - 1)
			fprintf(fp, "        },\n");
	}
	fprintf(fp, "        }\n    ],\n\n");
}
