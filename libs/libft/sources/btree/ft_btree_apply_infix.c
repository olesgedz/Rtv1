/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_infix.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 07:12:00 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 17:30:09 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_apply_infix(t_btree *root, void (*applyf)(void*))
{
	if (root == NULL)
		return ;
	ft_btree_apply_infix(root->left, (*applyf));
	(*applyf)(root->item);
	ft_btree_apply_infix(root->right, (*applyf));
}
