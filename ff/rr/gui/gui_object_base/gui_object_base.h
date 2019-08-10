#ifndef GUI_OBJECT_BASE_H
# define GUI_OBJECT_BASE_H

# include "gui_names.h"

# include <gtk/gtk.h>

typedef struct			s_gui_object_base
{
	GtkBox				*object;
	GtkViewport			*offscreen_parent;
}						t_gui_object_base;

void					gui_object_base_init
						(t_gui_object_base *gob, GtkOverlay *target);


#endif
