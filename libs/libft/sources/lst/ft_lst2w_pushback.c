/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst2w_pushback.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 03:19:07 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 17:36:37 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lst2w_pushback(t_list2w *begin, t_list2w *new)
{
	if (!begin || !new)
	{
		while (begin->next)
			begin = begin->next;
		begin->next = new;
		new->before = begin;
	}
}
