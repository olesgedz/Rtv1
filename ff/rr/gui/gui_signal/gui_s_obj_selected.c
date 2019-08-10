#include "gui_signal.h"

void				gui_s_obj_selected(
					GtkTreeSelection *select,
					gpointer ptr)
{
	t_gui			*gui;
	GtkTreeModel	*model;
	t_object		*object;

	gui = (t_gui *)ptr;
	if (!gtk_tree_selection_get_selected(gui->list->select,
		&model, &gui->list->iter))
		return ;
	if (gui->object->current_widget)
		gtk_widget_hide(gui->object->current_widget);
	gtk_tree_model_get(model,
			&gui->list->iter, gl_id, &gui->object->current_id, -1);
	object = gui->renderer->data_host.scene->objects + gui->object->current_id;
	if (object->type == object_sphere)
	{
		gui_sphere_load(&gui->object->sphere, object);
		gui->object->current_widget = GTK_WIDGET(gui->object->sphere.base.object);
	}
	if (object->type == object_plane)
	{
		gui_plane_load(&gui->object->plane, object);
		gui->object->current_widget = GTK_WIDGET(gui->object->plane.base.object);
	}
	gtk_widget_show(gui->object->current_widget);
}