#include "gui_image.h"

t_gui_image			*gui_image_new(GtkBuilder *builder)
{
	t_gui_image		*new;

	new = malloc(sizeof(t_gui_image));
	new->width = GI_DEFAULT_WIDTH;
	new->height = GI_DEFAULT_HEIGHT;
	new->image = GTK_IMAGE(gtk_builder_get_object(builder, GI_IMAGE));
	new->gdk_buffer =
		gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, new->width, new->height);
	new->char_buffer = gdk_pixbuf_get_pixels(new->gdk_buffer);
	new->color_buffer = (t_color *)new->char_buffer;
	for (int i = 0; i < new->width * new->height; i++)
		new->color_buffer[i] = (t_color){0, 0, 0, 255};
	gtk_image_set_from_pixbuf(new->image, new->gdk_buffer);
	gtk_widget_show(GTK_WIDGET(new->image));
	return (new);
}
