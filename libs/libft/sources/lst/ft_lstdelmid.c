/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelmid.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 20:13:27 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/26 20:47:30 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_lstdelmid(t_list **begin, t_list **list)
{
	t_list *temp;
	t_list *join;

	temp = *begin;
	if (temp != NULL && temp == &(**list))
	{
		*begin = (*begin)->next;
	}
	else
	{
		while (temp != NULL && temp->next)
		{
			if (temp->next == &(**list))
			{
				join = temp->next->next;
				ft_lstdel_u(&(temp->next));
				temp->next = join;
			}
			temp = temp->next;
		}
	}
	if (temp == NULL)
		return (1);
	return (1);
}
