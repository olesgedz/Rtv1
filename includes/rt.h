/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 14:49:06 by lminta            #+#    #+#             */
/*   Updated: 2019/12/08 20:26:51 by srobert-         ###   ########.fr       */
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
# include "SDL_net.h"
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
# include "cJSON.h"
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
	TORUS,
	PARABOLOID
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
	cl_float3			composed_pos;
	cl_float3			composed_v;
	cl_int				is_negative;
}						t_obj;

typedef struct			s_cam
{
	cl_float3			position;
	cl_float3			direction;
	cl_float3			normal;
	cl_float			fov;
	cl_float3			border_x;
	cl_float3			border_y;
	cl_int				id;
	cl_int				cartoon;
	cl_int				sepia;
	cl_int				stereo;
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
	cl_float3			*vec_temp1;
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
	int					ed_box;
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
	int					gui_mod;
}						t_game;

typedef struct	s_filter
{
	float	ambiance;
	int		cartoon;
	int		sepia;
	int		stereo;
	float	motion_blur;

}				t_filter;

typedef struct			s_json
{
	cJSON				*json;
	const cJSON 		*object;
	const cJSON			*objects;
	const cJSON			*camera;
	const cJSON			*cameras;
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
	cJSON				*stereo;
	cJSON				*motion_blur;
	cJSON				*ambience;
	cJSON				*global_texture;
	cJSON				*transparency;
	cJSON				*refraction;
	cJSON				*name;
	cJSON				*size;
	cJSON				*negative;
}             			t_json;

