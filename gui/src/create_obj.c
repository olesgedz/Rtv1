/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_obj.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 20:37:51 by lminta            #+#    #+#             */
/*   Updated: 2019/11/22 16:13:19 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	create_cone(t_game *game)
{
	t_obj *obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->v.s[0] = 0;
	obj->v.s[1] = 1;
	obj->v.s[2] = 0;
	obj->radius = 0.1;
	same_new(game, obj, CONE);
}

void	create_sphere(t_game *game)
{
	t_obj *obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->radius = 0.1;
	same_new(game, obj, SPHERE);
}

void	create_plane(t_game *game)
{
	t_obj *obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->v.s[0] = 0;
	obj->v.s[1] = 1;
	obj->v.s[2] = 0;
	obj->prolapse.s[0] = 1;
	obj->prolapse.s[1] = 1;
	same_new(game, obj, PLANE);
}

void	create_cylinder(t_game *game)
{
	t_obj *obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->v.s[0] = 0;
	obj->v.s[1] = 1;
	obj->v.s[2] = 0;
	obj->radius = 0.1;
	obj->prolapse.s[1] = 1;
	same_new(game, obj, CYLINDER);
}

void	create_triangle(t_game *game)
{
	t_obj *obj;

	obj = (t_obj*)malloc(sizeof(t_obj));
	obj->vertices[0].s[0] = 0.0;
	obj->vertices[0].s[1] = 0.1;
	obj->vertices[0].s[2] = 0.1;
	obj->vertices[1].s[0] = 0.0;
	obj->vertices[1].s[1] = 0.35;
	obj->vertices[1].s[2] = 1.0;
	obj->vertices[2].s[0] = 1.0;
	obj->vertices[2].s[1] = 0.0;
	obj->vertices[2].s[2] = 0.0;
	same_new(game, obj, TRIANGLE);
}
