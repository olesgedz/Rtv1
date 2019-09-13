/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:14:40 by lminta            #+#    #+#             */
/*   Updated: 2019/09/13 17:32:00 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

#include "KW_gui.h"
#include "KW_frame.h"
#include "KW_editbox.h"
#include "KW_label.h"
#include "KW_button.h"
#include "KW_renderdriver_sdl2.h"

typedef struct
{
	KW_RenderDriver	*driver;
	KW_Surface		*set;
	KW_GUI			*gui;
	KW_Widget		*editBox;
}					t_gui;

#endif
