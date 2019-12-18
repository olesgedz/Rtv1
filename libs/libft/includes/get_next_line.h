/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/23 22:51:08 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 17:24:31 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 20

typedef struct		s_stree
{
	struct s_stree	*left;
	struct s_stree	*right;
	char			*buff;
	int				fd;
}					t_stree;

int					get_next_line(const int fd, char **line);

#endif
