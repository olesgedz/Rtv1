/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/06/04 21:08:15 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "libmath.h"
#include <time.h>
/*
* ! We can't use global variables 
*/

# define DROUND(d)	ABS(d) < 0.00001 ? 0 : (d)

t_game game;
float xa, ya, za;

/*
*	Funtion: handles presses mouse/keyboard
* 	Return: value, doesnt change any parameters
*
*	- can handle multiple presses at once
*	- that goes into libsdl void ft_input(void *main, int (*f)(void *main, SDL_Event *ev))
*/
int		ft_input_keys(void *sdl, SDL_Event *ev)
{
	switch (ev->type)
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				switch (ev->key.keysym.sym)
				{
					case SDLK_LCTRL:
					case SDLK_RCTRL:
					case SDLK_ESCAPE: ft_exit(NULL); break;
					case 'w': game.wsad[0] = ev->type==SDL_KEYDOWN; break;
					case 's': game.wsad[1] = ev->type==SDL_KEYDOWN; break;
					case 'a': game.wsad[2] = ev->type==SDL_KEYDOWN; break;
					case 'd': game.wsad[3] = ev->type==SDL_KEYDOWN; break;
					case 'q': game.wsad[4] = ev->type==SDL_KEYDOWN; break;
					case 'e': game.wsad[5] = ev->type==SDL_KEYDOWN; break;
					case 'z': game.wsad[6] = ev->type==SDL_KEYDOWN; break;
					case 'x': game.wsad[7] = ev->type==SDL_KEYDOWN; break;
					case 'p': ya+=0.2; break;
					case ';': ya-=0.2; break;
					case 'l': xa+=0.2; break;
					case '\'': xa-=0.2; break;
					case '.': za+=0.2; break;
					case '/': za-=0.2; break;
					default: break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:  
				break;
			case SDL_QUIT: ft_exit(NULL);
		}
	return (1);
}


/*
*	Function: creates 3d point from coordinates
*	Parameters: x y z coodinates of the 3d point as float 
*	Return: malloced t_vec3, no parameters change
*
* ? probably suppose to be t_vector3d or smth
*/

inline t_vec3 ft_vec3_create(float x, float y, float z)
{
	t_vec3 new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}
/*
*	Fucntion: sum of two vectors
*	Parameters: two vectors
*	Return: sum of two vectors, no parammeters change
*/


inline t_vec3	ft_vec3_sum(t_vec3 a, t_vec3 b)
{
	t_vec3 new;

	new.x = (a.x + b.x);
	new.y = (a.y + b.y);
	new.z = (a.z + b.z);
	return (new);
}

/*
*	Fucntion: substact two vectors
*	Parameters: two vectors
*	Return: difference of two vectors, no parammeters change
*/


inline t_vec3	ft_vec3_substract(t_vec3 a, t_vec3 b)
{
	t_vec3 new;

	new.x = (a.x - b.x);
	new.y = (a.y - b.y);
	new.z = (a.z - b.z);
	return (new);
}

/*
*	Fucntion: prints a 3d point
*	Parameters: 3d point, no parameters change
*	Return: none
* ! printf delete it
*/

inline void ft_vec3_print(t_vec3 a)
{
	printf("x:%f y:%f z:%f\n", a.x, a.y, a.z);
}

