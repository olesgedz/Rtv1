/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclean.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/25 16:04:10 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/02 23:16:44 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

void		ft_lstclean(t_list **begin)
{
	t_list *next_tmp;

	next_tmp = NULL;
	while (*begin)
	{
		free((*begin)->content);
		(*begin)->content = NULL;
		next_tmp = (*begin)->next;
		free(*begin);
		*begin = NULL;
		*begin = next_tmp;
	}
	*begin = NULL;
	begin = NULL;
}
