/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_btree_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 07:24:19 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 17:35:09 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_btree_print(t_btree *root, int spaces)
{
	int	i;

	if (root == NULL)
		return ;
	spaces += 5;
	ft_btree_print(root->right, spaces);
	ft_putstr("\n");
	i = 4;
	while (++i < spaces)
		ft_putstr(" ");
	ft_putstr(root->item);
	ft_btree_print(root->left, spaces);
}
