/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_2darrayclean.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 01:03:57 by olesgedz          #+#    #+#             */
/*   Updated: 2019/09/20 20:00:25 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_2darrayclean(char ***dst)
{
	size_t i;

	i = 0;
	while ((*dst)[i])
		ft_memdel((void **)&(*dst)[i++]);
	ft_memdel((void **)(*dst));
	dst = NULL;
	return (1);
}
