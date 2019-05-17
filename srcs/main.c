/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:53:03 by jblack-b          #+#    #+#             */
/*   Updated: 2019/05/17 21:43:02 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rtv1.h"

/*
* ! We can't use global variables 
*/
t_game game;

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
* 	Return:value, doesnt change any parameters
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
	
	//new = malloc (sizeof(t_p3d));
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


t_p3d ft_p3d_sum(t_p3d a, t_p3d b)
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


t_p3d ft_p3d_substract(t_p3d a, t_p3d b)
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


// /*
// *	Fucntion: vector multiplication, cross product
// *	Parameters: two vectors no parameters change 
// *	Return: t_p3d vector result of multiplication,
// */
// t_p3d ft_p3d_sum(t_p3d *a, t_p3d *b)
// {
// 	t_p3d new;

// 	new.x = a->x + b->x;
// 	new.y = a->y + b->y;
// 	new.z = a->z + b->z;
// 	return (new);
// }

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
/*
*	Fucntion: checks of ray hits sphere
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/
int ray_intersect(t_sphere *sphere, t_p3d *orig, t_p3d *dir, float *t0)
{
	t_p3d L = ft_p3d_substract(sphere->center, *orig);
	// printf("%f %f %f, dir: %f %f %f\n", L.x, L.y, L.z, dir->x, dir->y, dir->z);
	float tca = ft_p3d_dot_multiply(L, *dir);
	//printf("tca %f\n", tca);
	float d2 = ft_p3d_dot_multiply(L, L) - tca*tca;
	//printf("d2 %f %f \n", d2, sphere->radius * sphere->radius);
	if (d2 > sphere->radius * sphere->radius) return FALSE;
	float thc = sqrtf( sphere->radius * sphere->radius - d2);
	*t0	= tca - thc;
	float t1 = tca + thc;
	if (t0 < 0) *t0 = t1;
	if (t0 < 0) return FALSE;
	return TRUE;
}

/*
*	Fucntion: checks all objects on the scene
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/

int scene_intersect( t_p3d *orig, t_p3d *dir, t_sphere *spheres, t_p3d *hit, t_p3d *N, t_material *material)
{
	float spheres_dist = FLT_MAX; // WHY
	size_t i=0;
	// ft_p3d_print(&spheres[0].center);
	// ft_p3d_print(&spheres[1].center);
	//ft_exit(NULL);
	while (i < game.n_spheres) {
		float dist_i;

		//printf("%d", ray_intersect(&spheres[i], orig, dir, dist_i));
		// printf("%f, %f\n", dist_i, spheres_dist);
		// ft_exit(NULL);
		if (ray_intersect(&spheres[i], orig, dir, &dist_i) && dist_i < spheres_dist)
		{
			spheres_dist = dist_i;
			t_p3d temp = ft_p3d_scalar_multiply(*dir, dist_i);
			*hit = ft_p3d_sum(*orig, temp);
			t_p3d tmp = ft_p3d_substract(*hit, spheres[i].center);
			*N = ft_p3d_normalize(tmp);
			*material = spheres[i].material;
		}
		i++;
	}
	return spheres_dist<1000;
}

/*
*	Fucntion: casts ray for that pixel
*	Parameters: stuff, sphere, ray
*	Return: returns matiral(color) for that pixel
*/

