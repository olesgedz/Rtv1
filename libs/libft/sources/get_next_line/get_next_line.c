/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/12 16:20:41 by jblack-b          #+#    #+#             */
/*   Updated: 2019/10/17 17:35:48 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "get_next_line.h"
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

char			*ft_recharlloc(char **str, char c)
{
	char		*buff;
	size_t		len;

	len = ft_strlen(*str);
	if (!(buff = ft_strnew(len + 1)))
		return (0);
	if (*str)
		ft_memcpy(buff, *str, len);
	buff[len] = c;
	if (*str)
		ft_memdel((void **)str);
	return (buff);
}

static t_stree	*stree_create_node(int fd)
{
	t_stree	*node;

	if (!(node = (t_stree*)malloc(sizeof(t_stree))))
		return (0);
	if (!(node->buff = ft_strnew(BUFF_SIZE)))
	{
		free(node);
		return (0);
	}
	node->fd = fd;
	node->left = 0;
	node->right = 0;
	return (node);
}

static t_stree	*stree_search_item(t_stree *root, int fd)
{
	if (root)
	{
		if (fd == root->fd)
			return (root);
		if (fd > root->fd)
		{
			if (root->right)
				return (stree_search_item(root->right, fd));
			else
				return (root->right = stree_create_node(fd));
		}
		if (fd < root->fd)
		{
			if (root->left)
				return (stree_search_item(root->left, fd));
			else
				return (root->left = stree_create_node(fd));
		}
	}
	else
		return (stree_create_node(fd));
	return (0);
}

static int		reader(t_stree *current_node, char **line)
{
	size_t			i;
	long int		err;

	i = 0;
	while (current_node->buff[i] != '\n')
	{
		if (!(current_node->buff[i]))
		{
			err = read(current_node->fd, current_node->buff, BUFF_SIZE);
			if (err == 0 && ft_strlen(*line))
				current_node->buff[err++] = '\n';
			else if (err <= 0)
				return (err);
			else if (err < BUFF_SIZE && current_node->buff[err - 1] != '\n')
				current_node->buff[err++] = '\n';
			current_node->buff[err] = '\0';
		}
		i = 0;
		while (current_node->buff[i] && current_node->buff[i] != '\n')
			if (!(*line = ft_recharlloc(line, current_node->buff[i++])))
				return (-1);
	}
	i++;
	current_node->buff = ft_strcpy(current_node->buff, current_node->buff + i);
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	static t_stree	*root_node;
	t_stree			*current_node;

	if (!line || !(*line = ft_strnew(0)) || fd < 0 || read(fd, 0, 0) < 0)
		return (-1);
	if (!root_node)
		root_node = stree_search_item(root_node, fd);
	if (!(current_node = stree_search_item(root_node, fd)))
		return (-1);
	return (reader(current_node, line));
}
