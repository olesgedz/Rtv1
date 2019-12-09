/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   net_string.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 16:22:55 by lminta            #+#    #+#             */
/*   Updated: 2019/12/09 17:18:03 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

char	*make_string(char *name, int smpls, int fd)
{
	char	buff[FILE_SIZE];
	int		len;
	char	*res;
	char	*tmp;
	char	*str_smpl;

	fd = open(name, O_RDONLY);
	len = read(fd, buff, FILE_SIZE);
	buff[len] = 0;
	res = ft_strjoin(name, "|");
	str_smpl = ft_itoa(smpls);
	tmp = ft_strjoin(res, str_smpl);
	free(res);
	free(str_smpl);
	res = ft_strjoin(tmp, "|");
	free(tmp);
	tmp = ft_strjoin(res, buff);
	free(res);
	close(fd);
	return (tmp);
}
