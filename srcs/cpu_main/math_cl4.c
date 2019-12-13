/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_cl4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 21:42:00 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/10 21:42:43 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

cl_float3	sum_cfloat3(cl_float3 one, cl_float3 two)
{
	cl_float3	res;

	res.s[0] = one.s[0] + two.s[0];
	res.s[1] = one.s[1] + two.s[1];
	res.s[2] = one.s[2] + two.s[2];
	return (res);
}

cl_float3	mult_cfloat3(cl_float3 one, float f)
{
	cl_float3	res;

	res.s[0] = one.s[0] * f;
	res.s[1] = one.s[1] * f;
	res.s[2] = one.s[2] * f;
	return (res);
}
