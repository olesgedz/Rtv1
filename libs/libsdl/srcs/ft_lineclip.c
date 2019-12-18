/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lineclip.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 02:14:57 by olesgedz          #+#    #+#             */
/*   Updated: 2019/10/17 18:59:31 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libsdl.h"

/*
** Helper function to get a t_point with a size
*/

static t_point	size(int w, int h)
{
	t_point p;

	p.x = w;
	p.y = h;
	return (p);
}

/*
** Gets the region (top, bottom), (left, right)
*/

static int		region(int x, int y, int w, int h)
{
	int c;

	c = 0;
	if (y >= h)
		c |= 1;
	else if (y < 0)
		c |= 2;
	if (x >= w)
		c |= 4;
	else if (x < 0)
		c |= 8;
	return (c);
}

/*
** Clips the lines according to the region codes
*/

static t_point	clip_xy(t_point *p1, t_point *p2, t_point size, int rout)
{
	t_point p;

	if (rout & 1)
	{
		p.x = p1->x + (p2->x - p1->x) * (size.y - p1->y) / (p2->y - p1->y);
		p.y = size.y - 1;
	}
	else if (rout & 2)
	{
		p.x = p1->x + (p2->x - p1->x) * -p1->y / (p2->y - p1->y);
		p.y = 0;
	}
	else if (rout & 4)
	{
		p.x = size.x - 1;
		p.y = p1->y + (p2->y - p1->y) * (size.x - p1->x) / (p2->x - p1->x);
	}
	else
	{
		p.x = 0;
		p.y = p1->y + (p2->y - p1->y) * -p1->x / (p2->x - p1->x);
	}
	return (p);
}

/*
** Implementation of the Cohen–Sutherland line-clipping algorithm
*/

int				lineclip(t_point *p1, t_point *p2, int w, int h)
{
	t_point		p;
	int			r1;
	int			r2;
	int			rout;

	r1 = region(p1->x, p1->y, w, h);
	r2 = region(p2->x, p2->y, w, h);
	while (!(!(r1 | r2) || (r1 & r2)))
	{
		rout = r1 ? r1 : r2;
		p = clip_xy(p1, p2, size(w, h), rout);
		if (rout == r1)
		{
			p1->x = p.x;
			p1->y = p.y;
			r1 = region(p1->x, p1->y, w, h);
		}
		else
		{
			p2->x = p.x;
			p2->y = p.y;
			r2 = region(p2->x, p2->y, w, h);
		}
	}
	return (!(r1 | r2));
}
