#ifndef GUI_H
# define GUI_H

# include "gui_names.h"

# include "gui_list.h"
# include "gui_object.h"
# include "gui_image.h"
# include "cl_renderer.h"

# include <gtk/gtk.h>

typedef struct		s_gui
{
	t_cl_renderer		*renderer;
	GtkBuilder		*builder;
	GtkWindow		*window;
	t_gui_list		*list;
	t_gui_object	*object;
	t_gui_image		*image;
}					t_gui;

t_gui				*gui_new(int *ac, char ***av);
void				gui_delete(t_gui **gui);

void				gui_loop(t_gui *gui);
void				gui_connect_renderer(t_gui *gui);

#endif
