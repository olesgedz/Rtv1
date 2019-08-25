#ifndef GUI_IMAGE_H
# define GUI_IMAGE_H

# include "libft_standart.h"
# include "gui_names.h"
# include "rt_parameters.h"

# include "color.h"

# include <gtk/gtk.h>

typedef struct 		s_gui_image
{
	GtkImage		*image;
	GdkPixbuf		*gdk_buffer;
	guchar			*char_buffer;
	t_color			*color_buffer;
	int				width;
	int				height;
}					t_gui_image;

t_gui_image			*gui_image_new(GtkBuilder *builder);
void				gui_image_delete(t_gui_image **image);

#endif