t_p3d cast_ray (t_p3d *orig, t_p3d *dir, t_sphere *spheres) {
	t_p3d point;
	t_p3d N;
	t_material material;

	// ft_p3d_print(&spheres[0].center);
	// ft_p3d_print(&spheres[1].center);
	 float sphere_dist = FLT_MAX;
	//if (!ray_intersect(&spheres[0], orig, dir, &sphere_dist))
	if(!scene_intersect(orig, dir, spheres, &point, &N, &material)) {
		return ft_p3d_create(0.4, 0.4, 0.4); // background color
	}
	float diffuse_light_intensity = 0;
	float specular_light_intensity = 0;
		for (size_t i=0; i<game.elum.number; i++)
		{
			t_p3d light_dir      = ft_p3d_normalize(ft_p3d_substract(game.elum.lights[i].position, point));
			float light_distance = ft_p3d_norm(ft_p3d_substract(game.elum.lights[i].position, point));
			t_p3d shadow_orig = ((ft_p3d_dot_multiply(light_dir, N) < 0) ? ft_p3d_substract(point, ft_p3d_scalar_multiply(N, 1e-3)) : ft_p3d_sum(point, ft_p3d_scalar_multiply(N, 1e-3)));
			t_p3d shadow_pt, shadow_N;
			t_material temp_material;
			if (scene_intersect(&shadow_orig, &light_dir, spheres, &shadow_pt, &shadow_N, &temp_material) && ((ft_p3d_norm(ft_p3d_substract(shadow_pt, shadow_orig)) < light_distance)))
			diffuse_light_intensity  += game.elum.lights[i].intensity * max(0, ft_p3d_dot_multiply(light_dir, N));
			specular_light_intensity += powf(max(0.f, ft_p3d_dot_multiply(ft_p3d_scalar_multiply(reflect(ft_p3d_scalar_multiply(light_dir, -1), N), -1),*dir)),\
			 material.specular_exponent)*game.elum.lights[i].intensity;
		
			// write negative * -1
		}
		//printf("1:");
		//ft_p3d_print(ft_p3d_scalar_multiply(&material.diffuse_color, diffuse_light_intensity));
		//printf("x:%f y:%f light:%f \n", material.albendo.x, material.albendo.y, specular_light_intensity);
	// t_p3d temp = ft_p3d_scalar_multiply(material.diffuse_color, diffuse_light_intensity * material.albendo.x);
	// t_p3d temp2 = ft_p3d_scalar_multiply((t_p3d){1,1,1}, specular_light_intensity * material.albendo.y);
	//material.diffuse_color * diffuse_light_intensity * material.albedo[0] + Vec3f(1., 1., 1.)*specular_light_intensity * material.albedo[1];
	//printf("2:");
	//ft_p3d_print(ft_p3d_sum(&temp, &temp2));
	// if (ft_p3d_sum(&temp, &temp2).x != 0)
	// {
	// 	// printf("\n\n");
	// 	// ft_p3d_print(ft_p3d_scalar_multiply(&material.diffuse_color, diffuse_light_intensity));
	// 	// printf("\n");
	// 	// ft_p3d_print(ft_p3d_sum(&temp, &temp2));
	// 	// printf("\n\n");
	// }
	return ft_p3d_sum(ft_p3d_scalar_multiply(material.diffuse_color, diffuse_light_intensity * material.albendo.x), \
	 ft_p3d_scalar_multiply((t_p3d){1,1,1}, specular_light_intensity *  material.albendo.y));					//ft_p3d_scalar_multiply(&material.diffuse_color, diffuse_light_intensity);
}



	const float fov      = M_PI/3.; // field of vision

/*
*	Fucntion: render all pixels on the surface
*	Parameters: game, sdl
*	Return: none
*/
void 	ft_render(t_game* game, t_sphere *sphere)
{
	int width = game->sdl->surface->width;
	int height = game->sdl->surface->height;
	for (size_t j = 0; j<height ; j++)
	{
		for (size_t i = 0; i< width; i++) {
			float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
			float y = -(2*(j + 0.5)/(float)height - 1)*tan(fov/2.);
			t_p3d dir = ft_p3d_normalize((t_p3d){x, y, -1});//.normalize();
			t_p3d orign = ft_p3d_create(0,0,0);
			t_p3d temp = cast_ray(&orign, &dir, game->spheres);
			game->sdl->surface->data[i+j*width] = ft_rgb_to_hex(225 * max(0, min(1, temp.x)), 225 * max(0, min(1, temp.y)), 225 * max(0, min(1, temp.z)));
			//255 * std::max(0.f, std::min(1.f, framebuffer[i][j]))
			// if (sqrt(pow(i - sphere->center.x, 2) + pow(j - sphere->center.y, 2)) <= sphere->radius)
			// {
			// 	game->sdl->surface->data[i+j*width] = 0xFF0000;
 		//  	game->sdl->surface->data[i+j*width] = ft_rgb_to_hex(temp.x, temp.y, temp.z);
				 
			// }
		}
	}
}

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

