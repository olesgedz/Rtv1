#include "gui_image.h"

void				gui_image_delete(t_gui_image **image)
{
	free(*image);
	*image = NULL;
}