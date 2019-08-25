#include "gui.h"

void				gui_delete(t_gui **gui)
{
	cl_renderer_delete(&(*gui)->renderer);
	gui_list_delete(&(*gui)->list);
	gui_object_delete(&(*gui)->object);
	gui_image_delete(&(*gui)->image);
	free(*gui);
	*gui = NULL;
}