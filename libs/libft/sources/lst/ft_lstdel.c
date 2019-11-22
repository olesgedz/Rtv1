/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/05 17:29:39 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/11 18:37:48 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lstdel(t_list **alst, void (*del)(void*, size_t))
{
	t_list	*acnt;
	t_list	*anxt;

	if (alst && del)
	{
		acnt = *alst;
		while (acnt)
		{
			anxt = acnt->next;
			del((acnt->content), (acnt->content_size));
			free(acnt);
			acnt = anxt;
		}
		*alst = NULL;
	}
}
