/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libvect.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 20:15:41 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/22 17:53:00 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBVECT_H
# define LIBVECT_H
# define GROWTH_FACTOR	1.618
# include <stdlib.h>

typedef struct	s_vect
{
	void		*data;
	size_t		used;
	size_t		total;
}				t_vect;

int				vect_add(t_vect *v, void *data, size_t size);
int				vect_cmp(t_vect *a, t_vect *b);
int				vect_grow(t_vect *v, size_t n);
int				vect_memcmp(t_vect *a, unsigned char *s, size_t n);
int				vect_mset(t_vect *v, unsigned char c, size_t size, size_t n);
int				vect_mset_end(t_vect *v, unsigned char c, size_t size);
int				vect_push(t_vect *v, void *data, size_t size, size_t n);
int				vect_req(t_vect *v, size_t n);
int				vect_str_add(t_vect *v, char *data);
int				vect_str_push(t_vect *v, char *s, size_t n);
t_vect			*vect_new(void *data, size_t size);
t_vect			*vect_wrap(void *data, size_t size);
void			*vect_memmem(t_vect *a, unsigned char *s, size_t n);
void			vect_del(t_vect *v);
void			vect_init(t_vect *v);
void			vect_print(int fd, t_vect *a);

#endif
