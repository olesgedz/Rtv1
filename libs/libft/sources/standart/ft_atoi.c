/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/27 15:37:56 by jblack-b          #+#    #+#             */
/*   Updated: 2019/01/16 01:25:11 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void		ft_atoi_skip(const char **str, int *sign)
{
	while (**str == ' ' || **str == '\n'
	|| **str == '\t' || **str == '\r'
	|| **str == '\v' || **str == '\f')
		(*str)++;
	if (**str == '+' || **str == '-')
	{
		if (**str == '-')
			*sign = -1;
		(*str)++;
	}
	while (**str == '0')
		(*str)++;
}

int				ft_atoi(const char *str)
{
	long	int				nbr;
	int						sign;

	sign = 1;
	nbr = 0;
	ft_atoi_skip(&str, &sign);
	while ('0' <= *str && *str <= '9')
	{
		if (nbr * 10 + *str - '0' < nbr)
		{
			if (sign == 1)
				return (-1);
			else
				return (0);
		}
		nbr = nbr * 10 + *str - '0';
		str++;
	}
	return ((int)(nbr) * sign);
}
