/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/05 18:22:47 by jblack-b          #+#    #+#             */
/*   Updated: 2019/06/05 18:44:44 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

/*
*	Fucntion: sum of two points
*	Parameters: two points
*	Return: sum of two points, no parammeters change
*/

t_point3 ft_point3_sum(t_point3 a, t_point3 b)
{ 
    t_point3 new;
    
    new.x = a.x + b.x;
    new.y = a.y + b.y;
    new.z = a.z + b.z;
    return (new);
}

/*
*	Fucntion: sum of two points
*	Parameters: two points
*	Return: sum of two points, no parammeters change
*/

t_point3 ft_point3_substract(t_point3 a, t_point3 b)
{ 
    t_point3 new;
    
    new.x = a.x - b.x;
    new.y = a.y - b.y;
    new.z = a.z - b.z;
    return (new);
}

t_point3 ft_point3_substract_vec3(t_point3 a, t_vec3 b)
{ 
    t_point3 new;
    
    new.x = a.x - b.x;
    new.y = a.y - b.y;
    new.z = a.z - b.z;
    return (new);
}

double ft_point3_substract_sum_2(t_point3 a, t_vec3 b)
{ 
    return (pow(a.x - b.x, 2) + pow(a.y - b.y, 2) + pow(a.z - b.z, 2));
}

double ft_point3_dist(t_point3 a, t_vec3 b)
{ 
    return (sqrt(ft_point3_substract_sum_2(a, b)));
}

t_point3 ft_point3_scalar_multiply(t_point3 a, double b)
{
    t_point3 new;
    
    new.x = a.x * b;
    new.y = a.y * b;
    new.z = a.z * b;

    return (new);
}