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

typedef struct s_quaternion
{
	float s; //scalar
	t_vec3 v;
} t_quaternion;

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

#endif