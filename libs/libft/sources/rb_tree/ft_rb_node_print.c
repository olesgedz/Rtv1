/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rb_node_print.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 20:28:24 by jblack-b          #+#    #+#             */
/*   Updated: 2019/04/23 20:30:44 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void		ft_rb_node_print(t_rb_node *root, int spaces)
{
	int i;

	i = 0;
	if (root == NULL)
		return ;
	spaces += 5;
	ft_rb_node_print(root->right, spaces);
	ft_putstr("\n");
	while (i++ < spaces)
		ft_putstr(" ");
	ft_putstr(root->data);
	if (root->color == RB_RED)
		ft_putstr("-R");
	else
		ft_putstr("-B");
	ft_putstr(" p->");
	if (root->parent)
		ft_putstr(root->parent->data);
	ft_rb_node_print(root->left, spaces);
}
