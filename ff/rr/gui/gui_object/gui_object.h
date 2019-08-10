#ifndef GUI_OBJECT_H
# define GUI_OBJECT_H

# include "gui_object_base.h"
# include "object_definition.h"
# include "object_list.h"

# include <stdio.h>

typedef struct			s_gui_object_sphere
{
	t_gui_object_base	base;
	GtkEntry			*position_x;
	GtkEntry			*position_y;
	GtkEntry			*position_z;
	GtkEntry			*radius;
}						t_gui_object_sphere;

void 					gui_object_sphere_init
						(t_gui_object_sphere *sphere,
		 				GtkBuilder *builder,
						 GtkOverlay *target);

typedef struct			s_gui_object_plane
{
	t_gui_object_base	base;
	GtkEntry			*position_x;
	GtkEntry			*position_y;
	GtkEntry			*position_z;
	GtkEntry			*normal_x;
	GtkEntry			*normal_y;
	GtkEntry			*normal_z;
}						t_gui_object_plane;

void 					gui_object_plane_init
						(t_gui_object_plane *sphere,
						GtkBuilder *builder,
						GtkOverlay *target);


typedef struct			s_gui_object
{
	t_gui_object_sphere	sphere;
	t_gui_object_plane	plane;
	GtkWidget			*current_widget;
	int 				current_id;
	GtkOverlay			*overlay;
}						t_gui_object;

t_gui_object			*gui_object_new(GtkBuilder *builder);
void					gui_object_delete(t_gui_object **object);

void					gui_sphere_load
						(t_gui_object_sphere *gui, t_object *sphere);
void					gui_plane_load
						(t_gui_object_plane *gui, t_object *plane);

#endif
