#include "gui_list.h"

t_gui_list		*gui_list_new(GtkBuilder *builder)
{
	t_gui_list	*new;

	new = malloc(sizeof(t_gui_list));
	new->data = GTK_LIST_STORE(gtk_builder_get_object(builder, GL_DATA));
	new->view = GTK_TREE_VIEW(gtk_builder_get_object(builder, GL_VIEW));
	new->select =
		GTK_TREE_SELECTION(gtk_builder_get_object(builder, GL_SELECT));
	return (new);
}