/*
*	Fucntion: vector multiplication, dot product
*	Parameters: two vectors no parameters change 
*	Return: scalar float result of multiplication,
*/
inline float ft_vec3_dot_multiply(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
*	Fucntion: vector multiplication by scalar
*	Parameters: two vectors no parameters change 
*	Return: t_vec3 vector result of multiplication,
*/

inline t_vec3 ft_vec3_scalar_multiply(t_vec3 a, float b)
{
	return ((t_vec3){a.x * b, a.y * b, a.z * b});
}
/*
*	Fucntion: vector multiplication by vector
*	Parameters: two vectors no parameters change 
*	Return: t_vec3 vector result of multiplication,
*/

inline t_vec3 ft_vec3_cross_multiply(t_vec3 a, t_vec3 b)
{
	t_vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

/*
*	Fucntion: scalar value of vector
*	Parameters: vector, no parameters change 
*	Return: (float) scalar value of a vector
*/

inline float ft_vec3_norm(t_vec3 vect)
{
	return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
}

/*
*	Fucntion: changes scalar value of a vector
*	Parameters: vector (changes), needed length
*	Return: normalized vector
*/

inline t_vec3 ft_vec3_normalize(t_vec3 vect)
{
	float norm = ft_vec3_norm(vect);
	vect.x = vect.x / norm;
	vect.y = vect.y / norm;
	vect.z = vect.z / norm;
	return (vect);
}


/*
*	Fucntion: projection of vector a on vector b
*	Parameters: two vectors no parameters change 
*	Return: float,
*/

inline float ft_vec3_projection(t_vec3 a, t_vec3 b)
{
	return (ft_vec3_dot_multiply(b, a) /  ft_vec3_norm(b));
}

/*
*	Fucntion:
*	Parameters:
*	Return:
*/

t_vec3	reflect(t_vec3 I, t_vec3 n)
{
	t_vec3 temp;
	
	temp = ft_vec3_scalar_multiply(n, 2.f * ft_vec3_dot_multiply(I, n));
	return ft_vec3_substract(I, temp);
}

double		get_t(double a, double b, double d, float *t0)
{
	double	t1;
	double	t2;

	t1 = (-b - sqrt(d)) / (2 * a);
	t2 = (-b + sqrt(d)) / (2 * a);
	if ((t1 <= t2 && t1 >= 0) || (t1 >= 0 && t2 < 0))
		return (*t0 = t1);
	if ((t2 <= t1 && t2 >= 0) || (t2 >= 0 && t1 < 0))
		return (*t0 = t2);
	return (-1);
}


/*
*	Fucntion: checks if a ray hits the sphere
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/
int ray_intersect(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	t_vec3 L = ft_vec3_substract(sphere->center, *orig);
	// printf("%f %f %f, dir: %f %f %f\n", L.x, L.y, L.z, dir->x, dir->y, dir->z);
	float tca = ft_vec3_dot_multiply(L, *dir);
	//printf("tca %f\n", tca);
	float d2 = ft_vec3_dot_multiply(L, L) - tca * tca;
	//printf("d2 %f %f \n", d2, sphere->radius * sphere->radius);
	if (d2 > sphere->radius * sphere->radius)
		return FALSE;
	float thc = sqrtf(sphere->radius * sphere->radius - d2);
	*t0	= tca - thc;
	float t1 = tca + thc;
	if (*t0 < 0)
		*t0 = t1;
	if (*t0 < 0)
		return FALSE;
	return TRUE;
}

double		ray_intersect_sphere(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	float	a;
	float	b;
	float	c;
	float	d;

	a = ft_vec3_dot_multiply(*dir, *dir);
	b = 2 * ft_vec3_dot_multiply(*dir, ft_vec3_substract(*orig, sphere->center));
	c = ft_vec3_dot_multiply(ft_vec3_substract(*orig, sphere->center),
		ft_vec3_substract(*orig, sphere->center)) - sphere->radius * sphere->radius;
	d = b * b - 4 * a * c;
	return (d < 0 ? -1 : get_t(a, b, d, t0));
}


double		ray_intersect_cylinder(t_sphere *cylinder, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	t_vec3	x;
	double	a;
	double	b;
	double	c;
	double	d;
	
	x = ft_vec3_substract(*orig, cylinder->center);
	a = ft_vec3_dot_multiply(*dir, cylinder->v);
	a = ft_vec3_dot_multiply(*dir, *dir) - a * a;
	b = 2 * (ft_vec3_dot_multiply(*dir, x) - ft_vec3_dot_multiply(*dir, cylinder->v)
		* ft_vec3_dot_multiply(x, cylinder->v));
	c = ft_vec3_dot_multiply(x, cylinder->v);
	c = ft_vec3_dot_multiply(x, x) - c * c - cylinder->radius * cylinder->radius;
	d = b * b - 4 * a * c;
	return (d = d < 0 ? -1 : get_t(a, b, d, t0));
}



double		ray_intersect_cone(t_sphere *cone, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	t_vec3	x;
	double	a;
	double	b;
	double	c;
	double	d;

	x = ft_vec3_substract(*orig, cone->center);
	a = ft_vec3_dot_multiply(*dir, cone->v);
	a = ft_vec3_dot_multiply(*dir, *dir) - (1 + cone->radius * cone->radius) * a * a;
	b =  2 * (ft_vec3_dot_multiply(*dir, x) - (1 + cone->radius * cone->radius)
		* ft_vec3_dot_multiply(*dir, cone->v) * ft_vec3_dot_multiply(x, cone->v));
	c = ft_vec3_dot_multiply(x, cone->v);
	c = ft_vec3_dot_multiply(x, x) - (1 + cone->radius * cone->radius) * c * c;
	d = b * b - 4 * a * c;
	d = DROUND(d);
	return (d = d < 0 ? -1 : get_t(a, b, d, t0));
}

double		ray_intersect_sphere_book(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
{
	double t;
	t_vec3 temp = ft_vec3_substract(*orig, sphere->center);
	double a = ft_vec3_dot_multiply(*dir, *dir);
	double b = ft_vec3_dot_multiply(ft_vec3_scalar_multiply(temp, 2), *dir);
	double c = ft_vec3_dot_multiply(temp, temp) - sphere->radius * sphere->radius;
	double disc = b * b - 4.0 * a * c;
	if(disc < 0)
		return ( 0);
	else
	{
			double e = sqrt(disc);
			double denom = 2 * a;
			t = (-b - e) / denom;
			if (t > 0)
			{
				*t0 = t;
				return (1);
			}
			t = (-b + e)/denom;

			if (t > 0)
			{
				*t0 = t;
				return (1);
			}

	}

		return 0;
	

}
/*
*	Fucntion: checks if a ray hits the sphere
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/
// int ray_intersect(t_sphere *sphere, t_vec3 *orig, t_vec3 *dir, float *t0)
// {
// 	t_vec3 L = ft_vec3_substract(sphere->center, *orig);
// 	// printf("%f %f %f, dir: %f %f %f\n", L.x, L.y, L.z, dir->x, dir->y, dir->z);
// 	float tca = ft_vec3_dot_multiply(L, *dir);
// 	//printf("tca %f\n", tca);
// 	float d2 = ft_vec3_dot_multiply(L, L) - tca * tca;
// 	//printf("d2 %f %f \n", d2, sphere->radius * sphere->radius);
// 	if (d2 > sphere->radius * sphere->radius)
// 		return FALSE;
// 	float thc = sqrtf(sphere->radius * sphere->radius - d2);
// 	*t0	= tca - thc;
// 	float t1 = tca + thc;
// 	if (*t0 < 0)
// 		*t0 = t1;
// 	if (*t0 < 0)
// 		return FALSE;
// 	return TRUE;
// }
double				quandratic_solve(double k1, double k2, double k3)
{
	double			diskr;
	double			t1;
	double			t2;
	double			tmp;

	diskr = k2 * k2 - 4 * k1 * k3;
	if (diskr < 0)
		return (0);
	t1 = (-k2 + sqrt(diskr)) / (2 * k1);
	t2 = (-k2 - sqrt(diskr)) / (2 * k1);
	if (t1 > t2)
	{
		tmp = t1;
		t1 = t2;
		t2 = tmp;
	}
	if (t1 < 0)
		t1 = t2;
	if (t1 < 0)
		return (-1.);
	return (t1);
}

/*
*	Fucntion: checks all objects on the scene
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/

int scene_intersect(t_vec3 *orig, t_vec3 *dir, t_sphere *spheres, t_vec3 *hit, t_vec3 *N, t_material *material)
{
	float spheres_dist = FLT_MAX; // WHY
	size_t	i = -1;
	// ft_vec3_print(&spheres[0].center);
	// ft_vec3_print(&spheres[1].center);
	//ft_exit(NULL);
	
	while (++i < game.n_spheres)
	{
		float dist_i;

		if (ray_intersect_sphere_book(&spheres[i], orig, dir, &dist_i) && dist_i < spheres_dist)
		{
			spheres_dist = dist_i;
			t_vec3 temp = ft_vec3_scalar_multiply(*dir, dist_i);
			*hit = ft_vec3_sum(*orig, temp);
			temp = ft_vec3_substract(*hit, spheres[i].center);
			*N = ft_vec3_normalize(temp);
			*material = spheres[i].material;
		}
	}
	float checkerboard_dist = FLT_MAX;
    if (fabs(dir->y) > 1e-3)
	{
        float d = -(orig->y + 4) / dir->y; // the checkerboard plane has equation y = -4
        t_vec3 board = ft_vec3_sum(*orig, ft_vec3_scalar_multiply(*dir, d));
        if (d > 0 && fabs(board.x) < 10 && board.z < -10 && board.z > -30 && d < spheres_dist)
		{
            checkerboard_dist = d;
            *hit = board;
            *N = ft_vec3_create(0, 1, 0);
            material->diffuse_color = ((int)(0.5*(hit->x+1000)) + (int)(0.5*(hit->z)) & 1) ? ft_vec3_create(0.1, 0.1, 0.1) : ft_vec3_create(0.8, 0.7, 0.6);
        }
    }
	return spheres_dist < checkerboard_dist ? spheres_dist < 1000 : checkerboard_dist < 1000;
	//return spheres_dist < 1000;
}

/*
*	Fucntion: casts ray for that pixel
*	Parameters: stuff, sphere, ray
*	Return: returns matiral(color) for that pixel
*/

t_vec3 cast_ray(t_vec3 *orig, t_vec3 *dir, t_sphere *spheres)
{
	t_vec3 point;
	t_vec3 N;
	t_material material;
	int	i;

	// ft_vec3_print(&spheres[0].center);
	// ft_vec3_print(&spheres[1].center);
	float sphere_dist = FLT_MAX;
	//if (!ray_intersect(&spheres[0], orig, dir, &sphere_dist))
	if(!scene_intersect(orig, dir, spheres, &point, &N, &material))
		return ft_vec3_create(0.4, 0.4, 0.4); // background color
	float diffuse_light_intensity = 0;
	float specular_light_intensity = 0;
	i = -1;
	while (++i < game.elum.number)
	{
		t_vec3 light_dir      = ft_vec3_normalize(ft_vec3_substract(game.elum.lights[i].position, point));
		float light_distance = ft_vec3_norm(ft_vec3_substract(game.elum.lights[i].position, point));
		t_vec3 shadow_orig = ((ft_vec3_dot_multiply(light_dir, N) < 0) ? ft_vec3_substract(point, ft_vec3_scalar_multiply(N, 1e-3)) : ft_vec3_sum(point, ft_vec3_scalar_multiply(N, 1e-3)));
		t_vec3 shadow_pt, shadow_N;
		t_material temp_material;
		if (scene_intersect(&shadow_orig, &light_dir, spheres, &shadow_pt, &shadow_N, &temp_material) && ft_vec3_norm(ft_vec3_substract(shadow_pt, shadow_orig)) < light_distance)
			continue ;
		diffuse_light_intensity  += game.elum.lights[i].intensity * max(0, ft_vec3_dot_multiply(light_dir, N));
		specular_light_intensity += powf(max(0.f, ft_vec3_dot_multiply(ft_vec3_scalar_multiply(reflect(ft_vec3_scalar_multiply(light_dir, -1), N), -1),*dir)),\
		 	material.specular_exponent)*game.elum.lights[i].intensity;
	}
	return ft_vec3_sum(ft_vec3_scalar_multiply(material.diffuse_color, diffuse_light_intensity * material.albendo.x), \
	 	ft_vec3_scalar_multiply((t_vec3){1,1,1}, specular_light_intensity *  material.albendo.y));					//ft_vec3_scalar_multiply(&material.diffuse_color, diffuse_light_intensity);
}



	const float fov      = M_PI/2.; // field of vision




/*
*	Fucntion: render all pixels on the surface
*	Parameters: game, sdl
*	Return: none
*/
void 	ft_render(t_game* game, t_sphere *sphere)
{
	int		i;
	int		j;
	int width = game->sdl->surface->width;
	int height = game->sdl->surface->height;
	j = -1;
	while (++j < height)
	{
		i = -1;
		while (++i < width)
		{
			float x = (2 * (i + 0.5) / (float)width  - 1) * tan(fov / 2.) * width / (float)height;
			float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
			t_vec3 dir = ft_vec3_normalize((t_vec3){x, y, -1});
			t_vec3 orign = ft_vec3_create(0, 0, 0);
			t_vec3 temp = cast_ray(&orign, &dir, game->spheres);
			game->sdl->surface->data[i+j*width] = ft_rgb_to_hex(225 * max(0, min(1, temp.x)), 225 * max(0, min(1, temp.y)), 225 * max(0, min(1, temp.z)));
		}
	}
}


t_vec3 cube[8];


/*
*	Fucntion: Main loop
*		1. Clear the screen
*		2. Handle input
*		3. Render
*	!	4. surface_combine is redrawing only part of the screen, not used yet
*		5. Put surface to texture and then to on Screen
*			? don't use surfaces and use just textures for speed
*	Parameters: game, sdl
*	Return: none
*/


t_vec3 ft_vec3_project_test1(t_vec3 p)
{
	t_vec3 new;
	p.z+=300;
	new.x=(p.x*500)/p.z+320, new.y=(p.y*500)/p.z+240;
	return (new);
}

t_vec3 ft_vec3_rotate_test1(t_vec3 p, t_vec3 angle)
{
	float mat[3][3];            // Determine rotation matrix
	t_vec3 new;	
	float xdeg=angle.x*M_PI/180, ydeg=angle.y*M_PI/180, zdeg=angle.z*M_PI/180;
	float sx=(float)sin(xdeg), sy=(float)sin(ydeg), sz=(float)sin(zdeg);
	float cx=(float)cos(xdeg), cy=(float)cos(ydeg), cz=(float)cos(zdeg);
	mat[0][0]=cx*cz+sx*sy*sz, mat[1][0]=-cx*sz+cz*sx*sy, mat[2][0]=cy*sx;
	mat[0][1]=cy*sz, mat[1][1]=cy*cz, mat[2][1]=-sy;
	mat[0][2]=-cz*sx+cx*sy*sz, mat[1][2]=sx*sz+cx*cz*sy, mat[2][2]=cx*cy;
	new.x=p.x*mat[0][0]+p.y*mat[1][0]+p.z*mat[2][0];
	new.y=p.x*mat[0][1]+p.y*mat[1][1]+p.z*mat[2][1];
	new.z=p.x*mat[0][2]+p.y*mat[1][2]+p.z*mat[2][2];	
	return (new);
}


t_vec3 ft_vec3_project_test2(t_vec3 p)
{
	p.x *= 1;
	p.y *= 1;
	p.x += 300;
	p.y += 300;
	return (p);
}

t_vec3 ft_vec3_rotate_test2(t_vec3 p, t_vec3 angle)
{

	t_vec3	v;
	double		x;
	double		y;
	double		z;
	
	x = p.x;
	z = p.z;
	v.x = cos(angle.y) * x + sin(angle.y) * z;
	v.z = -sin(angle.y) * x + cos(angle.y) * z;
	y = p.y;
	z = v.z;
	v.y = cos(angle.x) * y - sin(angle.x) * z;
	v.z = sin(angle.x) * y + cos(angle.x) * z + 300;
	x = v.x;
	y = v.y;
	v.x = cos(angle.z) * x - sin(angle.z) * y;
	v.y = sin(angle.z) * x + cos(angle.z) * y;
	return (v);
}


// min X and max X for every horizontal line within the triangle
void ScanLine(long x1, long y1, long x2, long y2, long ContourX[][2])
{
  long sx, sy, dx1, dy1, dx2, dy2, x, y, m, n, k, cnt;

  sx = x2 - x1;
  sy = y2 - y1;

  if (sx > 0) dx1 = 1;
  else if (sx < 0) dx1 = -1;
  else dx1 = 0;

  if (sy > 0) dy1 = 1;
  else if (sy < 0) dy1 = -1;
  else dy1 = 0;

  m = ABS(sx);
  n = ABS(sy);
  dx2 = dx1;
  dy2 = 0;

  if (m < n)
  {
    m = ABS(sy);
    n = ABS(sx);
    dx2 = 0;
    dy2 = dy1;
  }

  x = x1; y = y1;
  cnt = m + 1;
  k = n / 2;

  while (cnt--)
  {
    if ((y >= 0) && (y < WIN_H))
    {
      if (x < ContourX[y][0]) ContourX[y][0] = x;
      if (x > ContourX[y][1]) ContourX[y][1] = x;
    }

    k += n;
    if (k < m)
    {
      x += dx2;
      y += dy2;
    }
    else
    {
      k -= m;
      x += dx1;
      y += dy1;
    }
  }
}


void DrawTriangle(t_surface *surface, t_point p0, t_point p1, t_point p2)
{
  int y;
  long ContourX[surface->height][2];
  for (y = 0; y < surface->height; y++)
  {
    ContourX[y][0] = LONG_MAX; // min X
    ContourX[y][1] = LONG_MIN; // max X
  }
	ScanLine(p0.x, p0.y, p1.x, p1.y, ContourX);
  	ScanLine(p1.x, p1.y, p2.x, p2.y, ContourX);
  	ScanLine(p2.x, p2.y, p0.x, p0.y, ContourX);
  for (y = 0; y < surface->height; y++)
  {
	  //printf("%ld >= %ld\n", ContourX[y][1], ContourX[y][0]);
    if (ContourX[y][1] >= ContourX[y][0])
    {
      long x = ContourX[y][0];
      long len = 1 + ContourX[y][1] - ContourX[y][0];

      // Can draw a horizontal line instead of individual pixels here
	 
      while (len--)
      {
        ft_put_pixel(surface, &(t_point){x++, y}, 0xff0000);
      }
    }
  }
}
void ft_cube(t_game *game)
{
	t_vec3 cube_r[8];
	for(int i = 0; i < 8; i++)
	{
		cube_r[i] = ft_vec3_project_test1(ft_vec3_rotate_quaterion(ya * 30,cube[i],(t_vec3){1,0,0}));//ft_vec3_rotate_test2(cube[i], (t_vec3){xa,ya,za})); 
	}
	for (int i = 0; i<4; i++)         // Actual drawing
	{
		// ft_plot_wline(game->sdl->surface, &(t_fpoint){cube_r[i].x, cube_r[i].y}, &(t_fpoint){cube_r[i+4].x, cube_r[i+4].y}, 0xFF0000);
		// ft_plot_wline(game->sdl->surface, &(t_fpoint){cube_r[i].x, cube_r[i].y}, &(t_fpoint){cube_r[(i+1)%4].x, cube_r[(i+1)%4].y}, 0xFF0000);
		// ft_plot_wline(game->sdl->surface, &(t_fpoint){cube_r[i + 4].x, cube_r[i + 4].y}, &(t_fpoint){cube_r[(i+1)%4 + 4].x, cube_r[(i+1)%4 + 4].y}, 0xFF0000);
		DrawTriangle(game->sdl->surface, (t_point){cube_r[i].x, cube_r[i].y}, (t_point){cube_r[i+4].x, cube_r[i+4].y}, (t_point){cube_r[(i+1)%4].x, cube_r[(i+1)%4].y});
		DrawTriangle(game->sdl->surface, (t_point){cube_r[i].x, cube_r[i].y}, (t_point){cube_r[i+4].x, cube_r[(i+1)%4 + 4].y}, (t_point){cube_r[(i+1)%4].x, cube_r[(i+1)%4].y});
	}
}
void ft_update(t_game *game)
{
	t_rectangle r = (t_rectangle){(t_point){0,0},(t_size){WIN_W, WIN_H}};
	t_sphere sphere = {(t_vec3){-3, 0, -16}, 2};
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	while(1)
	{
		
		// ((t_light *)game->elum.light.get(&game->elum.light, 0))->position = game->elum.lights[0].position; //  Because VECTORS!
		// game->spheres[2].center =  ((t_light *)game->elum.light.get(&game->elum.light, 0))->position;       //game->elum.lights[0].position;
		//printf("%f %f\n", ((t_light *)game->elum.light.get(&game->elum.light, 0))->position.x);
		//game->spheres[2].center = game->elum.lights[0].position;
		current_ticks = clock();
		ft_surface_clear(game->sdl->surface);
		ft_input(game->sdl, &ft_input_keys);
		game->wsad[0] ? game->elum.lights[0].position.z -= 1: 0;
		game->wsad[1] ? game->elum.lights[0].position.z += 1 : 0;
		game->wsad[2] ? game->elum.lights[0].position.x -= 1 : 0;
		game->wsad[3] ? game->elum.lights[0].position.x += 1 : 0;
		game->wsad[4] ? game->elum.lights[0].position.y += 1 : 0;
		game->wsad[5] ? game->elum.lights[0].position.y -= 1 : 0;
		game->wsad[6] ? game->elum.lights[0].intensity += 0.1 : 0;
		game->wsad[7] ? game->elum.lights[0].intensity -= 0.1 : 0;
		ft_render(game, &sphere);
		//ft_cube(game);
		//DrawTriangle(game->sdl->surface, (t_point){10,2}, (t_point){10,50}, (t_point){5,37});
		//ft_surface_combine(game->sdl->surface, game->image, &r);
		ft_surface_present(game->sdl, game->sdl->surface);
				 delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
    if(delta_ticks > 0)
        fps = CLOCKS_PER_SEC / delta_ticks;
			printf("fps :%lu\n", fps);
	 }
}

t_vec3 ft_mat3_multiply_vec(t_mat3 matrix, t_vec3 vector)
{
	t_vec3 new;

	new.x = matrix.matrix[0][0] * vector.x + matrix.matrix[0][1] * vector.y + matrix.matrix[0][2] * vector.z;
	new.y = matrix.matrix[1][0] * vector.x + matrix.matrix[1][1] * vector.y + matrix.matrix[1][2] * vector.z;
	new.z = matrix.matrix[2][0] * vector.x + matrix.matrix[2][1] * vector.y + matrix.matrix[2][2] * vector.z;
	return (new);
}
int	main(int argc, char **argv)
{

	t_mat3 a = (t_mat3){{{1,2,3}, {4,5,6}, {7,8,9}}};
	t_vec3 v = (t_vec3){1,1,1};
	v = ft_mat3_multiply_vec(a,v);
	ft_vec3_print(v);
	printf("move light source with wasdqe \nchange intensity with zx\n");
	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	t_material ivory = (t_material){(t_vec3){0.4, 0.4, 0.3}, (t_vec3){0.6, 0.3, 0}, 70};
	t_material red_rubber = (t_material){(t_vec3){0.3, 0.1, 0.1}, (t_vec3){0.3, 0.5, 0}, 10000};
	//printf("%f %f %f\n", bb.albendo.x, bb.albendo.y, bb.specular_exponent);
	game.elum.lights = ft_memalloc(sizeof(t_light) * 5);
	game.elum.lights[0] = (t_light){(t_vec3){7, 10, -16}, 1.5};
	game.elum.lights[1] = (t_light){(t_vec3){-20, 20, 20}, 1.5};
	game.elum.lights[2] = (t_light){(t_vec3){30, 50, -25}, 1.8};
	game.elum.lights[3] = (t_light){(t_vec3){30, 20, 30}, 1.7};
	//vector_init(&game.elum.light);
	//vector_add(&game.elum.light,  &(t_light){(t_vec3){7, 10, -16}, 1.5});
	game.elum.number = 4; // number of light sources
	game.n_spheres = 1;
	game.spheres = ft_memalloc(sizeof(t_sphere) * 6);
	game.spheres[0] = (t_sphere){(t_vec3){-3, 0, -16}, ivory, 5, (t_vec3){10, 0, 0}};
	game.spheres[1] = (t_sphere){(t_vec3){-1.0, -1.5, -12}, red_rubber, 2, 5};
	game.spheres[3] = (t_sphere){(t_vec3){1.5, -0.5, -18}, red_rubber, 3, 5};
	game.spheres[4] = (t_sphere){(t_vec3){7, 5, -18}, ivory, 4, 5};

	game.spheres[2] = (t_sphere){(t_vec3){-3.0, 0, -12}, red_rubber, 1, 5}; // this is a light source, move with wasdqe

	// ft_vec3_print(&game.spheres[0].center);
	// ft_vec3_print(&game.spheres[1].center);
	t_sphere sphere;
	
	for (int i=0; i<8; i++)     // Define the cube
	{
		cube[i].x=(float)(50-100*(((i+1)/2)%2));
		cube[i].y=(float)(50-100*((i/2)%2));
		cube[i].z=(float)(50-100*((i/4)%2));
	}


	configure_sphere(argv[1], &sphere);
	ft_init_window(game.sdl, WIN_W, WIN_H);
	ft_update(&game);
	ft_exit(NULL);
}