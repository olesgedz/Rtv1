/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_pop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 03:25:09 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 17:43:42 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_stack_pop(t_stack *stack)
{
	t_list *temp;

	temp = stack->top;
	if (stack->top->next)
		stack->top = stack->top->next;
	return (temp);
}
