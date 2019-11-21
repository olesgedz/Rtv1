/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/07 17:54:13 by qle-guen          #+#    #+#             */
/*   Updated: 2019/10/17 17:25:08 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stdlib.h>

# define MALLOC_F malloc
# define MALLOC_ERR(x) ft_malloc_err(x, __FUNCTION__, __FILE__, __LINE__)

# define MALLOC(p, x) if (!(p = MALLOC_F(x))) MALLOC_ERR(x)
# define MALLOC_N(p, n) MALLOC(p, sizeof(*p) * n)
# define MALLOC1(p) MALLOC_N(p, 1)

# define MALLOC_ZERO(p, x) MALLOC(p, x); ft_bzero(p, x)
# define MALLOC_ZERO_N(p, n) MALLOC_N(p, n); ft_bzero(p, sizeof(*p) * n)
# define MALLOC1_ZERO(p) MALLOC_ZERO(p, 1)

void	*ft_null(size_t size);
void	ft_malloc_err(size_t size, const char *func,
const char *file, int line);

#endif
