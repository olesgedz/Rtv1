#include "gui.h"

static void			gui_connect_scene(t_gui *gui)
{
	GtkTreeIter		iter;
	int				i;

	i = 0;
	while (i < gui->renderer->data_host.scene->objects_length)
	{
		gtk_list_store_append(gui->list->data, &iter);
		gtk_list_store_set(
			gui->list->data,
			&iter,
			//gs_type_icon, ...,
			gl_name, "oh hi mark",
			gl_id, i,
			gl_type_id, gui->renderer->data_host.scene->objects->type,
			-1);
		i++;
	}
	gtk_widget_show(GTK_WIDGET(gui->list->view));
}

void				gui_connect_renderer(t_gui *gui)
{
	gui_connect_scene(gui);
}