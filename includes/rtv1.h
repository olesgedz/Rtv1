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
typedef	struct 	s_p3d t_p3d;


struct 	s_p3d
{
	float x;
	float y;
	float z;
};

typedef struct Material {
	t_p3d diffuse_color;
} t_material;

typedef struct s_light {
	t_p3d position;
	float intensity;
} t_light;

typedef struct s_lights {
	t_light *lights;
	int number;
} t_lights;

typedef struct s_sphere
{
	t_p3d center;
	t_material material;
	float radius;
} t_sphere;


struct s_vertex
{
	t_p3d position;
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

#endif