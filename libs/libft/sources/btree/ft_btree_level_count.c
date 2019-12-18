/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_level_count.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 07:18:46 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 17:33:01 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_btree_level_count(t_btree *root)
{
	int	left_depth;
	int	right_depth;

	if (root == 0)
		return (-1);
	left_depth = ft_btree_level_count(root->left);
	right_depth = ft_btree_level_count(root->right);
	if (left_depth > right_depth)
		return (left_depth + 1);
	else
		return (right_depth + 1);
}
