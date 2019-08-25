#include "gui_object.h"

void				gui_object_delete(t_gui_object **object)
{
	free(*object);
	*object = NULL;
}