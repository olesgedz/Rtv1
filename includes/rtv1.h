#ifndef RTV1_H
#define RTV1_H

#define WIN_W 700
#define WIN_H 700
#define CL_SILENCE_DEPRECATION
#include <sys/types.h>
#include "SDL2/SDL.h"
#include "libsdl.h"
#include "libft.h"
#include "libmath.h"
#include <fcntl.h>
#include <limits.h>
#include <float.h>
#include <math.h>
#include "cl_error.h"
#include "libcl.h"
#ifdef __APPLE__
#include <OpenCL/opencl.h>
#else
#include <Cl/cl.h>
#endif

#include "gui.h"

#ifndef DEVICE
#define DEVICE CL_DEVICE_TYPE_DEFAULT
#endif
//#include "libmath.h"
# define DROUND(d)	ABS(d) < 0.00001 ? 0 : (d)
//#define float double
typedef enum e_figure
{
	SPHERE,
	CYLINDER,
	CONE,
	PLANE,
	TRIANGLE
} 						t_type;

typedef struct s_txture
{
	cl_int		width;
	cl_int		height;
	cl_int		texture[1920][1080];
}				t_txture;

typedef struct Object{
	float radius;
	cl_float3 position;
	cl_float3 color;
	cl_float3 emission;
	cl_float3 v;
	t_type type;
	cl_float refraction;
	cl_float reflection;
	cl_float plane_d;
	cl_int		texture;
	cl_float3	vertices[3];
} t_obj;

typedef struct s_ray
{
	t_vec3 				orig;
	t_vec3 				dir;
	t_vec3 				hit;
	double 				t;
} 						t_ray;


typedef struct 			s_cam
{
	cl_float3			position;
	cl_float3			direction;
	cl_float3			normal;
	cl_float			fov;
	cl_float3			border_x;
	cl_float3			border_y;
}						t_cam;

typedef enum			e_camera_direction
{
	left,
	right,
	up,
	down,
	forward,
	backward
}						t_camera_direction;

typedef struct s_gpu
{
    cl_device_id		device_id;     // compute device id
    cl_context			context;       // compute context
    cl_command_queue	commands;      // compute command queue
    cl_program			program;       // compute program
    cl_kernel			kernel;       // compute kernel
	cl_uint				numPlatforms;
	cl_int				err;
	cl_ulong			*random;
	char				*kernel_source;
	int 				*cpuOutput;
	cl_float3			*vec_temp;
	t_obj				*objects;
	cl_mem				cl_bufferOut;
	cl_mem				cl_cpuSpheres;
	cl_mem				cl_cpu_vectemp;
	cl_mem				cl_cpu_camera;
	cl_mem 				cl_cpu_random;
	t_cam	 			*camera;
	int 				samples;
}						t_gpu;

typedef struct			s_game
{
	char 				*av;
	SDL_Event			ev;
	t_gui				gui;
	t_sdl 				sdl;
	t_surface 			*image;
	t_list				*verties;
	int 				n_spheres;
	int 				n_cones;
	int 				n_cylinders;
	size_t 				obj_quantity;
	int					cam_quantity;
	int 				wsad[20];
	t_vec3 				origin;
	t_gpu 				*gpu;
	int 				init_render;
	t_txture			*textures;
	int					textures_num;
	t_cl_info 			*cl_info;
	t_cl_krl 			*kernels;
	int 				*gpuOutput;
	int					cam_num;
	int					mouse;
	int					quit;
} 						t_game;

int						bind_data(t_gpu *gpu, t_game *game);
void 					release_gpu(t_gpu *gpu);
void 					ft_run_gpu(t_gpu *gpu);

int						opencl_init(t_gpu *gpu, t_game *game);
cl_float3				create_cfloat3 (float x, float y, float z);

cl_float3				cl_scalar_mul(cl_float3 vector, double scalar);

cl_float3				cl_add(cl_float3 v1, cl_float3 v2);
// t_camera				*camera_new(int width, int height);
// void 					camera_move
// 						(t_camera *camera,
// 						t_camera_direction direction,
// 						float length);
void					get_texture(char *name, t_txture *texture);

t_obj					*add_plane(cl_float3 position, cl_float3 color, cl_float3 emition, cl_int texture, cl_float reflection, cl_float3 v);
t_obj					*add_sphere(cl_float3 position, float radius, cl_float3 color, cl_float3 emition, cl_int texture, cl_float reflection);
t_obj 					*add_cylinder(cl_float3 position, float radius, cl_float3 color, cl_float3 emition, cl_int texture, cl_float reflection, cl_float3 v);
t_obj 					*add_cone(cl_float3 position, float radius, cl_float3 color, cl_float3 emition, cl_int texture, cl_float reflection, cl_float3 v);
void 					read_scene(char *argv, t_game *game);
t_cam *add_cam(cl_float3 position, cl_float3 direction, cl_float3 normal);
cl_float3				mult_cfloat3(cl_float3 one, float f);
cl_float3				sum_cfloat3(cl_float3 one, cl_float3 two);
cl_float3				rotate(cl_float3 axis, cl_float3 vector, float angle);
cl_float3   			cross(cl_float3 one, cl_float3 two);
cl_float3				vector_diff(cl_float3 one, cl_float3 two);
cl_float3				normalize(cl_float3 vector);
void					reconfigure_camera(t_cam *camera);
void					rotate_vertical(t_cam *camera, float angle);
void					rotate_horizontal(t_cam *camera, float angle);
t_obj *add_triangle(cl_float3 *vertices, cl_float3 color, cl_float3 emition, cl_int texture, cl_float reflection);
int						ft_input_keys(void *game1, SDL_Event *ev);

void					start_screen(t_game *game);
void					init_kiwi(t_game *game);
void					quit_kiwi(t_game *game);
void					loopa(t_game *game);
t_game					*g_game(t_game *game, int flag);

#endif
