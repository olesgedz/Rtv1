/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:49:06 by lminta            #+#    #+#             */
/*   Updated: 2019/11/22 21:12:27 by srobert-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H
# define WIN_W 1920
# define WIN_H 1080
# define SAMPLES 5
# define CL_SILENCE_DEPRECATION
# include <sys/types.h>
# include "SDL2/SDL.h"
# include "cl_error.h"
# include "SDL_image.h"
# include "SDL_mixer.h"
# include "libft.h"
# include <dirent.h>
# include "libsdl.h"
# include "libvect.h"
# include <fcntl.h>
# include <limits.h>
# include <float.h>
# include <math.h>
# include <time.h>
# include "libcl.h"
# include "../cJSON/cJSON.h"
# ifdef __APPLE__
#  include <OpenCL/opencl.h>
# else
#  include <CL/cl.h>
# endif
# include "gui.h"
# ifndef DEVICE
#  define DEVICE CL_DEVICE_TYPE_DEFAULT
# endif


// # define LOOPA_POOPA
# ifdef LOOPA_POOPA
#  define SDL_BUTTON_LEFT 3
#  define SDL_BUTTON_RIGHT 1
# endif

# define TICKS_PER_FRAME	47

// # define BMASK 0x000000ff
// # define GMASK 0x0000ff00
// # define RMASK 0x00ff0000
// # define AMASK 0xff000000

typedef enum			e_figure
{
	SPHERE,
	CYLINDER,
	CONE,
	PLANE,
	TRIANGLE,
	DISK,
	TORUS
}						t_type;

typedef struct			s_txture
{
	cl_int				width;
	cl_int				height;
	cl_int				texture[CL_DEVICE_IMAGE2D_MAX_HEIGHT][CL_DEVICE_IMAGE2D_MAX_WIDTH];
}						t_txture;

typedef struct			s_object
{
	t_type				type;
	cl_float			radius;
	cl_float			tor_radius;
	cl_float3			position;
	cl_float3			color;
	cl_float3			emission;
	cl_float3			v;
	cl_float			metalness;
	cl_int				texture;
	cl_int				normal;
	cl_float3			vertices[3];
	cl_int				is_visible;
	cl_float2			shift;
	cl_float3			basis[3];
	cl_float2			prolapse;
	cl_int				id;
	cl_float			transparency;
	cl_float			refraction;
}						t_obj;

typedef struct			s_cam
{
	cl_float3			position;
	cl_float3			direction;
	cl_float3			normal;
	cl_float			fov;
	cl_float3			border_x;
	cl_float3			border_y;
	cl_int				cartoon;
	cl_int				sepia;
	cl_float			motion_blur;
	cl_float			ambience;
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
	cl_uint				num_platforms;
	cl_int				err;
	cl_ulong			*random;
	char				*kernel_source;
	cl_float3			*vec_temp;
	t_obj				*objects;
	cl_mem				cl_cpu_spheres;
	cl_mem				cl_buffer_out;
	cl_mem				cl_cpu_vectemp;
	cl_mem				cl_cpu_camera;
	cl_mem				cl_cpu_random;
	t_cam				*camera;
	int					samples;
}						t_gpu;

typedef struct			s_mouse_pos
{
	int					x;
	int					y;
	int					g;
	int					lmb;
	int					rmb;
	int					mm;
}						t_mouse_pos;
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
	int					space;
	int					r;
	Sint32				xrel;
	Sint32				yrel;
	int					show_gui;
}						t_keys;

typedef struct			s_game
{
	char				*av;
	SDL_Event			ev;
	t_sdl				sdl;
	size_t				obj_quantity;
	int					cam_quantity;
	t_gpu				gpu;
	t_txture			*textures;
	int					textures_num;
	char				**texture_list;
	char				**normal_list;
	int					normals_num;
	t_txture			*normals;
	t_cl_info			*cl_info;
	t_cl_krl			*kernels;
	int					cam_num;
	int					flag;
	int					quit;
	t_keys				keys;
	t_mouse_pos			mouse;
	cl_int				global_tex_id;
	SDL_Surface			*blured;
	cl_float3			*vertices_list;
	int					vertices_num;
}						t_game;

typedef struct	s_filter
{
	float	ambiance;
	int		cartoon;
	int		sepia;
	float	motion_blur;

}				t_filter;

typedef struct			s_json
{
    cJSON				*position;
    cJSON				*color;
    cJSON				*emition;
    cJSON				*reflection;
    cJSON				*translucency;
    cJSON				*texture;
    cJSON				*radius;
	cJSON				*tor_radius;
    cJSON				*v;
    cJSON				*x;
    cJSON				*y;
    cJSON				*z;
    cJSON				*a;
    cJSON				*b;
    cJSON				*c;
	cJSON				*fov;
    cJSON				*shift;
    cJSON				*x_basis;
    cJSON				*y_basis;
    cJSON				*z_basis;
    cJSON				*prolapse;
    cJSON				*type;
    cJSON				*normal;
	cJSON				*composed_pos;
	cJSON				*composed_v;
	cJSON				*cartoon;
	cJSON				*sepia;
	cJSON				*motion_blur;
	cJSON				*ambience;
	cJSON				*global_texture;
	cJSON				*transparency;
	cJSON				*refraction;
	cJSON				*name;
	cJSON				*size;
}             			t_json;


typedef struct		s_gui
{
	t_game			*game;
	t_sdl			sdl;
	SDL_Event		ev;
	int				quit;
	KW_RenderDriver	*driver;
	KW_Surface		*set;
	KW_GUI			*gui;
	t_edit_win		ed_w;
	t_scene_select	s_s;
	t_object_select	o_s;
	t_gui_bar		g_b;
	t_obj_type		o_t;
	t_change_obj	c_o;
	char			*av;
	int				flag;
	int				main_screen;
	int				over_gui;
	float			fps;
}					t_gui;

int						bind_data(t_gpu *gpu, t_game *game);
void					release_gpu(t_gpu *gpu);
void					ft_run_gpu(t_gpu *gpu);
cl_float3				create_cfloat3 (float x, float y, float z);
cl_float3				cl_scalar_mul(cl_float3 vector, double scalar);
cl_float3				cl_add(cl_float3 v1, cl_float3 v2);
void					get_texture(char *name, t_txture *texture, char *path);
void					read_scene(char *argv, t_game *game);
t_cam					*add_cam(cl_float3 position,\
cl_float3 direction, cl_float3 normal);
cl_float3				mult_cfloat3(cl_float3 one, float f);
cl_float3				sum_cfloat3(cl_float3 one, cl_float3 two);
cl_float3				rotate(cl_float3 axis, cl_float3 vector, float angle);
cl_float3				cross(cl_float3 one, cl_float3 two);
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
void					main_render(t_game *game, t_gui *gui);
void					free_opencl(t_game *game);
void					terminate(char *s);
void					feel_free(char **str);
void					ft_object_push(t_game *game, t_obj *object);
void					ft_cam_push(t_game *game, t_cam *cam);
void					ft_texture_push(t_game *game, char ***mass, char *texture_name);
void					ft_normal_push(t_game *game, char ***mass, char *normal_name);
void					main_screen(t_gui *gui, t_game *game);
void					obj_select(t_gui *gui, t_obj *objs, int num);
void					pos_check(t_game *game, t_gui *gui);
void					opencl_init(t_game *game);
void					check_file(t_game *game);
cl_float2				create_cfloat2 (float x, float y);
cl_float3				parse_vec3(cJSON *vec);
cl_float2				parse_vec2(cJSON *vec);
void					main_screen(t_gui *gui, t_game *game);
void					semples_to_line(t_game *game, t_gui *gui);
void					info_button(t_game *game, t_gui *gui);
void					show_hide(t_game *game, t_gui *gui);
void					mouse_down(t_game *game, t_gui *gui);
void					mouse_up(t_game *game, t_gui *gui);
void					gui_bar(t_game *game, t_gui *gui);
void					buttons(t_game *game, t_gui *gui);
cl_float2				parse_vec2(cJSON *vec);
char					*start_gui(t_game *game, t_gui *gui);
void					loopa(t_game *game, t_gui *gui);
void					screen_present(t_game *game, t_gui *gui);
void					ft_render(t_game *game, t_gui *gui);
void					play_stop_music(char *name);
void					check_object(const cJSON *object, t_game *game,
cJSON *comp_pos, cJSON *comp_v, int id);
int 					compare_in_texture_dict(t_game *game, char *texture_name);
int						compare_in_normal_dict(t_game *game, char *normal_name);
void					mouse_motion(t_game *game, t_gui *gui);
void					free_list(t_game *game);
void					add_obj(t_game *game, t_gui *gui);
void					obj_type(t_game *game, t_gui *gui);
void					change_plane(/*t_game *game,*/ t_gui *gui, t_obj *obj);
void					change_sphere(/*t_game *game, */t_gui *gui, t_obj *obj);
void					change_cylin(/*t_game *game, */t_gui *gui, t_obj *obj);
void					change_cone(/*t_game *game, */t_gui *gui, t_obj *obj);
void					change_trian(/*t_game *game, */t_gui *gui, t_obj *obj);
void 					obj_if(t_gui *gui, t_obj *obj);
char					*fill_name_mass(t_obj *obj, int num);
void					obj_same(t_gui *gui, t_obj *obj);
void					visibility_name(KW_Widget *widget, t_obj *obj);
KW_Widget				*f_e(t_gui *gui, double db, KW_Rect *rect);
void					color_emission(t_gui *gui, t_obj *obj, int *i);
float					vec_len(cl_float3 vec);
void					obj_click(KW_Widget *widget, int b);
void					print_error_gui(const char *message, const char
*error_message);
void					scene_select(t_gui *gui, int i,
KW_Widget *const *wid_arr);
void					start_screen(t_gui *gui);
void					init_kiwi(t_gui *gui);
void					quit_kiwi(t_gui *gui);
t_gui					*g_gui(t_gui *gui, int flag);
SDL_Texture				*load_picture(t_gui *gui, const char *filename);
void					quit_kiwi_main(t_gui *gui);
void					main_screen_free(t_gui *gui);
void					over(KW_Widget *widget, int b);
void					leave(KW_Widget *widget, int b);
void					visibility(KW_Widget *widget, int b);
void					radius(t_gui *gui, t_obj *obj, int *i);
void 					obj3d_parse(const cJSON *object, t_game *game, t_json *parse);
cl_float3				triangle_norm(cl_float3 *vertices);
#endif
