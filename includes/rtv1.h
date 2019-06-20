#ifndef RTV1_H
#define RTV1_H

#define WIN_W 1280
#define WIN_H 720

#include "SDL2/SDL.h"
#include "libsdl.h"
#include "libft.h"
#include <fcntl.h>
#include <limits.h>
#include <float.h>
#include <math.h>
//#include "libmath.h"
# define DROUND(d)	ABS(d) < 0.00001 ? 0 : (d)
//#define float double

typedef struct s_vertex t_vertex;
typedef struct s_sector t_sector;
typedef struct s_object t_object;
typedef struct s_coord t_coord;
typedef	struct 	s_vec3 t_vec3;
typedef	struct 	s_vec4 t_vec4;

typedef	struct s_point3
{
	float x;
	float y;
	float z;
} t_point3;

struct 	s_vec3
{
	float x;
	float y;
	float z;
	float w;
};

struct 	s_vec4
{
	float x;
	float y;
	float z;
	float w;
};

typedef	struct s_normal3
{
	float x;
	float y;
	float z;
} t_normal3;

typedef struct 	s_mat3
{
	double matrix[3][3];
} t_mat3;

typedef struct 	s_mat4
{
	double matrix[4][4];
} t_mat4;

typedef struct s_p2d
{
	float x;
	float y;
} t_p2d;

typedef struct s_quaternion
{
	float s; //scalar
	t_vec3 v;
} t_quaternion;

typedef struct s_ray
{
	t_vec3 orig;
	t_vec3 dir;
} t_ray;

typedef struct Material {
	t_vec3 diffuse_color;
	t_vec3 albendo;
	float specular_exponent;
	float refractive_index;
} t_material;

typedef struct s_light {
	t_vec3 position;
	float intensity;
} t_light;

typedef struct s_lights {
	t_light *lights;
	//t_vector light;
	int number;
} t_lights;

typedef struct		s_triangle
{
	t_vec3		a;
	t_vec3		b;
	t_vec3		c;
	t_material material;
} t_triangle;
typedef  double		(* t_f_intersect)(void *figure, t_vec3 *orig, t_vec3 *dir, float *t0); // cheats

struct s_object
{
	void *object;
	t_f_intersect intersect;
}; 

typedef  double		(* t_f_intersect)(void *figure, t_vec3 *orig, t_vec3 *dir, float *t0); // cheats
typedef struct s_sphere
{
	t_vec3 center;
	t_material material;
	float radius;
	t_vec3 v;
	double			angle;
	t_vec3		tip;
	t_f_intersect intersect;
} t_sphere;


typedef	struct s_cylinder
{
	t_vec3	center;
	t_material material;
	float	radius;
	int		min;
	int		max;
}				t_cylinder;

typedef	struct		s_cone
{
	// t_vec3		tip;
	// t_vec3		direction;
	// double			angle;
	// t_material material;
	t_vec3 center;
	t_material material;
	float radius;
	t_vec3 v;
	double			angle;
	t_vec3		tip;
}					t_cone;


struct s_vertex
{
	t_vec3 position;
	float U, V;
};

typedef struct s_coord
{
	t_vertex original;
	t_vertex rotated;
	char processed;
} t_coord;

typedef struct s_polygon
{
	t_vertex **vertices;
	int nvertices;
	//Texture
	t_sector *sector;
	//Plane
} t_polygon;

typedef struct s_plane
{
	t_vec3 point;
	t_normal3 normal;
	t_material material;
} t_plane;

// struct s_object
// {
// 	t_polygon *polygons;
// 	t_object *childs;
// 	//matrix matrix
// };

struct s_sector
{
	t_polygon *polygons;
};

typedef  struct s_world
{
	t_sector *sectors;
} t_world;

typedef struct s_game
{
	t_object *figures;
	int n_figures;
	t_sdl *sdl;
	t_surface *image;
	t_list *verties;
	t_lights elum;
	t_sphere *spheres;
	t_cone *cones;
	t_cylinder *cylinders;
	int n_spheres;
	int n_cones;
	int n_cylinders;
	int wsad[8];
	t_vec3 origin;
	double closest;

} t_game;

void	configure_sphere(char *map_name, t_sphere *sphere);
// inline t_vec3 ft_vec3_create(float x, float y, float z);
// inline t_vec3	ft_vec3_sum(t_vec3 a, t_vec3 b);
// inline  t_vec3	ft_vec3_substract(t_vec3 a, t_vec3 b);
// inline  float ft_vec3_dot_multiply(t_vec3 a, t_vec3 b);
// inline t_vec3 ft_vec3_scalar_multiply(t_vec3 a, float b);
// inline t_vec3 ft_vec3_cross_multiply(t_vec3 a, t_vec3 b);
// inline  float ft_vec3_norm(t_vec3 vect);
// inline  t_vec3 ft_vec3_normalize(t_vec3 vect);
// inline float ft_vec3_projection(t_vec3 a, t_vec3 b);
// inline void ft_vec3_print(t_vec3 a);

// extern inline t_vec3 ft_vec3_create(float x, float y, float z);
// extern inline t_vec3	ft_vec3_sum(t_vec3 a, t_vec3 b);
//  extern inline t_vec3	ft_vec3_substract(t_vec3 a, t_vec3 b);
//  extern inline float ft_vec3_dot_multiply(t_vec3 a, t_vec3 b);
//  extern inline t_vec3 ft_vec3_scalar_multiply(t_vec3 a, float b);
// extern inline t_vec3 ft_vec3_cross_multiply(t_vec3 a, t_vec3 b);
//  extern inline float ft_vec3_norm(t_vec3 vect);
//  extern inline t_vec3 ft_vec3_normalize(t_vec3 vect);
//  extern inline float ft_vec3_projection(t_vec3 a, t_vec3 b);
// extern inline void ft_vec3_print(t_vec3 a);


