#include "cl_renderer.h"

void				cl_renderer_create_queue(t_cl_renderer *renderer)
{
	renderer->queue = clCreateCommandQueue(renderer->context,
		renderer->device_id, 0, &renderer->error);
	ASSERT(renderer->error == 0)
	if (RT_DEBUG)
		renderer->queue_length = RT_DEBUG_QUEUE_LENGTH;
	else
		renderer->queue_length = renderer->image->width * renderer->image->height;
}