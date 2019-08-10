#include "cl_renderer.h"

static void 		cl_renderer_delete_cl(t_cl_renderer *renderer)
{
	clReleaseDevice(renderer->device_id);
	clReleaseContext(renderer->context);
	clReleaseProgram(renderer->program.program);
	clReleaseKernel(renderer->kernel);
	clReleaseCommandQueue(renderer->queue);
}

void				cl_renderer_delete(t_cl_renderer **renderer)
{
	camera_delete(&(*renderer)->data_host.camera);
	scene_delete(&(*renderer)->data_host.scene);
	cl_renderer_delete_cl(*renderer);
	free(*renderer);
	*renderer = NULL;
}