#include "gui_signal.h"

#define MACRO(x) gtk_builder_add_callback_symbol(gui->builder, #x, G_CALLBACK(x));

void				gui_signal_connect(t_gui *gui)
{
	MACRO(gui_s_key)
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_key", G_CALLBACK(gui_s_key));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_obj_selected", G_CALLBACK(gui_s_obj_selected));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_obj_add", G_CALLBACK(gui_s_obj_add));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_sphere_pos_x", G_CALLBACK(gui_s_sphere_pos_x));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_sphere_pos_y", G_CALLBACK(gui_s_sphere_pos_y));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_sphere_pos_z", G_CALLBACK(gui_s_sphere_pos_z));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_sphere_rad", G_CALLBACK(gui_s_sphere_rad));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_plane_pos_x", G_CALLBACK(gui_s_plane_pos_x));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_plane_pos_y", G_CALLBACK(gui_s_plane_pos_y));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_plane_pos_z", G_CALLBACK(gui_s_plane_pos_z));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_plane_norm_x", G_CALLBACK(gui_s_plane_norm_x));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_plane_norm_y", G_CALLBACK(gui_s_plane_norm_y));
	gtk_builder_add_callback_symbol(gui->builder, "gui_s_plane_norm_z", G_CALLBACK(gui_s_plane_norm_z));
	gtk_builder_connect_signals(gui->builder, (gpointer)gui);
}