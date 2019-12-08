/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_new.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 15:51:24 by lminta            #+#    #+#             */
/*   Updated: 2019/12/04 22:46:36 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void	in_cl(t_game *game)
{
	int ret = 0;

	main_screen_free(g_gui(0, 0));
	main_screen(g_gui(0, 0), game);
	clReleaseMemObject(game->cl_info->progs[0].krls[0].args[1]);
	ret = cl_krl_init_arg(&game->cl_info->progs[0].krls[0], 1,
	game->obj_quantity * sizeof(t_obj), game->gpu.objects);
	ERROR(ret);
	ret = cl_krl_mem_create(game->cl_info, &game->cl_info->progs[0].krls[0], 1,
	CL_MEM_READ_WRITE);
	ERROR(ret);
	ret = cl_krl_set_arg(&game->cl_info->progs[0].krls[0], 1);
	ERROR(ret);
}

void		same_new(t_game *game, t_obj *obj, t_type type)
{
	obj->type = type;
	obj->is_visible = 0;
	if (type != TRIANGLE)
	{
		obj->position = create_cfloat3(0, 0, 0);
		obj->texture = 0;
		obj->normal = 0;
		parse_new_basis(obj);
		obj->shift = create_cfloat2(0, 0);
	}
	obj->id = game->gpu.objects[game->obj_quantity - 1].id + 1;
	obj->emission = create_cfloat3(0, 0, 0);
	obj->color = create_cfloat3(1, 1, 1);
	obj->metalness = 0;
	obj->refraction = 0;
	ft_object_push(game, obj);
	in_cl(game);
}

void			refraction(t_gui *gui, t_obj *obj, int *i)
{
	gui->c_o.labelrect.y += 30;
	gui->c_o.editboxrect[0].y += 30;
	gui->c_o.editboxrect[1].y += 30;
	gui->c_o.editboxrect[2].y += 30;
	KW_CreateLabel(gui->gui, gui->c_o.frame, "Refraction", gui->c_o.rects[0]);
	gui->c_o.ed_b[(*i)++] = f_e(gui, obj->refraction, gui->c_o.rects[1]);
}
