/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_rb_insert.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 20:19:40 by jblack-b          #+#    #+#             */
/*   Updated: 2019/04/23 21:03:17 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void		f_rb_give_parent(t_rb_node **root)
{
	if ((*root)->left)
		(*root)->left->parent = (*root);
	if ((*root)->right)
		(*root)->right->parent = (*root);
}

static void		ft_rb_color(t_rb_node **root)
{
	if (!root || !*root)
		return ;
	if ((*root)->color == RB_RED)
	{
		if ((*root)->left)
			(*root)->left->color = RB_BLACK;
		if ((*root)->right)
			(*root)->right->color = RB_BLACK;
	}
	else
	{
		if ((*root)->left)
			(*root)->left->color = RB_RED;
		if ((*root)->right)
			(*root)->right->color = RB_RED;
	}
}

void			ft_rb_insert(t_rb_node **root,\
		void *data, int (*cmpf)(void *, void *))
{
	t_rb_node *new;

	if (*root != NULL && cmpf(data, (*root)->data) < 0)
	{
		if ((*root)->left != NULL)
		{
			ft_rb_insert(&(*root)->left, data, cmpf);
			return ;
		}
		else
			(*root)->left = ft_rb_node_create(data);
	}
	else if (root != NULL)
	{
		if ((*root)->right != NULL)
		{
			ft_rb_insert(&(*root)->right, data, cmpf);
			return ;
		}
		else
			(*root)->right = ft_rb_node_create(data);
		ft_rb_color(root);
		f_rb_give_parent(root);
	}
}
