/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 20:26:22 by jblack-b          #+#    #+#             */
/*   Updated: 2019/06/05 15:51:47 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_quaternion t_quaternion_sum(t_quaternion a, t_quaternion b)
{
	t_quaternion new;

	new.s = a.s + b.s;
	new.v = ft_vec3_sum(a.v, b.v);
	return (new);
}

t_quaternion t_quaternion_substract(t_quaternion a, t_quaternion b)
{
	t_quaternion new;

	new.s = a.s - b.s;
	new.v = ft_vec3_substract(a.v, b.v);
	return (new);
}

float ft_quaternion_norm(t_quaternion q)
{

	float scalar = q.s * q.s;
	float imaginary = ft_vec3_dot_multiply(q.v, q.v);
	return (sqrt(scalar + imaginary));
}

float ft_degree_to_rad(float degree)
{
	return (degree * M_PI/180);
}

t_quaternion ft_quaternion_normalize(t_quaternion q)
{
	t_quaternion new;
	float norm;
    float norm_value;

	norm = ft_quaternion_norm(q);
	if (norm != 0)
	{
		norm_value = 1 / norm;
		new.s = q.s * norm_value;
		new.v = ft_vec3_scalar_multiply(q.v, norm_value);
	}
	return (new);
}

//Unit-Norm Quaternion (Special Form)
t_quaternion ft_quaternion_covert_to_unit_norm(t_quaternion q)
{
	t_quaternion new;
	float angle  = ft_degree_to_rad(q.s);

	new.v = ft_vec3_normalize(q.v);
	new.s = cosf(angle * 0.5);
	new.v = ft_vec3_scalar_multiply(q.v, sinf(angle * 0.5));
	return (new);
}

t_quaternion ft_quaternion_conjugate(t_quaternion q)
{
	float scalar=q.s;
	t_vec3 imaginary = ft_vec3_scalar_multiply(q.v, -1);
	return ((t_quaternion){scalar, imaginary});
}

t_quaternion ft_quaternion_inverse(t_quaternion q)
{
	float abs = ft_quaternion_norm(q); 
	abs*=abs;
	abs=1/abs;
	t_quaternion conjugare_val = ft_quaternion_conjugate(q);

	float scalar = conjugare_val.s * abs;
	t_vec3 imaginary = ft_vec3_scalar_multiply(conjugare_val.v, abs);

	return((t_quaternion){scalar, imaginary});

}

t_quaternion ft_quaternion_multiply(t_quaternion a, t_quaternion b)
{
	float scalar = a.s * b.s - ft_vec3_dot_multiply(a.v, b.v);

	t_vec3 imaginary = ft_vec3_sum(ft_vec3_sum(ft_vec3_scalar_multiply(b.v, a.s), ft_vec3_scalar_multiply(a.v, b.s)), ft_vec3_cross_multiply(a.v, b.v)); 
	return ((t_quaternion){scalar, imaginary});
}
//https://www.cprogramming.com/tutorial/3d/quaternions.html
t_quaternion ft_quaternion_multiply2(t_quaternion a, t_quaternion b)
{
	t_quaternion new;
	new.s = (a.s * b.s - a.v.x * b.v.x  - a.v.y * b.v.y - a.v.z * b.v.z);
	new.v.x = (a.s * b.v.x + a.v.x * b.s + a.v.y * b.v.z - a.v.z * b.v.y);
	new.v.y = (a.s * b.v.y - a.v.x * b.v.z + a.v.y * b.s + a.v.z * b.v.x);
	new.v.z  = (a.s * b.v.z + a.v.x * b.v.y - a.v.y * b.v.x + a.v.z * b.s);
	return (new);
}

t_quaternion ft_quaternion_local_rotation(t_vec3 axis, float angle)
{
	t_quaternion local_rotation;
	angle = angle * M_PI / 180.0;
	local_rotation.s = cosf(angle/2);
	local_rotation.v.x = axis.x * sinf(angle/2);
	local_rotation.v.y = axis.y * sinf(angle/2);
	local_rotation.v.z = axis.z * sinf(angle/2);
	return (local_rotation);
}

t_vec3	ft_vec3_rotate_quaterion(float angle, t_vec3 vector, t_vec3 axis)
{
	 //convert our vector to a pure quaternion
    t_quaternion p = (t_quaternion){0,vector};
	//create the real quaternion
	t_quaternion q = (t_quaternion){angle, ft_vec3_normalize(axis)};
	 //convert quaternion to unit norm quaternion
	q = ft_quaternion_covert_to_unit_norm(q);

	t_quaternion q_invesrse = ft_quaternion_inverse(q);

	t_quaternion rotated = ft_quaternion_multiply2(ft_quaternion_multiply(q,p), q_invesrse);
	return (rotated.v);
}

t_vec3	ft_vec3_rotate_quaterion2(float angle, t_vec3 vector, t_vec3 axis)
{
	t_vec3 new;
	t_quaternion local_rotation = ft_quaternion_local_rotation(axis, angle);
	t_quaternion total = (t_quaternion){1, {0, 0, 0}};
	total  = ft_quaternion_multiply2(local_rotation, total);
	new.x = (1 - 2 * pow(total.v.y, 2) - 2.0 * pow(total.v.z, 2)) * vector.x
	+ (2 * total.v.x * total.v.y - 2 * total.s * total.v.z) * vector.y
	+ (2 * total.v.x * total.v.z + 2 * total.s * total.v.y) * vector.z;
	new.y = (2 * total.v.x * total.v.y + 2 * total.s * total.v.z) * vector.x
	+ (1 - 2 * pow(total.v.x, 2) - 2 * pow(total.v.z, 2)) * vector.y
	+ (2 * total.v.y * total.v.z - 2 * total.s * total.v.x) * vector.z;
	new.z = (2 * total.v.x * total.v.z - 2 * total.s * total.v.y) * vector.x
	+ (2 * total.v.y * total.v.z + 2 * total.s * total.v.x) * vector.y
	+ (1 - 2 * pow(total.v.x, 2) - 2 * pow(total.v.y, 2)) * vector.z;
	return (new);
}
