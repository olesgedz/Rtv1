/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_create_node.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 07:05:32 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 17:32:22 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_btree		*ft_btree_create_node(void *item)
{
	t_btree		*new_node;

	new_node = (t_btree *)malloc(sizeof(t_btree));
	if (new_node == NULL)
		return (NULL);
	new_node->item = item;
	new_node->left = 0;
	new_node->right = 0;
	return (new_node);
}
