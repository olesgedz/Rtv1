/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_by_level.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 07:23:19 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 17:26:43 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_apply_by_level(t_btree *root,
void (*applyf)(void *item, int current_level, int is_first_elem))
{
	t_queue	*queue;
	t_queue	*pop;

	queue = NULL;
	ft_queue_push(&queue, root, 0);
	while (queue != NULL)
	{
		pop = ft_queue_pop(&queue);
		applyf(pop->node->item, pop->current_level, pop->is_first_elem);
		if (pop->node->left != NULL)
			ft_queue_push(&queue, pop->node->left, pop->current_level + 1);
		if (pop->node->right != NULL)
			ft_queue_push(&queue, pop->node->right, pop->current_level + 1);
	}
}