void ft_update(t_game *game)
{
	t_rectangle r = (t_rectangle){(t_point){0,0},(t_size){WIN_W, WIN_H}};
	t_sphere sphere = {(t_p3d){-3, 0, -16}, 2};
	while(1)
	{
		game->spheres[2].center = game->elum.lights[0].position;
		ft_surface_clear(game->sdl->surface);
		ft_input(game->sdl, &ft_input_keys);
		if(game->wsad[0]) { game->elum.lights[0].position.z -= 1;}
		if(game->wsad[1]) { game->elum.lights[0].position.z += 1;}
		if(game->wsad[2]) { game->elum.lights[0].position.x -= 1;}
		if(game->wsad[3]) { game->elum.lights[0].position.x += 1;}
		if(game->wsad[4]) { game->elum.lights[0].position.y += 1;}
		if(game->wsad[5]) { game->elum.lights[0].position.y -= 1; }
		if(game->wsad[6]) { game->elum.lights[0].intensity += 0.1; }
		if(game->wsad[7]) { game->elum.lights[0].intensity -= 0.1; }
		ft_render(game, &sphere);
		//ft_put_pixel(game->sdl->surface, &(t_point){500,500}, 0xFF0000);
		ft_surface_combine(game->sdl->surface, game->image, &r);
		ft_surface_present(game->sdl, game->sdl->surface);
		//SDL_Delay(20);
	 }
}


// void Sphere(const t_p3d *c, const float r)
// {

// }

// bool ray_intersect(const t_p3d *orig, const t_p3d dir, float *t0)
// {
// 	t_p3d L = center - orig;
// 	float tca = L*dir;
// 	float d2 = L*L - tca*tca;
// 	if (d2 > radius*radius) return false;
// 	float thc = sqrtf(radius*radius - d2);
// 	t0       = tca - thc;
// 	float t1 = tca + thc;
// 	if (t0 < 0) t0 = t1;
// 	if (t0 < 0) return false;
// 	return true;
// }


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
	game.elum.number = 4;
	game.n_spheres = 5;
	game.spheres = ft_memalloc(sizeof(t_sphere) * 6);
	game.spheres[0] = (t_sphere){(t_p3d){-3, 0, -16}, ivory, 2};
	game.spheres[1] = (t_sphere){(t_p3d){-1.0, -1.5, -12}, red_rubber, 2};
	game.spheres[3] = (t_sphere){(t_p3d){1.5, -0.5, -18}, red_rubber, 3};
	game.spheres[4] = (t_sphere){(t_p3d){7, 5, -18}, ivory, 4};

	game.spheres[2] = (t_sphere){(t_p3d){-3.0, 0, -12}, red_rubber, 1}; // this is a light source, move with wasdqe

	// ft_p3d_print(&game.spheres[0].center);
	// ft_p3d_print(&game.spheres[1].center);
	t_sphere sphere;
	
	configure_sphere(argv[1], &sphere);
	//printf("%d",ray_intersect(&sphere, ft_p3d_create(0,0,0), ft_p3d_normalize(&(t_p3d){650, 650, -1}, 1), FLT_MAX));
	ft_init_window(game.sdl, WIN_W, WIN_H);
	printf("%zu, %zu\n", game.sdl->surface->height, game.sdl->surface->width);

	ft_update(&game);
	ft_exit(NULL);
}
