/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rb_node_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 19:59:41 by jblack-b          #+#    #+#             */
/*   Updated: 2019/04/23 20:03:44 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_rb_node		*ft_rb_node_create(void *data)
{
	t_rb_node *new_node;

	if (!(new_node = (t_rb_node *)malloc(sizeof(t_rb_node))))
		return (NULL);
	new_node->data = data;
	new_node->parent = NULL;
	new_node->right = NULL;
	new_node->left = NULL;
	new_node->color = RB_BLACK;
	return (new_node);
}
