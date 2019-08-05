/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cl_krl_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/14 15:54:21 by qle-guen          #+#    #+#             */
/*   Updated: 2017/02/09 14:20:32 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "malloc.h"
#include "libcl.h"

void
	cl_krl_init
	(t_cl_krl *krl
	, size_t nargs)
{
	MALLOC_N(krl->args, nargs);
	MALLOC_N(krl->sizes, nargs);
	krl->nargs = nargs;
}
