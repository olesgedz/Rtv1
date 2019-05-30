/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/05/30 12:08:32 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
/*
* ! We can't use global variables 
*/

# define DROUND(d)	ABS(d) < 0.00001 ? 0 : (d)
t_game game;
float xa, ya, za;

int ft_point_compare(t_list *list, void *target)
{
	if ((((t_point *)list->content)->x == ((t_point *)target)->x) &&
		(((t_point *)list->content)->y == ((t_point *)target)->y))
		{
			printf("S:%d %d %d %d\n", ((t_point *)list->content)->x,((t_point *)target)->x,
			((t_point *)list->content)->y , ((t_point *)target)->y);
			return (1);
		}
	return (0);
}
void ft_lst_free(void *content, size_t size)
{
	ft_memdel((void **)content);
}
t_list		*ft_list_search(t_list *lst, void *target, int (*f)(t_list *, void *))
{
	while (lst != NULL)
	{
		if (f(lst, target))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void ft_put_vertex(t_game *game)
{
	
	ft_put_pixel(game->image, &(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, 0xFF0000);
	if (ft_list_search(game->verties, &(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, ft_point_compare))
	{
		printf("YIIIIS\n");
		//ft_lstdel(&game->verties, ft_lst_free);
	}
	ft_lstadd(&game->verties, ft_lstnew(&(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, sizeof(t_point)));
	printf("%d %d\n", ((t_point *)game->verties->content)->x, ((t_point *)game->verties->content)->y);
}

/*
* Drawing from doom/hadnling mouse
*/

void ft_mouse_pressed(t_game *game, SDL_Event *ev)
{
	game->sdl->mouse.pressed = 1;
	game->sdl->mouse.last_x = game->sdl->mouse.x;
	game->sdl->mouse.last_y = game->sdl->mouse.y;
	game->sdl->mouse.x = ev->button.x;
	game->sdl->mouse.y = ev->button.y;
	ft_put_vertex(game);
	if (game->sdl->mouse.last_x > 0)
		ft_plot_line(game->image, &(t_point){game->sdl->mouse.last_x, game->sdl->mouse.last_y},\
	 		&(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, 0x00FF00);
}

/*
*	End of Doom stuff
*/

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
			case SDL_MOUSEBUTTONDOWN:  ft_mouse_pressed(&game, ev);
				break;
			case SDL_QUIT: ft_exit(NULL);
		}
	return (1);
}

/*
*	Function: creates 3d point from coordinates
*	Parameters: x y z coodinates of the 3d point as float 
*	Return: malloced t_p3d, no parameters change
*
* ? probably suppose to be t_vector3d or smth
*/

t_p3d ft_p3d_create(float x, float y, float z)
{
	t_p3d new;

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


t_p3d	ft_p3d_sum(t_p3d a, t_p3d b)
{
	t_p3d new;

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


t_p3d	ft_p3d_substract(t_p3d a, t_p3d b)
{
	t_p3d new;

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

void ft_p3d_print(t_p3d a)
{
	printf("x:%f y:%f z:%f\n", a.x, a.y, a.z);
}

/*
*	Fucntion: vector multiplication, dot product
*	Parameters: two vectors no parameters change 
*	Return: scalar float result of multiplication,
*/
float ft_p3d_dot_multiply(t_p3d a, t_p3d b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

/*
*	Fucntion: vector multiplication by scalar
*	Parameters: two vectors no parameters change 
*	Return: t_p3d vector result of multiplication,
*/

t_p3d ft_p3d_scalar_multiply(t_p3d a, float b)
{
	return ((t_p3d){a.x * b, a.y * b, a.z * b});
}
/*
*	Fucntion: vector multiplication by vector
*	Parameters: two vectors no parameters change 
*	Return: t_p3d vector result of multiplication,
*/

t_p3d ft_p3d_cross_multiply(t_p3d a, t_p3d b)
{
	t_p3d result;

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

float ft_p3d_norm(t_p3d vect)
{
	return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
}

/*
*	Fucntion: changes scalar value of a vector
*	Parameters: vector (changes), needed length
*	Return: normalized vector
*/

t_p3d ft_p3d_normalize(t_p3d vect)
{
	float norm = ft_p3d_norm(vect);
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

float ft_p3d_projection(t_p3d a, t_p3d b)
{
	return (ft_p3d_dot_multiply(b, a) /  ft_p3d_norm(b));
}


/*
*	Fucntion:
*	Parameters:
*	Return:
*/

t_p3d	reflect(t_p3d I, t_p3d n)
{
	t_p3d temp;
	
	temp = ft_p3d_scalar_multiply(n, 2.f * ft_p3d_dot_multiply(I, n));
	return ft_p3d_substract(I, temp);
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

double		ray_intersect_sphere(t_sphere *sphere, t_p3d *orig, t_p3d *dir, float *t0)
{
	float	a;
	float	b;
	float	c;
	float	d;

	a = ft_p3d_dot_multiply(*dir, *dir);
	b = 2 * ft_p3d_dot_multiply(*dir, ft_p3d_substract(*orig, sphere->center));
	c = ft_p3d_dot_multiply(ft_p3d_substract(*orig, sphere->center),
		ft_p3d_substract(*orig, sphere->center)) - sphere->radius * sphere->radius;
	d = b * b - 4 * a * c;
	return (d < 0 ? -1 : get_t(a, b, d, t0));
}


double		ray_intersect_cylinder(t_sphere *cylinder, t_p3d *orig, t_p3d *dir, float *t0)
{
	t_p3d	x;
	double	a;
	double	b;
	double	c;
	double	d;
	
	x = ft_p3d_substract(*orig, cylinder->center);
	a = ft_p3d_dot_multiply(*dir, cylinder->v);
	a = ft_p3d_dot_multiply(*dir, *dir) - a * a;
	b = 2 * (ft_p3d_dot_multiply(*dir, x) - ft_p3d_dot_multiply(*dir, cylinder->v)
		* ft_p3d_dot_multiply(x, cylinder->v));
	c = ft_p3d_dot_multiply(x, cylinder->v);
	c = ft_p3d_dot_multiply(x, x) - c * c - cylinder->radius * cylinder->radius;
	d = b * b - 4 * a * c;
	return (d = d < 0 ? -1 : get_t(a, b, d, t0));
}



double		ray_intersect_cone(t_sphere *cone, t_p3d *orig, t_p3d *dir, float *t0)
{
	t_p3d	x;
	float	a;
	float	b;
	float	c;
	float	d;

	x = ft_p3d_substract(*orig, cone->center);
	a = ft_p3d_dot_multiply(*dir, cone->v);
	a = ft_p3d_dot_multiply(*dir, *dir) - (1 + cone->radius * cone->radius) * a * a;
	b =  1* (ft_p3d_dot_multiply(*dir, x) - (1 + cone->radius * cone->radius)
		* ft_p3d_dot_multiply(*dir, cone->v) * ft_p3d_dot_multiply(x, cone->v));
	c = ft_p3d_dot_multiply(x, cone->v);
	c = ft_p3d_dot_multiply(x, x) - (1 + cone->radius * cone->radius) * c * c;
	d = b * b - 4 * a * c;
	//d = DROUND(d);
	return (d = d < 0 ? -1 : get_t(a, b, d, t0));
}
/*
*	Fucntion: checks if a ray hits the sphere
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/
// int ray_intersect(t_sphere *sphere, t_p3d *orig, t_p3d *dir, float *t0)
// {
// 	t_p3d L = ft_p3d_substract(sphere->center, *orig);
// 	// printf("%f %f %f, dir: %f %f %f\n", L.x, L.y, L.z, dir->x, dir->y, dir->z);
// 	float tca = ft_p3d_dot_multiply(L, *dir);
// 	//printf("tca %f\n", tca);
// 	float d2 = ft_p3d_dot_multiply(L, L) - tca * tca;
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

/*
*	Fucntion: checks all objects on the scene
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/

int scene_intersect(t_p3d *orig, t_p3d *dir, t_sphere *spheres, t_p3d *hit, t_p3d *N, t_material *material)
{
	float spheres_dist = FLT_MAX; // WHY
	size_t	i = -1;
	// ft_p3d_print(&spheres[0].center);
	// ft_p3d_print(&spheres[1].center);
	//ft_exit(NULL);
	while (++i < game.n_spheres)
	{
		float dist_i;

		if (ray_intersect_sphere(&spheres[i], orig, dir, &dist_i) && dist_i < spheres_dist)
		{
			spheres_dist = dist_i;
			t_p3d temp = ft_p3d_scalar_multiply(*dir, dist_i);
			*hit = ft_p3d_sum(*orig, temp);
			temp = ft_p3d_substract(*hit, spheres[i].center);
			*N = ft_p3d_normalize(temp);
			*material = spheres[i].material;
		}
	}
	float checkerboard_dist = FLT_MAX;
    if (fabs(dir->y) > 1e-3)
	{
        float d = -(orig->y + 4) / dir->y; // the checkerboard plane has equation y = -4
        t_p3d board = ft_p3d_sum(*orig, ft_p3d_scalar_multiply(*dir, d));
        if (d > 0 && fabs(board.x) < 10 && board.z < -10 && board.z > -30 && d < spheres_dist)
		{
            checkerboard_dist = d;
            *hit = board;
            *N = ft_p3d_create(0, 1, 0);
            material->diffuse_color = ((int)(0.5*(hit->x+1000)) + (int)(0.5*(hit->z)) & 1) ? ft_p3d_create(0.1, 0.1, 0.1) : ft_p3d_create(0.8, 0.7, 0.6);
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

t_p3d cast_ray(t_p3d *orig, t_p3d *dir, t_sphere *spheres)
{
	t_p3d point;
	t_p3d N;
	t_material material;
	int	i;

	// ft_p3d_print(&spheres[0].center);
	// ft_p3d_print(&spheres[1].center);
	float sphere_dist = FLT_MAX;
	//if (!ray_intersect(&spheres[0], orig, dir, &sphere_dist))
	if(!scene_intersect(orig, dir, spheres, &point, &N, &material))
		return ft_p3d_create(0.4, 0.4, 0.4); // background color
	float diffuse_light_intensity = 0;
	float specular_light_intensity = 0;
	i = -1;
	while (++i < game.elum.number)
	{
		t_p3d light_dir      = ft_p3d_normalize(ft_p3d_substract(game.elum.lights[i].position, point));
		float light_distance = ft_p3d_norm(ft_p3d_substract(game.elum.lights[i].position, point));
		t_p3d shadow_orig = ((ft_p3d_dot_multiply(light_dir, N) < 0) ? ft_p3d_substract(point, ft_p3d_scalar_multiply(N, 1e-3)) : ft_p3d_sum(point, ft_p3d_scalar_multiply(N, 1e-3)));
		t_p3d shadow_pt, shadow_N;
		t_material temp_material;
		if (scene_intersect(&shadow_orig, &light_dir, spheres, &shadow_pt, &shadow_N, &temp_material) && ft_p3d_norm(ft_p3d_substract(shadow_pt, shadow_orig)) < light_distance)
			continue ;
		diffuse_light_intensity  += game.elum.lights[i].intensity * max(0, ft_p3d_dot_multiply(light_dir, N));
		specular_light_intensity += powf(max(0.f, ft_p3d_dot_multiply(ft_p3d_scalar_multiply(reflect(ft_p3d_scalar_multiply(light_dir, -1), N), -1),*dir)),\
		 	material.specular_exponent)*game.elum.lights[i].intensity;
	}
	return ft_p3d_sum(ft_p3d_scalar_multiply(material.diffuse_color, diffuse_light_intensity * material.albendo.x), \
	 	ft_p3d_scalar_multiply((t_p3d){1,1,1}, specular_light_intensity *  material.albendo.y));					//ft_p3d_scalar_multiply(&material.diffuse_color, diffuse_light_intensity);
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
			t_p3d dir = ft_p3d_normalize((t_p3d){x, y, -1});
			t_p3d orign = ft_p3d_create(0, 0, 0);
			t_p3d temp = cast_ray(&orign, &dir, game->spheres);
			game->sdl->surface->data[i+j*width] = ft_rgb_to_hex(225 * max(0, min(1, temp.x)), 225 * max(0, min(1, temp.y)), 225 * max(0, min(1, temp.z)));
		}
	}
}


t_p3d cube[8];


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


t_p3d ft_p3d_project_test1(t_p3d p)
{
	t_p3d new;
	p.z+=300;
	new.x=(p.x*500)/p.z+320, new.y=(p.y*500)/p.z+240;
	return (new);
}

t_p3d ft_p3d_rotate_test1(t_p3d p, t_p3d angle)
{
	float mat[3][3];            // Determine rotation matrix
	t_p3d new;	
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


t_p3d ft_p3d_project_test2(t_p3d p)
{
	p.x *= 1;
	p.y *= 1;
	p.x += 300;
	p.y += 300;
	return (p);
}

t_p3d ft_p3d_rotate_test2(t_p3d p, t_p3d angle)
{

	t_p3d	v;
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

t_quaternion t_quaternion_sum(t_quaternion a, t_quaternion b)
{
	t_quaternion new;

	new.s = a.s + b.s;
	new.v = ft_p3d_sum(a.v, b.v);
	return (new);
}

t_quaternion t_quaternion_substract(t_quaternion a, t_quaternion b)
{
	t_quaternion new;

	new.s = a.s - b.s;
	new.v = ft_p3d_substract(a.v, b.v);
	return (new);
}

float ft_quaternion_norm(t_quaternion q)
{

	float scalar = q.s * q.s;
	float imaginary = ft_p3d_dot_multiply(q.v, q.v);
	return (sqrt(scalar + imaginary));
}

float ft_degree_to_rad(float degree)
{
	return (degree * M_PI/180);
}

t_quaternion ft_quaternion_normalize(t_quaternion q)
{
	t_quaternion new;
	float norm;
    float norm_value;

	norm = ft_quaternion_norm(q);
	if (norm != 0)
	{
		norm_value = 1 / norm;
		new.s = q.s * norm_value;
		new.v = ft_p3d_scalar_multiply(q.v, norm_value);
	}
	return (new);
}

//Unit-Norm Quaternion (Special Form)
t_quaternion ft_quaternion_covert_to_unit_norm(t_quaternion q)
{
	t_quaternion new;
	float angle  = ft_degree_to_rad(q.s);

	new.v = ft_p3d_normalize(q.v);
	new.s = cosf(angle * 0.5);
	new.v = ft_p3d_scalar_multiply(q.v, sinf(angle * 0.5));
	return (new);
}

t_quaternion ft_quaternion_conjugate(t_quaternion q)
{
	float scalar=q.s;
	t_p3d imaginary = ft_p3d_scalar_multiply(q.v, -1);
	return ((t_quaternion){scalar, imaginary});
}

t_quaternion ft_quaternion_inverse(t_quaternion q)
{
	float abs = ft_quaternion_norm(q); 
	abs*=abs;
	abs=1/abs;
	t_quaternion conjugare_val = ft_quaternion_conjugate(q);

	float scalar = conjugare_val.s * abs;
	t_p3d imaginary = ft_p3d_scalar_multiply(conjugare_val.v, abs);

	return((t_quaternion){scalar, imaginary});

}

t_quaternion ft_quaternion_multiply(t_quaternion a, t_quaternion b)
{
	float scalar = a.s * b.s - ft_p3d_dot_multiply(a.v, b.v);

	t_p3d imaginary = ft_p3d_sum(ft_p3d_sum(ft_p3d_scalar_multiply(b.v, a.s), ft_p3d_scalar_multiply(a.v, b.s)), ft_p3d_cross_multiply(a.v, b.v)); 
	return ((t_quaternion){scalar, imaginary});
}
//https://www.cprogramming.com/tutorial/3d/quaternions.html
t_quaternion ft_quaternion_multiply2(t_quaternion a, t_quaternion b)
{
	t_quaternion new;
	new.s = (a.s * b.s - a.v.x * b.v.x  - a.v.y * b.v.y - a.v.z * b.v.z);
	new.v.x = (a.s * b.v.x + a.v.x * b.s + a.v.y * b.v.z - a.v.z * b.v.y);
	new.v.y = (a.s * b.v.y - a.v.x * b.v.z + a.v.y * b.s + a.v.z * b.v.x);
	new.v.z  = (a.s * b.v.z + a.v.x * b.v.y - a.v.y * b.v.x + a.v.z * b.s);
	return (new);
}

t_quaternion ft_quaternion_local_rotation(t_p3d axis, float angle)
{
	t_quaternion local_rotation;
	angle = angle * M_PI / 180.0;
	local_rotation.s = cosf(angle/2);
	local_rotation.v.x = axis.x * sinf(angle/2);
	local_rotation.v.y = axis.y * sinf(angle/2);
	local_rotation.v.z = axis.z * sinf(angle/2);
	return (local_rotation);
}

t_p3d	ft_p3d_rotate_quaterion(float angle, t_p3d vector, t_p3d axis)
{
	 //convert our vector to a pure quaternion
    t_quaternion p = (t_quaternion){0,vector};
	//create the real quaternion
	t_quaternion q = (t_quaternion){angle, ft_p3d_normalize(axis)};
	 //convert quaternion to unit norm quaternion
	q = ft_quaternion_covert_to_unit_norm(q);

	t_quaternion q_invesrse = ft_quaternion_inverse(q);

	t_quaternion rotated = ft_quaternion_multiply2(ft_quaternion_multiply(q,p), q_invesrse);
	return (rotated.v);
}

t_p3d	ft_p3d_rotate_quaterion2(float angle, t_p3d vector, t_p3d axis)
{
	t_p3d new;
	t_quaternion local_rotation = ft_quaternion_local_rotation(axis, angle);
	t_quaternion total = (t_quaternion){1, {0, 0, 0}};
	total  = ft_quaternion_multiply2(local_rotation, total);
	new.x = (1 - 2 * pow(total.v.y, 2) - 2.0 * pow(total.v.z, 2)) * vector.x
	+ (2 * total.v.x * total.v.y - 2 * total.s * total.v.z) * vector.y
	+ (2 * total.v.x * total.v.z + 2 * total.s * total.v.y) * vector.z;
	new.y = (2 * total.v.x * total.v.y + 2 * total.s * total.v.z) * vector.x
	+ (1 - 2 * pow(total.v.x, 2) - 2 * pow(total.v.z, 2)) * vector.y
	+ (2 * total.v.y * total.v.z - 2 * total.s * total.v.x) * vector.z;
	new.z = (2 * total.v.x * total.v.z - 2 * total.s * total.v.y) * vector.x
	+ (2 * total.v.y * total.v.z + 2 * total.s * total.v.x) * vector.y
	+ (1 - 2 * pow(total.v.x, 2) - 2 * pow(total.v.y, 2)) * vector.z;
	return (new);
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
	t_p3d cube_r[8];
	for(int i = 0; i < 8; i++)
	{
		cube_r[i] = ft_p3d_project_test1(ft_p3d_rotate_quaterion(ya * 30,cube[i],(t_p3d){1,0,0}));//ft_p3d_rotate_test2(cube[i], (t_p3d){xa,ya,za})); 
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
	t_sphere sphere = {(t_p3d){-3, 0, -16}, 2};
	while(1)
	{
		// ((t_light *)game->elum.light.get(&game->elum.light, 0))->position = game->elum.lights[0].position; //  Because VECTORS!
		// game->spheres[2].center =  ((t_light *)game->elum.light.get(&game->elum.light, 0))->position;       //game->elum.lights[0].position;
		//printf("%f %f\n", ((t_light *)game->elum.light.get(&game->elum.light, 0))->position.x);
		//game->spheres[2].center = game->elum.lights[0].position;
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
		DrawTriangle(game->sdl->surface, (t_point){10,2}, (t_point){10,50}, (t_point){5,37});
		//ft_surface_combine(game->sdl->surface, game->image, &r);
		ft_surface_present(game->sdl, game->sdl->surface);
	 }
}


int	main(int argc, char **argv)
{
	printf("move light source with wasdqe \nchange intensity with zx\n");
	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	t_material ivory = (t_material){(t_p3d){0.4, 0.4, 0.3}, (t_p3d){0.6, 0.3, 0}, 70};
	t_material red_rubber = (t_material){(t_p3d){0.3, 0.1, 0.1}, (t_p3d){0.3, 0.5, 0}, 10000};
	//printf("%f %f %f\n", bb.albendo.x, bb.albendo.y, bb.specular_exponent);
	game.elum.lights = ft_memalloc(sizeof(t_light) * 5);
	game.elum.lights[0] = (t_light){(t_p3d){7, 10, -16}, 1.5};
	game.elum.lights[1] = (t_light){(t_p3d){-20, 20, 20}, 1.5};
	game.elum.lights[2] = (t_light){(t_p3d){30, 50, -25}, 1.8};
	game.elum.lights[3] = (t_light){(t_p3d){30, 20, 30}, 1.7};
	//vector_init(&game.elum.light);
	//vector_add(&game.elum.light,  &(t_light){(t_p3d){7, 10, -16}, 1.5});
	game.elum.number = 4; // number of light sources
	game.n_spheres = 5;
	game.spheres = ft_memalloc(sizeof(t_sphere) * 6);
	game.spheres[0] = (t_sphere){(t_p3d){-3, 0, -16}, ivory, 5, (t_p3d){1, 1, 1}};
	game.spheres[1] = (t_sphere){(t_p3d){-1.0, -1.5, -12}, red_rubber, 2, 5};
	game.spheres[3] = (t_sphere){(t_p3d){1.5, -0.5, -18}, red_rubber, 3, 5};
	game.spheres[4] = (t_sphere){(t_p3d){7, 5, -18}, ivory, 4, 5};

	game.spheres[2] = (t_sphere){(t_p3d){-3.0, 0, -12}, red_rubber, 1, 5}; // this is a light source, move with wasdqe

	// ft_p3d_print(&game.spheres[0].center);
	// ft_p3d_print(&game.spheres[1].center);
	t_sphere sphere;
	
	for (int i=0; i<8; i++)     // Define the cube
	{
		cube[i].x=(float)(50-100*(((i+1)/2)%2));
		cube[i].y=(float)(50-100*((i/2)%2));
		cube[i].z=(float)(50-100*((i/4)%2));
	}


	configure_sphere(argv[1], &sphere);
	ft_init_window(game.sdl, WIN_W, WIN_H);
	printf("%zu, %zu\n", game.sdl->surface->height, game.sdl->surface->width);
	ft_update(&game);
	ft_exit(NULL);
	t_p3d v = (t_p3d){5,0,0};
	t_p3d axis = (t_p3d){0,0,1};
	t_p3d rotated = v;

	rotated = ft_p3d_rotate_quaterion2(90, v ,axis);

	t_p3d rotated2 = ft_p3d_rotate_quaterion(90, v ,axis);

	t_p3d rotated3 = ft_p3d_rotate_test1(v, (t_p3d){0,0,90});
	ft_p3d_print(rotated);
	ft_p3d_print(rotated2);
	ft_p3d_print(rotated3);
}

//https://stackoverflow.com/questions/7870533/c-triangle-rasterization
//https://www.scratchapixel.com/lessons/3d-basic-rendering/rasterization-practical-implementation/rasterization-stage