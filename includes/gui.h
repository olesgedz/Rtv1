/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:14:40 by lminta            #+#    #+#             */
/*   Updated: 2019/12/10 18:40:18 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GUI_H
# define GUI_H

# include "KW_gui.h"
# include "KW_frame.h"
# include "KW_editbox.h"
# include "KW_label.h"
# include "KW_button.h"
# include "KW_scrollbox.h"
# include "KW_renderdriver_sdl2.h"
# include "libsdl.h"
# define MAX_OBJ	1024
# define MAX_CL		4
# define FR_FZ		WIN_W / 10.
# define FR_ZF		WIN_H / 10.

typedef struct		s_scene_select
{
	KW_Rect			titlerect;
	KW_Rect			winrect;
	KW_Rect			frect;
	KW_Rect			buttonrect[MAX_OBJ];
	KW_Widget		*frame;
	KW_Widget		*label;
	KW_Rect			*rects[1];
	unsigned		weights[1];
	KW_Widget		*buttons[MAX_OBJ];
	char			*names[MAX_OBJ];
	int				max_i;
	int				show;
}					t_scene_select;

typedef struct		s_object_select
{
	KW_Rect			titlerect;
	KW_Rect			winrect;
	KW_Rect			frect;
	KW_Rect			buttonrect[MAX_OBJ];
	KW_Widget		*frame;
	KW_Widget		*label;
	KW_Rect			*rects[1];
	unsigned		weights[1];
	KW_Widget		*buttons[MAX_OBJ];
	char			*names[MAX_OBJ];
	int				max_i;
	int				show;
}					t_object_select;

typedef struct		s_camera_select
{
	KW_Rect			titlerect;
	KW_Rect			winrect;
	KW_Rect			frect;
	KW_Rect			buttonrect[MAX_OBJ];
	KW_Widget		*frame;
	KW_Widget		*label;
	KW_Rect			*rects[1];
	unsigned		weights[1];
	KW_Widget		*buttons[MAX_OBJ];
	char			*names[MAX_OBJ];
	int				max_i;
	int				show;
}					t_camera_select;

typedef struct		s_edit_win
{
	SDL_Texture		*backtex;
	KW_Rect			titlerect;
	KW_Rect			labelrect;
	KW_Rect			winrect;
	KW_Rect			editboxrect;
	KW_Rect			frect;
	KW_Rect			buttonrect;
	KW_Widget		*ed_b;
	KW_Widget		*frame;
	KW_Widget		*label;
	KW_Widget		*okbutton;
	KW_Widget		*servbut;
	KW_Rect			*rects[2];
	unsigned		weights[2];
	int				show;
}					t_edit_win;

typedef struct		s_gui_bar
{
	KW_Rect			frect;
	KW_Rect			buttonrect[30];
	KW_Widget		*frame;
	KW_Widget		*label;
	KW_Rect			*rects[30];
	unsigned		weights[30];
	KW_Widget		*buttons[30];
	char			*names[30];
	int				max_i;
	int				show;
}					t_gui_bar;

typedef struct		s_change_obj
{
	KW_Rect			frect;
	KW_Rect			buttonrect[3];
	KW_Rect			labelrect;
	KW_Rect			editboxrect[3];
	KW_Widget		*frame;
	KW_Widget		*ed_b[30];
	KW_Rect			*rects[4];
	unsigned		weights[4];
	KW_Widget		*buttons[3];
	char			*names[30];
	int				show;
}					t_change_obj;

typedef struct		s_change_cam
{
	KW_Rect			frect;
	KW_Rect			buttonrect[6];
	KW_Rect			labelrect;
	KW_Rect			editboxrect[3];
	KW_Widget		*frame;
	KW_Widget		*ed_b[30];
	KW_Rect			*rects[4];
	unsigned		weights[4];
	KW_Widget		*buttons[6];
	char			*names[30];
	int				show;
	int				cam_id;
}					t_change_cam;

typedef struct		s_obj_type
{
	KW_Rect			frect;
	KW_Rect			buttonrect[8];
	KW_Widget		*frame;
	KW_Widget		*label;
	KW_Rect			*rects[1];
	unsigned		weights[1];
	KW_Widget		*buttons[8];
	char			*names[8];
	int				max_i;
	int				show;
}					t_obj_type;

typedef struct		s_network
{
	KW_Rect			frect;
	KW_Rect			buttonrect[4];
	KW_Widget		*frame;
	KW_Widget		*label;
	KW_Rect			*rects[1];
	unsigned		weights[1];
	KW_Widget		*buttons[3];
	char			*names[3];
	int				show;
	TCPsocket		server;
	TCPsocket 		tcpsock;
	TCPsocket		client[MAX_CL];
	int				clients;
	IPaddress		ip;
	char			*str_ip;
	KW_Widget		*ed_b;
}					t_network;

#endif
