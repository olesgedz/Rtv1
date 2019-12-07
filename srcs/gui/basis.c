/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 21:18:13 by lminta            #+#    #+#             */
/*   Updated: 2019/12/03 21:25:10 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

static void	plane_basis(t_obj *obj)
{
	if (obj->v.s[0] != 0.0f || obj->v.s[1] != 0.0f)
		obj->basis[0] = normalize(create_cfloat3(obj->v.s[1], -obj->v.s[0], 0));
	else
		obj->basis[0] = create_cfloat3(0.0f, 1.0f, 0.0f);
	obj->basis[1] = cross(obj->v, obj->basis[0]);
	obj->basis[2] = cross(obj->basis[0], obj->basis[1]);
}

static void	sphere_basis(t_obj *obj)
{
	obj->basis[0] = create_cfloat3(1.0, 0.0, 0.0);
	obj->basis[1] = create_cfloat3(0.0, 1.0, 0.0);
	obj->basis[2] = cross(obj->basis[0], obj->basis[1]);
}

static void	cylinder_basis(t_obj *obj)
{
	if (obj->v.s[0] != 0.0f || obj->v.s[1] != 0.0f)
		obj->basis[0] = normalize(create_cfloat3(obj->v.s[1], -obj->v.s[0], 0));
	else
		obj->basis[0] = create_cfloat3(0.0f, 1.0f, 0.0f);
	obj->basis[1] = cross(obj->basis[0], obj->v);
	obj->basis[2] = create_cfloat3(0.0, 0.0, 1.0);
}

void		parse_new_basis(t_obj *obj)
{
	if (obj->type == SPHERE)
		sphere_basis(obj);
	else if (obj->type == CYLINDER)
		cylinder_basis(obj);
	else
		plane_basis(obj);
}
