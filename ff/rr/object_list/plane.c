#include "object_interaction.h"

void				object_plane_build(t_object *space, va_list *args)
{
	t_object_plane	*data;

	data = (t_object_plane *)space->data;
	data->position = va_arg(*args, RT_F4_API);
	data->normal = va_arg(*args, RT_F4_API);
	space->type = object_plane;
}
