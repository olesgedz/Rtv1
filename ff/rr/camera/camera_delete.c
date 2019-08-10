#include "camera.h"

void 				camera_delete(t_camera **camera)
{
	free(*camera);
	*camera = NULL;
}
