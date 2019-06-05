/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 16:02:42 by jblack-b          #+#    #+#             */
/*   Updated: 2019/06/05 16:16:37 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vec3 ft_vec3_project_test1(t_vec3 p)
{
	t_vec3 new;
	p.z+=300;
	new.x=(p.x*500)/p.z+320, new.y=(p.y*500)/p.z+240;
	return (new);
}

t_vec3 ft_vec3_rotate_test1(t_vec3 p, t_vec3 angle)
{
	float mat[3][3];            // Determine rotation matrix
	t_vec3 new;	
	float xdeg=angle.x*M_PI/180, ydeg=angle.y*M_PI/180, zdeg=angle.z*M_PI/180;
	float sx=(float)sin(xdeg), sy=(float)sin(ydeg), sz=(float)sin(zdeg);
	float cx=(float)cos(xdeg), cy=(float)cos(ydeg), cz=(float)cos(zdeg);
	mat[0][0]=cx*cz+sx*sy*sz, mat[1][0]=-cx*sz+cz*sx*sy, mat[2][0]=cy*sx;
	mat[0][1]=cy*sz, mat[1][1]=cy*cz, mat[2][1]=-sy;
	mat[0][2]=-cz*sx+cx*sy*sz, mat[1][2]=sx*sz+cx*cz*sy, mat[2][2]=cx*cy;
	new.x=p.x*mat[0][0]+p.y*mat[1][0]+p.z*mat[2][0];
	new.y=p.x*mat[0][1]+p.y*mat[1][1]+p.z*mat[2][1];
	new.z=p.x*mat[0][2]+p.y*mat[1][2]+p.z*mat[2][2];	
	return (new);
}


t_vec3 ft_vec3_project_test2(t_vec3 p)
{
	p.x *= 1;
	p.y *= 1;
	p.x += 300;
	p.y += 300;
	return (p);
}

t_vec3 ft_vec3_rotate_test2(t_vec3 p, t_vec3 angle)
{

	t_vec3	v;
	double		x;
	double		y;
	double		z;
	
	x = p.x;
	z = p.z;
	v.x = cos(angle.y) * x + sin(angle.y) * z;
	v.z = -sin(angle.y) * x + cos(angle.y) * z;
	y = p.y;
	z = v.z;
	v.y = cos(angle.x) * y - sin(angle.x) * z;
	v.z = sin(angle.x) * y + cos(angle.x) * z + 300;
	x = v.x;
	y = v.y;
	v.x = cos(angle.z) * x - sin(angle.z) * y;
	v.y = sin(angle.z) * x + cos(angle.z) * y;
	return (v);
}
