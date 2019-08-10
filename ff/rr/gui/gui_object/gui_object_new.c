#include "gui_object.h"

t_gui_object		*gui_object_new(GtkBuilder *builder)
{
	t_gui_object	*new;

	new = malloc(sizeof(t_gui_object));
	new->current_id = -1;
	new->current_widget = NULL;
	new->overlay =
		GTK_OVERLAY(gtk_builder_get_object(builder, GO_OVERLAY));
	gui_object_sphere_init(&new->sphere, builder, new->overlay);
	gui_object_plane_init(&new->plane, builder, new->overlay);
	return (new);
}
