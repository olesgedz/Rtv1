/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:47:28 by jblack-b          #+#    #+#             */
/*   Updated: 2019/06/08 20:58:34 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
*	Function: returns negative vector
*	Parameters: vector
*	Return: malloced t_vec3, no parameters change
*
* ? probably suppose to be t_vector3d or smth
*/

extern inline t_normal3 ft_normal3_neg(t_normal3 v)
{
	return (ft_normal3_scalar_multiply(v, 1));
}

extern inline t_normal3 ft_normal3_scalar_multiply(t_normal3 a, float b)
{
	return ((t_normal3){a.x * b, a.y * b, a.z * b});
}


/*
*	Fucntion: sum of two vectors
*	Parameters: two vectors
*	Return: sum of two vectors, no parammeters change
*/


extern inline t_normal3	ft_normal3_sum(t_normal3 a, t_normal3 b)
{
	t_normal3 new;

	new.x = (a.x + b.x);
	new.y = (a.y + b.y);
	new.z = (a.z + b.z);
	return (new);
}
 float ft_normal3_dot_multiply_vec3(t_normal3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}


