/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 18:27:18 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/15 10:41:31 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void				ft_lstiter(t_list *lst, void (*f)(t_list *elem))
{
	while (lst != NULL && f != NULL)
	{
		f(lst);
		lst = lst->next;
	}
}
