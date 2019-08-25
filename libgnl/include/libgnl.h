/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/07/07 08:40:07 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/09 14:14:03 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBGNL_H
# define LIBGNL_H

# include "libvect.h"

# ifndef GNL_BUFF_SIZE
#  define GNL_BUFF_SIZE 100
# endif

# ifndef GNL_SEP_CHAR
#  define GNL_SEP_CHAR '\n'
# endif

# ifndef GNL_APPEND_CHAR
#  define GNL_APPEND_CHAR GNL_SEP_CHAR
# endif

# ifndef GNL_IGNORE
#  define GNL_IGNORE ""
# endif

# define GNL_STR			1
# define GNL_APPEND			2
# define GNL_CHECK_SIZE		4

int		gnl_vect(int fd, t_vect *v, t_vect *line, int opts);
int		gnl_lines(int fd, t_vect *lines, int opts);
size_t	gnl_read_all(int fd, t_vect *buf, int opts, size_t *calls);

#endif
