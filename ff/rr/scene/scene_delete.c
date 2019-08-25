#include "scene.h"

void				scene_delete(t_scene **scene)
{
	free(*scene);
	*scene = NULL;
}