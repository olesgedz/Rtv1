# ifndef RTV1_H
# define RTV1_H

# define WIN_W 1920
# define WIN_H 1080
# define SAMPLES 5

# define CL_SILENCE_DEPRECATION
# include <sys/types.h>
# include "SDL2/SDL.h"
# include "SDL_image.h"
# include "libft.h"
# include "libmath.h"
# include "libsdl.h"
# include "libvect.h"
# include <fcntl.h>
# include <limits.h>
# include <float.h>
# include <math.h>
# include "cl_error.h"
# include "libcl.h"
# ifdef __APPLE__
# include <OpenCL/opencl.h>
# else
# include <Cl/cl.h>
# endif

# include "gui.h"

# ifndef DEVICE
# define DEVICE CL_DEVICE_TYPE_DEFAULT
# endif
# define RMASK 0x000000ff
# define GMASK 0x0000ff00
# define BMASK 0x00ff0000
# define AMASK 0xff000000
# define DROUND(d)	ABS(d) < 0.00001 ? 0 : (d)

typedef enum			e_figure
{
	SPHERE,
	CYLINDER,
	CONE,
	PLANE,
	TRIANGLE
}						t_type;

typedef struct			s_txture
{
	cl_int				width;
	cl_int				height;
	cl_int				texture[4096][2048];
}						t_txture;

typedef struct			s_object
{
	float				radius;
	cl_float3			position;
	cl_float3			color;
	cl_float3			emission;
	cl_float3			v;
	t_type				type;
	cl_float			refraction;
	cl_float			reflection;
	cl_float			plane_d;
	cl_int				texture;
	cl_float3			vertices[3];
	cl_int				is_visible;
}						t_obj;

typedef struct			s_ray
{
	t_vec3 				orig;
	t_vec3 				dir;
	t_vec3 				hit;
	double 				t;
} 						t_ray;


typedef struct			s_cam
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

typedef struct			s_gpu
{
    cl_device_id		device_id;
    cl_context			context;
    cl_command_queue	commands;
    cl_program			program;
    cl_kernel			kernel;
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


typedef struct			s_keys
{
	int					q;
	int					w;
	int					e;
	int					a;
	int					s;
	int					d;
	int					z;
	int					x;
	int					lmb;
	int					mm;
	int					space;
	Sint32				xrel;
	Sint32				yrel;

}						t_keys;

typedef struct			s_game
{
	char 				*av;
	SDL_Event			ev;
	t_sdl 				sdl;
	t_surface 			*image;
	t_list				*verties;
	int 				n_spheres;
	int 				n_cones;
	int 				n_cylinders;
	size_t 				obj_quantity;
	int					cam_quantity;
	t_vec3 				origin;
	t_gpu 				gpu;
	int 				init_render;
	t_txture			*textures;
	int					textures_num;
	t_cl_info 			*cl_info;
	t_cl_krl 			*kernels;
	int 				*gpuOutput;
	int					cam_num;
	int					flag;
	int					quit;
	t_keys				keys;
} 						t_game;

int						bind_data(t_gpu *gpu, t_game *game);
void 					release_gpu(t_gpu *gpu);
void 					ft_run_gpu(t_gpu *gpu);
int						opencl_init(t_gpu *gpu, t_game *game);
cl_float3				create_cfloat3 (float x, float y, float z);
cl_float3				cl_scalar_mul(cl_float3 vector, double scalar);
cl_float3				cl_add(cl_float3 v1, cl_float3 v2);
void					get_texture(char *name, t_txture *texture);
void 					read_scene(char *argv, t_game *game);
t_cam 					*add_cam(cl_float3 position, cl_float3 direction, cl_float3 normal);
cl_float3				mult_cfloat3(cl_float3 one, float f);
cl_float3				sum_cfloat3(cl_float3 one, cl_float3 two);
cl_float3				rotate(cl_float3 axis, cl_float3 vector, float angle);
cl_float3   			cross(cl_float3 one, cl_float3 two);
cl_float3				vector_diff(cl_float3 one, cl_float3 two);
cl_float3				normalize(cl_float3 vector);
void					reconfigure_camera(t_cam *camera);
void					rotate_vertical(t_cam *camera, float angle);
void					rotate_horizontal(t_cam *camera, float angle);
int						ft_input_keys(t_game *game);
void					key_check(t_game *game);
void					camera_reposition(t_game *game, t_gui *gui);
void					set_const(t_game *game, t_gui *gui);
void					opencl(t_game *game, char *argv);
cl_ulong				*get_random(cl_ulong *random);
void					poopa(t_game *game, t_gui *gui);
void					free_shit(t_game *game);
void					terminate(char *s);
void					feel_free(char **str);
void					ft_object_push(t_game *game, t_obj *object);
void					ft_cam_push(t_game *game, t_cam *cam);
void					parse_plane(char **data, t_game *game);
void					parse_sphere(char **data, t_game *game);
void					parse_cam(char **data, t_game *game);
void					parse_cone(char **data, t_game *game);
void					parse_cylinder(char **data, t_game *game);
void					parse_triangle(char **data, t_game *game);

void					main_screen(t_gui *gui, t_game *game);
void					obj_select(t_gui *gui, t_obj *objs, int num);

#endif
