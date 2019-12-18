/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 00:55:35 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 18:54:24 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	Fucntion: get intensity
**	Parameters: starting point , end point, precentage of it
**	Return: resulting intensity
**	? name change?
*/

int		ft_get_light(int start, int end, double percentage)
{
	return ((int)((1 - percentage) * start + percentage * end));
}
