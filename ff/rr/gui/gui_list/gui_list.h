#ifndef GUI_LIST_H
# define GUI_LIST_H

# include "gui_names.h"

# include <gtk/gtk.h>

typedef enum			e_gui_list_columns
{
	gl_type_icon,
	gl_name,
	gl_id,
	gl_type_id
}						t_gui_list_columns;

typedef struct			s_gui_list
{
	GtkListStore		*data;
	GtkTreeView			*view;
	GtkTreeSelection	*select;
	GtkTreeIter			iter;
}						t_gui_list;

t_gui_list				*gui_list_new(GtkBuilder *builder);
void					gui_list_delete(t_gui_list **gsl);

#endif
