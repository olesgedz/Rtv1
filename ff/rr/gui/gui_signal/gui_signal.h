#ifndef GUI_SIGNALS_H
# define GUI_SIGNALS_H

# include "gui.h"
# include "gui_object.h"

void				gui_signal_connect(t_gui *gui);

gboolean			gui_s_key
					(GtkWindow *window, GdkEventKey *key, gpointer ptr);

void				gui_s_obj_selected(
					GtkTreeSelection *select,
					gpointer ptr);
void				gui_s_obj_add(
					GtkTreeSelection *select,
					gpointer ptr);

void				gui_s_sphere_pos_x(GtkEntry *entry, gpointer ptr);
void				gui_s_sphere_pos_y(GtkEntry *entry, gpointer ptr);
void				gui_s_sphere_pos_z(GtkEntry *entry, gpointer ptr);
void				gui_s_sphere_rad(GtkEntry *entry, gpointer ptr);

void				gui_s_plane_pos_x(GtkEntry *entry, gpointer ptr);
void				gui_s_plane_pos_y(GtkEntry *entry, gpointer ptr);
void				gui_s_plane_pos_z(GtkEntry *entry, gpointer ptr);
void				gui_s_plane_norm_x(GtkEntry *entry, gpointer ptr);
void				gui_s_plane_norm_y(GtkEntry *entry, gpointer ptr);
void				gui_s_plane_norm_z(GtkEntry *entry, gpointer ptr);

#endif
