# include "gui_signal.h"
# include "gui_object.h"
# include <stdlib.h>

void				gui_s_sphere_pos_x(GtkEntry *entry, gpointer ptr)
{
	t_gui			*gui;
	t_object_sphere	*data;

	gui = (t_gui *)ptr;
	if (gui->object->current_id == -1)
		return ;
	data = (t_object_sphere *)
		gui->renderer->data_host.scene->objects[gui->object->current_id].data;
	data->position.x = atof(gtk_entry_get_text(entry));
}

void				gui_s_sphere_pos_y(GtkEntry *entry, gpointer ptr)
{
	t_gui			*gui;
	t_object_sphere	*data;

	gui = (t_gui *)ptr;
	if (gui->object->current_id == -1)
		return ;
	data = (t_object_sphere *)
			gui->renderer->data_host.scene->objects[gui->object->current_id].data;
	data->position.y = atof(gtk_entry_get_text(entry));
}

void				gui_s_sphere_pos_z(GtkEntry *entry, gpointer ptr)
{
	t_gui			*gui;
	t_object_sphere	*data;

	gui = (t_gui *)ptr;
	if (gui->object->current_id == -1)
		return ;
	data = (t_object_sphere *)
			gui->renderer->data_host.scene->objects[gui->object->current_id].data;
	data->position.z= atof(gtk_entry_get_text(entry));
}

