#include "gui_object.h"

void 					gui_object_plane_init
						(t_gui_object_plane *plane,
						GtkBuilder *builder,
						GtkOverlay *target)
{
	plane->base.object =
		GTK_BOX(gtk_builder_get_object(builder, GO_PLANE_OBJECT));
	plane->base.offscreen_parent =
		GTK_VIEWPORT(gtk_builder_get_object(builder, GO_PLANE_PARENT));
	gui_object_base_init(&plane->base, target);
	plane->position_x =
		GTK_ENTRY(gtk_builder_get_object(builder, GO_PLANE_POS_X));
	plane->position_y =
		GTK_ENTRY(gtk_builder_get_object(builder, GO_PLANE_POS_Y));
	plane->position_z =
		GTK_ENTRY(gtk_builder_get_object(builder, GO_PLANE_POS_Z));
	plane->normal_x =
		GTK_ENTRY(gtk_builder_get_object(builder, GO_PLANE_NORM_X));
	plane->normal_y =
		GTK_ENTRY(gtk_builder_get_object(builder, GO_PLANE_NORM_Y));
	plane->normal_z =
		GTK_ENTRY(gtk_builder_get_object(builder, GO_PLANE_NORM_Z));
}

void				gui_plane_load(t_gui_object_plane *gui, t_object *plane)
{
	char			buffer[16];
	t_object_plane	*data;

	data = (t_object_plane *)plane->data;
	sprintf(buffer, "%3.1f", data->position.x);
	gtk_entry_set_text(gui->position_x, buffer);
	sprintf(buffer, "%3.1f", data->position.y);
	gtk_entry_set_text(gui->position_y, buffer);
	sprintf(buffer, "%3.1f", data->position.z);
	gtk_entry_set_text(gui->position_z, buffer);
	sprintf(buffer, "%3.1f", data->normal.x);
	gtk_entry_set_text(gui->normal_x, buffer);
	sprintf(buffer, "%3.1f", data->normal.y);
	gtk_entry_set_text(gui->normal_y, buffer);
	sprintf(buffer, "%3.1f", data->normal.z);
	gtk_entry_set_text(gui->normal_z, buffer);
}
