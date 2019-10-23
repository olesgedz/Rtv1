/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/13 15:14:40 by lminta            #+#    #+#             */
/*   Updated: 2019/10/22 18:53:02 by lminta           ###   ########.fr       */
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
# define MAX_SC		256
# define MAX_OBJ	1024

typedef struct		s_scene_select
{
	KW_Rect			titlerect;
	KW_Rect			winrect;
	KW_Rect			frect;
	KW_Rect			buttonrect[MAX_SC];
	KW_Widget		*frame;
	KW_Widget		*label;
	KW_Rect			*rects[1];
	unsigned		weights[1];
	KW_Widget		*buttons[MAX_SC];
	char			*names[MAX_SC];
	int				max_i;
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
}					t_object_select;

typedef struct		s_edit_win
{
	SDL_Texture		*backtex;
	KW_Rect			titlerect;
	KW_Rect			labelrect;
	KW_Rect			winrect;
	KW_Rect			editboxrect;
	KW_Rect			frect;
	KW_Rect			buttonrect;
	KW_Widget		*edit_box;
	KW_Widget		*frame;
	KW_Widget		*label;
	KW_Widget		*okbutton;
	KW_Rect			*rects[2];
	unsigned		weights[2];
}					t_edit_win;

typedef struct		s_gui
{
	t_sdl			sdl;
	SDL_Event		ev;
	int				quit;
	KW_RenderDriver	*driver;
	KW_Surface		*set;
	KW_GUI			*gui;
	t_edit_win		ed_w;
	t_scene_select	s_s;
	t_object_select	o_s;
	char			*av;
	int				flag;
	int				main_screen;
	int				over_gui;
}					t_gui;

void				print_error_gui(const char *message, const char
*error_message);
char				*start_gui(t_gui *gui);
void				scene_select(t_gui *gui, int i, KW_Widget *const *wid_arr);
void				start_screen(t_gui *gui);
void				init_kiwi(t_gui *gui);
void				quit_kiwi(t_gui *gui);
void				loopa(t_gui *gui);
t_gui				*g_gui(t_gui *gui, int flag);
SDL_Texture			*load_picture(t_gui *gui, const char *filename);
void				quit_kiwi_main(t_gui *gui);
void				main_screen_free(t_gui *gui);
void				over(KW_Widget *widget, int b);
void				leave(KW_Widget *widget, int b);

#endif
