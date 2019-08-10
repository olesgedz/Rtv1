#include "gui_signal.h"

gboolean			gui_s_key
					(GtkWindow *window, GdkEventKey *key, gpointer ptr)
{
	t_gui			*gui;

	gui = (t_gui *)ptr;
	if (key->keyval == GDK_KEY_Escape)
		gtk_main_quit();
	else if (key->keyval == GDK_KEY_Return)
		cl_renderer_render(gui->renderer);
	else if (key->keyval == GDK_KEY_a)
		cl_renderer_camera_move(gui->renderer, left);
	else if (key->keyval == GDK_KEY_d)
		cl_renderer_camera_move(gui->renderer, right);
	else if (key->keyval == GDK_KEY_q)
		cl_renderer_camera_move(gui->renderer, up);
	else if (key->keyval == GDK_KEY_e)
		cl_renderer_camera_move(gui->renderer, down);
	else if (key->keyval == GDK_KEY_w)
		cl_renderer_camera_move(gui->renderer, forward);
	else if (key->keyval == GDK_KEY_s)
		cl_renderer_camera_move(gui->renderer, backward);
	return (FALSE);
}