//point
t_point3 ft_point3_sum(t_point3 a, t_point3 b);
t_point3 ft_point3_substract(t_point3 a, t_point3 b);
t_point3 ft_point3_substract_vec3(t_point3 a, t_vec3 b);
double ft_point3_substract_sum_2(t_point3 a, t_vec3 b);
double ft_point3_dist(t_point3 a, t_vec3 b);
t_point3 ft_point3_scalar_multiply(t_point3 a, double b);

	t_vec3 ft_vec3_create(float x, float y, float z);
	t_vec3	ft_vec3_sum(t_vec3 a, t_vec3 b);
	t_vec3	ft_vec3_substract(t_vec3 a, t_vec3 b);
	float ft_vec3_dot_multiply(t_vec3 a, t_vec3 b);
	t_vec3 ft_vec3_scalar_multiply(t_vec3 a, float b);
	t_vec3 ft_vec3_cross_multiply(t_vec3 a, t_vec3 b);
	float ft_vec3_norm(t_vec3 vect);
	t_vec3 ft_vec3_normalize(t_vec3 vect);
	float ft_vec3_projection(t_vec3 a, t_vec3 b);
	void ft_vec3_print(t_vec3 a);
	t_vec3 ft_vec3_neg(t_vec3 v);
	t_vec3	ft_vec3_multiply_matrix(t_vec3 v, t_mat4 m);
	double	ft_vec3_angle(t_vec3 a, t_vec3 b);
	double			ft_vec3_length(t_vec3 v1);

t_quaternion t_quaternion_sum(t_quaternion a, t_quaternion b);
t_quaternion t_quaternion_substract(t_quaternion a, t_quaternion b);
float ft_quaternion_norm(t_quaternion q);
float ft_degree_to_rad(float degree);
t_quaternion ft_quaternion_normalize(t_quaternion q);
t_quaternion ft_quaternion_covert_to_unit_norm(t_quaternion q);
t_quaternion ft_quaternion_conjugate(t_quaternion q);
t_quaternion ft_quaternion_inverse(t_quaternion q);
t_quaternion ft_quaternion_multiply(t_quaternion a, t_quaternion b);
t_quaternion ft_quaternion_multiply2(t_quaternion a, t_quaternion b);
t_quaternion ft_quaternion_local_rotation(t_vec3 axis, float angle);

//mat
t_mat4	ft_mat4_identity_matrix(void);
t_vec3 ft_mat3_multiply_vec3(t_mat3 matrix, t_vec3 vector);
t_mat4	ft_mat4_multiply_mat4(t_mat4 a, t_mat4 b);
t_mat4	ft_mat4_scalar_multiply(t_mat4 m, double n);
t_mat4	ft_mat4_sum_mat4(t_mat4 a, t_mat4 b);
t_mat4	ft_mat4_translation_matrix(t_vec3 v);
t_mat4	ft_mat4_scale_matrix(double a, double b, double c);
t_point3 ft_mat3_multiply_point3(t_mat3 matrix, t_point3 point);
t_vec3 ft_mat3_multiply_vec3(t_mat3 matrix, t_vec3 vector);
t_mat4	ft_mat4_rotation_matrix(t_vec3 axis, double alpha);
void ft_mat4_print(t_mat4 mat);
//rot
t_vec3	ft_vec3_rotate_quaterion(float angle, t_vec3 vector, t_vec3 axis);
t_vec3	ft_vec3_rotate_quaterion2(float angle, t_vec3 vector, t_vec3 axis);
t_vec3 ft_vec3_project_test1(t_vec3 p);
t_vec3 ft_vec3_rotate_test1(t_vec3 p, t_vec3 angle);
t_vec3 ft_vec3_project_test2(t_vec3 p);
t_vec3 ft_vec3_rotate_test2(t_vec3 p, t_vec3 angle);
t_mat4 ft_mat4_transpose(t_mat4 mat);
t_mat4 ft_look_at(t_vec3 eye, t_vec3 up);
//normals
extern inline t_normal3 ft_normal3_neg(t_normal3 v);
extern inline t_normal3 ft_normal3_scalar_multiply(t_normal3 a, float b);
extern inline t_normal3	ft_normal3_sum(t_normal3 a, t_normal3 b);
 float ft_normal3_dot_multiply_vec3(t_normal3 a, t_vec3 b);
inline t_normal3 ft_normal3_scalar_multiply(t_normal3 a, float b);

//intersect
int ray_intersect(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0);
double		ray_intersect_sphere(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0);
double		ray_intersect_cylinder(t_cone *cylinder, t_vec3 *orig, t_vec3 *dir, float *t0);
double		ray_intersect_cone(t_sphere *cone, t_vec3 *orig, t_vec3 *dir, float *t0);
double		ray_intersect_sphere_book(void *sphere, t_vec3 *orig, t_vec3 *dir, float *t0);
double				sphere_intersection3(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0);
double				cylinder_intersection(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0);
double				cone_intersection(t_cone *cone, t_vec3 *orig, t_vec3 *dir, float *t0);
double				plane_intersection(t_ray ray, t_triangle triangle, float *t0);
double				plane_intersection2(t_ray ray, t_plane plane, float *t0);
double		ray_intersect_cone_book(t_cone *sphere, t_vec3 *orig, t_vec3 *dir, float *t0);
double		cone_intersection1(void *vcone, t_vec3 *orig, t_vec3 *dir, float *t0);
double		cylinder_intersection1(void *cylinder, t_vec3 *orig, t_vec3 *dir, float *t0);
#endif