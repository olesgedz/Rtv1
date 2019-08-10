/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/07 18:54:11 by jblack-b          #+#    #+#             */
/*   Updated: 2019/08/10 08:47:52 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_mat4 ft_look_at(t_vec3 eye, t_vec3 up)
{
	t_vec3 w = ft_vec3_normalize(eye);
	t_vec3 u = ft_vec3_normalize(ft_vec3_cross_multiply(up, eye));
	t_vec3 v = ft_vec3_normalize(ft_vec3_cross_multiply(w,u));
  
   return (ft_mat4_transpose((t_mat4){u.x, u.y, u.z, ft_vec3_dot_multiply(u, ft_vec3_neg(eye)),
										v.x, v.y, v.z, ft_vec3_dot_multiply(v, ft_vec3_neg(eye)),
										w.x, w.y, w.z, ft_vec3_dot_multiply(v, ft_vec3_neg(eye)),
										0, 0, 0, 1}));
}


cl_float3 cl_scalar_mul(cl_float3 vector, double scalar)
{
	return (create_cfloat3 (vector.v4[0] * scalar,\
	vector.v4[1] * scalar,\
	vector.v4[2] * scalar));
}

cl_float3 cl_add(cl_float3 v1, cl_float3 v2)
{
	return (create_cfloat3 (v1.v4[0] + v2.v4[0],\
	v1.v4[1] + v2.v4[1],\
	v1.v4[2] + v2.v4[2]));
}