/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_stack_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 03:18:01 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 17:43:17 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_stack_print(t_stack *stack)
{
	while (stack->top)
	{
		ft_memprint(stack->top->content,\
		stack->top->content_size);
		ft_putchar('\n');
		stack->top = stack->top->next;
	}
}
