/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdel_u.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/26 20:10:47 by jblack-b          #+#    #+#             */
/*   Updated: 2018/12/26 20:12:53 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		ft_lstdel_u(t_list **list)
{
	if (*list)
	{
		ft_strclr((char *)(*list)->content);
		free((*list)->content);
		(*list)->content = NULL;
	}
	free(*list);
}
