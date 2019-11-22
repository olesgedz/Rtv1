/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:51:24 by lminta            #+#    #+#             */
/*   Updated: 2019/11/22 16:11:16 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	basis_shift(t_obj *obj)
{
	obj->basis[0].s[0] = 0;
	obj->basis[0].s[1] = 1;
	obj->basis[0].s[2] = 0;
	obj->basis[1].s[0] = 1;
	obj->basis[1].s[1] = 0;
	obj->basis[1].s[2] = 0;
	obj->basis[2].s[0] = 0;
	obj->basis[2].s[1] = 0;
	obj->basis[2].s[2] = 1;
	obj->shift.s[0] = 0;
	obj->shift.s[0] = 1;
}

void		same_new(t_game *game, t_obj *obj, t_type type)
{
	obj->type = type;
	if (type != TRIANGLE)
	{
		obj->position.s[0] = 0;
		obj->position.s[1] = 0;
		obj->position.s[2] = 0;
		obj->texture = 0;
		obj->normal = 0;
		basis_shift(obj);
	}
	obj->id = game->gpu.objects[game->obj_quantity - 1].id + 1;
	obj->emission.s[0] = 0;
	obj->emission.s[1] = 0;
	obj->emission.s[2] = 0;
	obj->color.s[0] = 1;
	obj->color.s[1] = 1;
	obj->color.s[2] = 1;
	obj->metalness = 0;
	ft_object_push(game, obj);
	main_screen_free(g_gui(0, 0));
	main_screen(g_gui(0, 0), game);
}
