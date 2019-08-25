#include "camera.h"

t_camera			*camera_new(INT_REF width, INT_REF height)
{
	t_camera		*new;

	new = (t_camera *)malloc(sizeof(t_camera));
	new->forward =
		(RT_F4_API){0., 0., -1. *  *width / (tan((M_PI / 3.) / 2.))};
	new->axis_x = (RT_F4_API){1., 0., 0.};
	new->axis_y = (RT_F4_API){0., 1., 0.};
	new->axis_z = (RT_F4_API){0., 0., 1.};
	new->position = (RT_F4_API){0., 0., 0.};
	new->width = *width;
	new->height = *height;
	return (new);
}
