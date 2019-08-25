#include "gui_object.h"

void 				gui_object_sphere_init
					(t_gui_object_sphere *sphere,
					GtkBuilder *builder,
					GtkOverlay *target)
{
	sphere->base.object =
		GTK_BOX(gtk_builder_get_object(builder, GO_SPHERE_OBJECT));
	sphere->base.offscreen_parent =
		GTK_VIEWPORT(gtk_builder_get_object(builder, GO_SPHERE_PARENT));
	gui_object_base_init(&sphere->base, target);
	sphere->position_x =
		GTK_ENTRY(gtk_builder_get_object(builder, GO_SPHERE_POS_X));
	sphere->position_y =
		GTK_ENTRY(gtk_builder_get_object(builder, GO_SPHERE_POS_Y));
	sphere->position_z =
		GTK_ENTRY(gtk_builder_get_object(builder, GO_SPHERE_POS_Z));
	sphere->radius =
		GTK_ENTRY(gtk_builder_get_object(builder, GO_SPHERE_RAD));
}

void				gui_sphere_load(t_gui_object_sphere *gui, t_object *sphere)
{
	char			buffer[16];
	t_object_sphere	*data;

	data = (t_object_sphere *)sphere->data;
	sprintf(buffer, "%3.1f", data->position.x);
	gtk_entry_set_text(gui->position_x, buffer);
	sprintf(buffer, "%3.1f", data->position.y);
	gtk_entry_set_text(gui->position_y, buffer);
	sprintf(buffer, "%3.1f", data->position.z);
	gtk_entry_set_text(gui->position_z, buffer);
	sprintf(buffer, "%3.1f", data->radius);
	gtk_entry_set_text(gui->radius, buffer);
}