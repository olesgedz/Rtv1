#include "cl_renderer.h"

void 				cl_renderer_camera_move
					(t_cl_renderer *renderer, t_camera_direction direction)
{
	renderer->flags.update_camera = 1;
	renderer->flags.update_settings = 1;
	renderer->data_host.settings.sample_count = 0;
	camera_move(renderer->data_host.camera, direction, 1.f);
	cl_renderer_render(renderer);
}