typedef struct		s_gui
{
	KW_Widget		*destroy[MAX_OBJ];
	int				to_destroy;
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
	t_change_cam	c_c;
	t_camera_select	c_s;
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
cl_float3				parse_vec3(cJSON *vec, int flag);
cl_float2				parse_vec2(cJSON *vec);
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
void					visibility(KW_Widget *widget, int b);
void					radius(t_gui *gui, t_obj *obj, int *i);
void					direction(t_gui *gui, t_obj *obj, int *i);
void					vert(t_gui *gui, t_obj *obj, int *i);
void					basis(t_gui *gui, t_obj *obj, int *i);
void					shift(t_gui *gui, t_obj *obj, int *i);
void					text_normal(t_gui *gui, t_obj *obj, int *i);
void					position(t_gui *gui, t_obj *obj, int *i);
void					prolapse(t_gui *gui, t_obj *obj, int *i);
void					savebutton(t_gui *gui, t_obj *obj);
void					save_click(KW_Widget *widget, int b);
void					trian_parse(t_gui *gui, t_obj *obj);
void					sphere_parse(t_gui *gui, t_obj *obj);
void					cylin_parse(t_gui *gui, t_obj *obj);
void					cone_parse(t_gui *gui, t_obj *obj);
void					plane_parse(t_gui *gui, t_obj *obj);
void					parse_prolapse(t_gui *gui, t_obj *obj, int *i);
void					parse_position(t_gui *gui, t_obj *obj, int *i);
void					parse_direction(t_gui *gui, t_obj *obj, int *i);
void					parse_radius(t_gui *gui, t_obj *obj, int *i);
void					parse_color_emission(t_gui *gui, t_obj *obj, int *i);
void					parse_text_normal(t_gui *gui, t_obj *obj, int *i);
void					parse_bas(t_gui *gui, t_obj *obj, int *i);
void					parse_vert(t_gui *gui, t_obj *obj, int *i);
void					parse_shift(t_gui *gui, t_obj *obj, int *i);
void					norma_from_obj_select(t_gui *gui, KW_Widget *widget,
KW_Widget *wid);
void					click_create(KW_Widget *widget, int b);
void					create_triangle(t_game *game);
void					create_cylinder(t_game *game);
void					create_plane(t_game *game);
void					create_sphere(t_game *game);
void					create_cone(t_game *game);
void					check_gui_entrance(t_game *game, t_gui *gui,
int x, int y);
void					same_new(t_game *game, t_obj *obj, t_type type);
void					obj_click(KW_Widget *widget, int b);
void					in_cl(t_game *game);
void					del_obj(t_obj *obj, t_game *game);
void					delbutton(t_gui *gui, t_obj *obj);
void					del_click(KW_Widget *widget, int b);
void					destr(t_gui *gui, KW_Widget *widget);
void					cam_button(t_game *game, t_gui *gui);
void					cam_select(t_gui *gui, t_cam *cams, int num);
char					*cam_mass_name(t_game *game, t_cam *cam);
void					cam_rename(t_game *game, t_gui *gui, int num);
void					norma_from_cam_select(t_gui *gui, KW_Widget *widget,
KW_Widget *wid);
void					take_cam(KW_Widget *widget, int b);
void					cam_savebutton(t_gui *gui, t_cam *cam);
void					cam_delbutton(t_gui *gui, t_cam *cam);
void					change_cam(t_gui *gui, t_cam *cam);
void					cam_position(t_gui *gui, t_cam *cam, int *i);
KW_Widget				*f_c(t_gui *gui, double db, KW_Rect *rect);
void					cam_border(t_gui *gui, t_cam *cam, int *i);
void					cam_fov(t_gui *gui, t_cam *cam, int *i);
void					cam_amb_blur(t_gui *gui, t_cam *cam, int *i);
void					cam_eff(t_gui *gui, t_cam *cam, int *i);
void					sep_name(KW_Widget *widget, t_cam *cam);
void					cart_name(KW_Widget *widget, t_cam *cam);
void					cart(KW_Widget *widget, int b);
void					sep(KW_Widget *widget, int b);
void					cam_click(KW_Widget *widget, int b);
void					cam_free(t_gui *gui);
void					cam_screen(t_gui *gui, t_game *game);
void					pars_cam_box(t_gui *gui, t_cam *cam);
void					cam_save_click(KW_Widget *widget, int b);
void					del_cam(t_cam *cam, t_game *game);
void					add_cam_button(t_gui *gui);
void					ddd_name(KW_Widget *widget, t_cam *cam);
void					ddd(KW_Widget *widget, int b);
void					push_tex(t_game *game, char *res);
void 					obj3d_parse(const cJSON *object, t_game *game,
t_json *parse);
cl_float3				triangle_norm(cl_float3 *vertices);
void					push_normal(t_game *game, char *res);
void					check_ed_box_focus(t_game *game, t_gui *gui,
int x, int y);
void					tor_parse(t_gui *gui, t_obj *obj);
void					hyper_parse(t_gui *gui, t_obj *obj);
void					change_hyper(t_gui *gui, t_obj *obj);
void					create_tor(t_game *game);
void					create_hyper(t_game *game);
void					change_tor(t_gui *gui, t_obj *obj);
void					parse_new_basis(t_obj *obj);
void					gui_mod_but(t_game *game, t_gui *gui);
void					parse_refraction(t_gui *gui, t_obj *obj, int *i);
void					refraction(t_gui *gui, t_obj *obj, int *i);
void					dumper_butt(t_game *game, t_gui *gui);
char					*dumper(t_game *game);
void					dump_scene(t_game *game, FILE *fp);
void					basis_print(t_obj *obj, FILE *fp);
void					dump_obj(t_game *game, FILE *fp);
void					dump_cam(t_game *game, FILE *fp);
void					ss_free(t_gui *gui);
void					check_scene(t_json json, t_game *game);
void					read_scene(char *argv, t_game *game);
void					check_object(const cJSON *object, t_game *game, t_json parse, int id);
void					check_scene(t_json parse, t_game *game);
void					check_cam(t_json parse, t_game *game, t_filter *filter);
cl_float3				get_composed_pos(cJSON *composed_pos);
cl_float3				get_composed_v(cJSON *composed_v);
void					parse_necessary(const cJSON *object, t_obj *obj, t_json *parse);
void					parse_facing(const cJSON *object, t_obj *obj, t_json *parse, t_game *game);
void					parse_basis(const cJSON *object, t_obj *obj, t_json *parse);
void					parse_rest(const cJSON *object, t_obj *obj, t_json *parse);
void					parse_triangle_vert(const cJSON *object, t_obj *obj, t_json *parse);
void prepare_data(char ***data, char *line);
#endif
