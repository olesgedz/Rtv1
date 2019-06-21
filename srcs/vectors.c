/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/04 20:23:19 by jblack-b          #+#    #+#             */
/*   Updated: 2019/06/21 15:25:47 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */



#include "rtv1.h"

/*
*	Function: creates 3d point from coordinates
*	Parameters: x y z coodinates of the 3d point as float 
*	Return: malloced t_vec3, no parameters change
*
* ? probably suppose to be t_vector3d or smth
*/

extern inline t_vec3 ft_vec3_create(float x, float y, float z)
{
	t_vec3 new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}
/*
*	Fucntion: sum of two vectors
*	Parameters: two vectors
*	Return: sum of two vectors, no parammeters change
*/


extern inline t_vec3	ft_vec3_sum(t_vec3 a, t_vec3 b)
{
	t_vec3 new;

	new.x = (a.x + b.x);
	new.y = (a.y + b.y);
	new.z = (a.z + b.z);
	return (new);
}

/*
*	Fucntion: substact two vectors
*	Parameters: two vectors
*	Return: difference of two vectors, no parammeters change
*/


extern inline t_vec3	ft_vec3_substract(t_vec3 a, t_vec3 b)
{
	t_vec3 new;

	new.x = (a.x - b.x);
	new.y = (a.y - b.y);
	new.z = (a.z - b.z);
	return (new);
}

/*
*	Fucntion: prints a 3d point
*	Parameters: 3d point, no parameters change
*	Return: none
* ! printf delete it
*/

extern inline void ft_vec3_print(t_vec3 a)
{
	printf("x:%f y:%f z:%f w:%f\n", a.x, a.y, a.z, a.w);
}

/*
*	Fucntion: vector multiplication, dot product
*	Parameters: two vectors no parameters change 
*	Return: scalar float result of multiplication,
*/
extern inline float ft_vec3_dot_multiply(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}



/*
*	Fucntion: vector multiplication by scalar
*	Parameters: two vectors no parameters change 
*	Return: t_vec3 vector result of multiplication,
*/

extern inline t_vec3 ft_vec3_scalar_multiply(t_vec3 a, float b)
{
	return ((t_vec3){a.x * b, a.y * b, a.z * b});
}
/*
*	Fucntion: vector multiplication by vector
*	Parameters: two vectors no parameters change 
*	Return: t_vec3 vector result of multiplication,
*/

extern inline t_vec3 ft_vec3_cross_multiply(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

/*
*	Fucntion: scalar value of vector
*	Parameters: vector, no parameters change 
*	Return: (float) scalar value of a vector
*/

extern inline float ft_vec3_norm(t_vec3 vect)
{
	return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
}

/*
*	Fucntion: changes scalar value of a vector
*	Parameters: vector (changes), needed length
*	Return: normalized vector
*/

extern inline t_vec3 ft_vec3_normalize(t_vec3 vect)
{
	float norm = ft_vec3_norm(vect);
	vect.x = vect.x / norm;
	vect.y = vect.y / norm;
	vect.z = vect.z / norm;
	return (vect);
}


/*
*	Fucntion: projection of vector a on vector b
*	Parameters: two vectors no parameters change 
*	Return: float,
*/

extern inline float ft_vec3_projection(t_vec3 a, t_vec3 b)
{
	return (ft_vec3_dot_multiply(b, a) /  ft_vec3_norm(b));
}

/*
*	Function: returns negative vector
*	Parameters: vector
*	Return: malloced t_vec3, no parameters change
*
* ? probably suppose to be t_vector3d or smth
*/

extern inline t_vec3 ft_vec3_neg(t_vec3 v)
{
	return (ft_vec3_scalar_multiply(v, -1));
}

double	ft_vec3_angle(t_vec3 a, t_vec3 b)
{
	t_vec3	v1;
	t_vec3	v2;

	v1 = ft_vec3_normalize(a);
	v2 = ft_vec3_normalize(b);
	return (acos(ft_vec3_dot_multiply(v1, v2)));
}

double			ft_vec3_length(t_vec3 v1)
{
	return (sqrt(v1.x * v1.x + v1.y * v1.y + v1.z * v1.z));
}


extern inline t_vec3 ft_vec3_sum_poin3(t_vec3 a, t_point3 b)
{
	t_vec3 new;

	new.x = (a.x + b.x);
	new.y = (a.y + b.y);
	new.z = (a.z + b.z);
	return (new);
}

t_vec3	ft_vec3_multiply_matrix(t_vec3 v, t_mat4 m)
{
	t_vec3	res;

	res.x = v.x * m.matrix[0][0] +
			v.y * m.matrix[0][1] +
			v.z * m.matrix[0][2] +
			v.w * m.matrix[0][3];
	res.y = v.x * m.matrix[1][0] +
			v.y * m.matrix[1][1] +
			v.z * m.matrix[1][2] +
			v.w * m.matrix[1][3];
	res.z = v.x * m.matrix[2][0] +
			v.y * m.matrix[2][1] +
			v.z * m.matrix[2][2] +
			v.w * m.matrix[2][3];
	res.w = v.x * m.matrix[3][0] +
			v.y * m.matrix[3][1] +
			v.z * m.matrix[3][2] +
			v.w * m.matrix[3][3];
	return (res);
}