# include "gui_signal.h"
# include "gui_object.h"
# include <stdlib.h>

void				gui_s_plane_norm_x(GtkEntry *entry, gpointer ptr)
{
	t_gui			*gui;
	t_object_plane	*data;

	gui = (t_gui *)ptr;
	if (gui->object->current_id == -1)
		return ;
	data = (t_object_plane *)
			gui->renderer->data_host.scene->objects[gui->object->current_id].data;
	data->normal.x = atof(gtk_entry_get_text(entry));
}

void				gui_s_plane_norm_y(GtkEntry *entry, gpointer ptr)
{
	t_gui			*gui;
	t_object_plane	*data;

	gui = (t_gui *)ptr;
	if (gui->object->current_id == -1)
		return ;
	data = (t_object_plane *)
			gui->renderer->data_host.scene->objects[gui->object->current_id].data;
	data->normal.x = atof(gtk_entry_get_text(entry));
}

void				gui_s_plane_norm_z(GtkEntry *entry, gpointer ptr)
{
	t_gui			*gui;
	t_object_plane	*data;

	gui = (t_gui *)ptr;
	if (gui->object->current_id == -1)
		return ;
	data = (t_object_plane *)
			gui->renderer->data_host.scene->objects[gui->object->current_id].data;
	data->normal.x = atof(gtk_entry_get_text(entry));
}