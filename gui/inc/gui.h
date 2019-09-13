/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:14:40 by lminta            #+#    #+#             */
/*   Updated: 2019/09/13 22:46:31 by lminta           ###   ########.fr       */
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

typedef struct		t_edit_win
{
	KW_Rect			titlerect;
	KW_Rect			labelrect;
	KW_Rect			winrect;
	KW_Rect			editboxrect;
	KW_Rect			framerect;
	KW_Rect			buttonrect;
	KW_Widget		*editBox;
	KW_Widget		*frame;
	KW_Widget		*okbutton;
	KW_Rect			*rects[2];
	unsigned		weights[2];
}					t_edit_win;

typedef struct		s_gui
{
	KW_RenderDriver	*driver;
	KW_Surface		*set;
	KW_GUI			*gui;
	t_edit_win		ed_w;
}					t_gui;



#endif
