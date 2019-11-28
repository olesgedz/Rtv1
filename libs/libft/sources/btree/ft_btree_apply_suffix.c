/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_apply_suffix.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:32:01 by lminta            #+#    #+#             */
/*   Updated: 2019/10/17 17:32:08 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_apply_suffix(t_btree *root, void (*applyf)(void*))
{
	if (root == NULL)
		return ;
	ft_btree_apply_suffix(root->left, (*applyf));
	ft_btree_apply_suffix(root->right, (*applyf));
	(*applyf)(root->item);
}
