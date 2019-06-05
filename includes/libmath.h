/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libmath.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/03 12:54:27 by jblack-b          #+#    #+#             */
/*   Updated: 2019/06/05 15:10:42 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBMATH_H
#define LIBMATH_H

#include "libft.h"
#include <stdlib.h>
#include <stdio.h>
#define min(a,b)             (((a) < (b)) ? (a) : (b)) // min: Choose smaller of two scalars.
#define max(a,b)             (((a) > (b)) ? (a) : (b)) // max: Choose greater of two scalars.
#define clamp(a, mi,ma)      min(max(a,mi),ma)         // clamp: Clamp value into set range.
#define vxs(x0,y0, x1,y1)    ((x0)*(y1) - (x1)*(y0))   // vxs: Vector cross product
// Overlap:  Determine whether the two number ranges overlap.
#define Overlap(a0,a1,b0,b1) (min(a0,a1) <= max(b0,b1) && min(b0,b1) <= max(a0,a1))
// IntersectBox: Determine whether two 2D-boxes intersect.
#define IntersectBox(x0,y0, x1,y1, x2,y2, x3,y3) (Overlap(x0,x1,x2,x3) && Overlap(y0,y1,y2,y3))
// PointSide: Determine which side of a line the point is on. Return value: <0, =0 or >0.
#define PointSide(px,py, x0,y0, x1,y1) vxs((x1)-(x0), (y1)-(y0), (px)-(x0), (py)-(y0))
// Intersect: Calculate the point of intersection between two lines.
#define Intersect(x1,y1, x2,y2, x3,y3, x4,y4) ((struct xy) { \
	vxs(vxs(x1,y1, x2,y2), (x1)-(x2), vxs(x3,y3, x4,y4), (x3)-(x4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)), \
	vxs(vxs(x1,y1, x2,y2), (y1)-(y2), vxs(x3,y3, x4,y4), (y3)-(y4)) / vxs((x1)-(x2), (y1)-(y2), (x3)-(x4), (y3)-(y4)) });
#define fpart(x) ((x) < 0 ? 1 - ((x) - floorf(x)) : (x) - floorf(x))
#define rfpart(x) (1 - fpart(x))


typedef	struct 	s_vec3 t_vec3;

typedef	struct s_point3
{
	float x;
	float y;
	float z;
} t_point3;

struct 	s_vec3
{
	float x;
	float y;
	float z;
};

typedef struct 	s_mat3
{
	double matrix[3][3];
} t_mat3;

typedef struct 	s_mat4
{
	double matrix[4][4];
} t_mat4;

typedef struct s_p2d
{
	float x;
	float y;
} t_p2d;

typedef struct s_quaternion
{
	float s; //scalar
	t_vec3 v;
} t_quaternion;


inline t_vec3 ft_vec3_create(float x, float y, float z);
inline t_vec3	ft_vec3_sum(t_vec3 a, t_vec3 b);
inline t_vec3	ft_vec3_substract(t_vec3 a, t_vec3 b);
inline float ft_vec3_dot_multiply(t_vec3 a, t_vec3 b);
inline t_vec3 ft_vec3_scalar_multiply(t_vec3 a, float b);
inline t_vec3 ft_vec3_cross_multiply(t_vec3 a, t_vec3 b);
inline float ft_vec3_norm(t_vec3 vect);
inline t_vec3 ft_vec3_normalize(t_vec3 vect);
inline float ft_vec3_projection(t_vec3 a, t_vec3 b);
void ft_vec3_print(t_vec3 a);

t_quaternion t_quaternion_sum(t_quaternion a, t_quaternion b);
t_quaternion t_quaternion_substract(t_quaternion a, t_quaternion b);
float ft_quaternion_norm(t_quaternion q);
float ft_degree_to_rad(float degree);
t_quaternion ft_quaternion_normalize(t_quaternion q);
t_quaternion ft_quaternion_covert_to_unit_norm(t_quaternion q);
t_quaternion ft_quaternion_conjugate(t_quaternion q);
t_quaternion ft_quaternion_inverse(t_quaternion q);
t_quaternion ft_quaternion_multiply(t_quaternion a, t_quaternion b);
t_quaternion ft_quaternion_multiply2(t_quaternion a, t_quaternion b);
t_quaternion ft_quaternion_local_rotation(t_vec3 axis, float angle);

t_vec3	ft_vec3_rotate_quaterion(float angle, t_vec3 vector, t_vec3 axis);
t_vec3	ft_vec3_rotate_quaterion2(float angle, t_vec3 vector, t_vec3 axis);


#endif