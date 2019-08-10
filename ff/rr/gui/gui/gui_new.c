#include "gui.h"
#include "gui_signal.h"

t_gui				*gui_new(int *ac, char ***av)
{
	t_gui			*new;

	gtk_disable_setlocale();
	gtk_init(ac, av);
	new = (t_gui *)malloc(sizeof(t_gui));
	new->builder = gtk_builder_new_from_file(G_SOURCE);
	new->window = GTK_WINDOW(gtk_builder_get_object(new->builder, G_WINDOW));
	new->list = gui_list_new(new->builder);
	new->object = gui_object_new(new->builder);
	new->image = gui_image_new(new->builder);
	new->renderer = cl_renderer_new(new->image);
	gui_signal_connect(new);
	gtk_widget_show(GTK_WIDGET(new->window));
	return (new);
}