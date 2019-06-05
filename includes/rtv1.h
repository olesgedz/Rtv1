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
//#include "libmath.h"
# define DROUND(d)	ABS(d) < 0.00001 ? 0 : (d)


typedef struct s_vertex t_vertex;
typedef struct s_sector t_sector;
typedef struct s_object t_object;
typedef struct s_coord t_coord;
typedef	struct 	s_vec3 t_vec3;

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
};

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

// typedef s_object
// {
// 	t_vec3 pos;
// 	t_vec3 v;
// 	t_material material;
// 	float radius;
// } t_object;

typedef struct s_sphere
{
	t_vec3 center;
	t_material material;
	float radius;
	t_vec3 v;
} t_sphere;

typedef	struct		s_cone
{
	t_vec3		tip;
	t_vec3		direction;
	double			angle;
	t_material material;
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

struct s_object
{
	t_polygon *polygons;
	t_object *childs;
	//matrix matrix
};

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
	t_sdl *sdl;
	t_surface *image;
	t_list *verties;
	t_lights elum;
	t_sphere *spheres;
	int n_spheres;
	int wsad[8];
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

t_vec3	ft_vec3_rotate_quaterion(float angle, t_vec3 vector, t_vec3 axis);
t_vec3	ft_vec3_rotate_quaterion2(float angle, t_vec3 vector, t_vec3 axis);
t_vec3 ft_vec3_project_test1(t_vec3 p);
t_vec3 ft_vec3_rotate_test1(t_vec3 p, t_vec3 angle);
t_vec3 ft_vec3_project_test2(t_vec3 p);
t_vec3 ft_vec3_rotate_test2(t_vec3 p, t_vec3 angle);


//intersect
int ray_intersect(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0);
double		ray_intersect_sphere(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0);
double		ray_intersect_cylinder(t_sphere *cylinder, t_vec3 *orig, t_vec3 *dir, float *t0);
double		ray_intersect_cylinder(t_sphere *cylinder, t_vec3 *orig, t_vec3 *dir, float *t0);
double		ray_intersect_cone(t_sphere *cone, t_vec3 *orig, t_vec3 *dir, float *t0);
double		ray_intersect_sphere_book(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0);
t_vec3 ft_mat3_multiply_vec(t_mat3 matrix, t_vec3 vector);
#endif