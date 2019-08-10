#ifndef CL_RENDERER_H
# define CL_RENDERER_H

# include "rt_float.h"
# include "rt_cl_compilation.h"

# include "assert.h"
# include "gui_image.h"
# include "scene.h"
# include "camera.h"
# include "ray.h"

# include <stdlib.h>
# include <time.h>

typedef struct 			s_cl_settings
{
	int					sample_count;
	int					sample_limit;
	int 				sample_depth;
	int					russian_depth;
	int					srgb;
	int					light_pb;
	int 				light_explicit;
}						t_cl_settings;

typedef struct 			s_cl_program
{
	cl_program 			program;
	char 				*buffer;
	u_long 				capacity;
	u_long				length;
	int 				error;
}						t_cl_program;

typedef struct 			s_cl_data_size
{
	u_long				camera;
	u_long				scene;
	u_long 				image;
	u_long 				settings;
	u_long 				sample_store;
	u_long				rng_state;
}						t_cl_data_size;

typedef	struct 			s_cl_data_host
{
	t_camera			*camera;
	t_scene				*scene;
	t_color				*image;
	t_cl_settings		settings;
	u_long				*rng_state;
}						t_cl_data_host;

typedef	struct 			s_cl_data_device
{
	cl_mem				camera;
	cl_mem				scene;
	cl_mem				image;
	cl_mem 				settings;
	cl_mem				sample_store;
	cl_mem 				rng_state;
}						t_cl_data_device;

typedef struct 			s_cl_flags
{
	int					update_camera;
	int 				update_scene;
	int					update_settings;
}						t_cl_flags;

typedef struct 			s_cl_renderer
{
	int 				error;
	t_gui_image			*image;
	t_cl_data_size		data_size;
	t_cl_data_host		data_host;
	t_cl_data_device	data_device;
	cl_device_id 		device_id;
	cl_context 			context;
	t_cl_program		program;
	cl_kernel 			kernel;
	cl_command_queue 	queue;
	u_long 				queue_length;
	t_cl_flags			flags;
}						t_cl_renderer;

t_cl_renderer			*cl_renderer_new(t_gui_image *image);
void					cl_renderer_delete(t_cl_renderer **renderer);

void					cl_renderer_log(t_cl_renderer *renderer);

void 					cl_renderer_init_data(t_cl_renderer *renderer);
void					cl_renderer_init_device(t_cl_renderer *renderer);
void					cl_renderer_init_context(t_cl_renderer *renderer);

void					cl_renderer_create_program(t_cl_renderer *renderer);
void					cl_renderer_create_queue(t_cl_renderer *renderer);
void					cl_renderer_create_kernel(t_cl_renderer *renderer);

void					cl_renderer_set_arguments(t_cl_renderer *renderer);

typedef enum 			e_cl_update
{
	update_camera,
	update_scene,
	update_settings

}						t_cl_update;

void					cl_renderer_update
						(t_cl_renderer *renderer, t_cl_update update);
void 					cl_renderer_camera_move
						(t_cl_renderer *renderer, t_camera_direction direction);

void					cl_renderer_render(t_cl_renderer *renderer);

#endif
