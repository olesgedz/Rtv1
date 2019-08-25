#include "cl_renderer.h"

void				cl_renderer_set_arguments(t_cl_renderer *renderer)
{
	renderer->error = clSetKernelArg(renderer->kernel,
		0, sizeof(cl_mem), &renderer->data_device.camera);
	renderer->error += clSetKernelArg(renderer->kernel,
		1, sizeof(cl_mem), &renderer->data_device.scene);
	renderer->error += clSetKernelArg(renderer->kernel,
		2, sizeof(cl_mem), &renderer->data_device.image);
	renderer->error += clSetKernelArg(renderer->kernel,
		3, sizeof(cl_mem), &renderer->data_device.sample_store);
	renderer->error += clSetKernelArg(renderer->kernel,
		4, sizeof(cl_mem), &renderer->data_device.settings);
	renderer->error += clSetKernelArg(renderer->kernel,
		5, sizeof(cl_mem), &renderer->data_device.rng_state);
	ASSERT(renderer->error == 0)
}
