/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pointsplit.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/30 19:46:50 by sbrella           #+#    #+#             */
/*   Updated: 2019/02/22 15:06:51 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static size_t	getwlen(const char *s)
{
	size_t a;

	a = 0;
	while ((*s != ' ' && *s != '\t' && *s != '\r') && *s)
	{
		s++;
		a++;
	}
	return (a);
}

static void		ft_free_masmas(size_t a, char **mas)
{
	while (a)
		free(mas[a--]);
	free(mas[0]);
	free(mas);
}

static size_t	ft_count_points(const char *s)
{
	size_t n;
	size_t a;

	n = 0;
	a = 0;
	while (s[a])
	{
		if (s[a] != ' ' || s[a] != '\t' || s[a] != '\r')
		{
			n++;
			while ((s[a] != ' ' && s[a] != '\t' && s[a] != '\r') && s[a])
				a++;
		}
		while (s[a] == ' ' || s[a] == '\t' || s[a] == '\r')
			a++;
	}
	return (n);
}

char			**ft_pointsplit(char const *s)
{
	size_t	count;
	size_t	a;
	char	**mas;

	a = 0;
	if (!(s))
		return (0);
	count = ft_count_points(s);
	if (!(mas = (char**)malloc(sizeof(char*) * (count + 1))))
		return (0);
	while (a < count)
	{
		while (*s == ' ' || *s == '\t' || *s == '\r')
			s++;
		if (!(mas[a] = (char*)malloc(getwlen(s) + 1)))
		{
			ft_free_masmas(a, mas);
			return (0);
		}
		ft_strcopy(mas[a++], s, (getwlen(s) + 1));
		s += getwlen(s);
	}
	mas[a] = 0;
	return (mas);
}
