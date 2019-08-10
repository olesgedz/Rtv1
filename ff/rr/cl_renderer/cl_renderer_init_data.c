#include "cl_renderer.h"

static void			cl_renderer_data_size_init(t_cl_renderer *renderer)
{
	renderer->data_size.camera = sizeof(t_camera);
	renderer->data_size.scene = sizeof(t_scene);
	renderer->data_size.image =
			sizeof(t_color) * renderer->image->width * renderer->image->height;
	renderer->data_size.sample_store = sizeof(RT_F4_API)
		 * renderer->image->width * renderer->image->height;
	renderer->data_size.settings = sizeof(t_cl_settings);
	renderer->data_size.rng_state =
		sizeof(u_long) * renderer->image->width * renderer->image->height;
}

static void			cl_renderer_data_host_init(t_cl_renderer *renderer)
{
	int 			i;

	renderer->data_host.camera =
			camera_new(&renderer->image->width, &renderer->image->height);
	renderer->data_host.scene = scene_new();
	renderer->data_host.image = renderer->image->color_buffer;
	renderer->data_host.settings.sample_count = 0;
	renderer->data_host.settings.sample_limit = CL_SAMPLES;
	renderer->data_host.settings.sample_depth = CL_PATH_DEPTH;
	renderer->data_host.settings.russian_depth = CL_RUSSIAN_DEPTH;
	renderer->data_host.settings.russian_depth = CL_SRGB;
	renderer->data_host.settings.light_pb = CL_LIGHT_PB;
	renderer->data_host.settings.light_explicit = CL_LIGHT_EXPLICIT;
	i = 0;
	renderer->data_host.rng_state = malloc(renderer->data_size.rng_state);
	srand(21);
	while (i < renderer->image->width * renderer->image->height)
		renderer->data_host.rng_state[i++] = rand();
}

static void			cl_renderer_data_device_init(t_cl_renderer *renderer)
{
	renderer->data_device.camera = clCreateBuffer(renderer->context,
		CL_MEM_READ_ONLY, renderer->data_size.camera, NULL, &renderer->error);
	ASSERT(renderer->error == 0)
	renderer->data_device.scene = clCreateBuffer(renderer->context,
		CL_MEM_READ_ONLY, renderer->data_size.scene, NULL, &renderer->error);
	ASSERT(renderer->error == 0)
	renderer->data_device.image = clCreateBuffer(renderer->context,
		CL_MEM_WRITE_ONLY, renderer->data_size.image, NULL, &renderer->error);
	ASSERT(renderer->error == 0)
	renderer->data_device.settings = clCreateBuffer(renderer->context,
		CL_MEM_READ_ONLY, renderer->data_size.settings, NULL, &renderer->error);
	ASSERT(renderer->error == 0)
	renderer->data_device.sample_store = clCreateBuffer(renderer->context,
		CL_MEM_WRITE_ONLY, renderer->data_size.sample_store,
		NULL, &renderer->error);
	ASSERT(renderer->error == 0)
	renderer->data_device.rng_state = clCreateBuffer(renderer->context,
		CL_MEM_READ_WRITE, renderer->data_size.rng_state,
		NULL, &renderer->error);
	ASSERT(renderer->error == 0)
	renderer->error = clEnqueueWriteBuffer(
		renderer->queue, renderer->data_device.rng_state,
		CL_TRUE, 0, renderer->data_size.rng_state,
		renderer->data_host.rng_state, 0, NULL, NULL);
	ASSERT(renderer->error == 0)
}

void 				cl_renderer_init_data(t_cl_renderer *renderer)
{
	cl_renderer_data_size_init(renderer);
	cl_renderer_data_host_init(renderer);
	cl_renderer_data_device_init(renderer);
}