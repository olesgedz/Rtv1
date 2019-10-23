/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libgnl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:15:34 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 18:01:19 by lminta           ###   ########.fr       */
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
