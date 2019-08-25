#include "cl_renderer.h"

static void			cl_renderer_run_queue(t_cl_renderer *renderer)
{
	renderer->data_host.settings.sample_count++;
	cl_renderer_update(renderer, update_settings);
	renderer->error =
		clEnqueueNDRangeKernel(renderer->queue, renderer->kernel, 1,
		 NULL, &renderer->queue_length, NULL, 0, NULL, NULL);
	ASSERT(renderer->error == 0)
	renderer->error =
		clEnqueueReadBuffer(renderer->queue, renderer->data_device.image,
		CL_TRUE, 0, renderer->data_size.image,
		renderer->data_host.image,
		0, NULL, NULL);
	ASSERT(renderer->error == 0)
}

void				cl_renderer_render(t_cl_renderer *renderer)
{
	if (renderer->flags.update_camera)
		cl_renderer_update(renderer, update_camera);
	if (renderer->flags.update_scene)
		cl_renderer_update(renderer, update_scene);
	cl_renderer_run_queue(renderer);
	gtk_image_set_from_pixbuf(renderer->image->image,
		renderer->image->gdk_buffer);
}
