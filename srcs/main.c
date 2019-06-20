/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/06/20 18:26:43 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>
//aelinor-
//home
/*
* ! We can't use global variables 
*/

//#define FPS

t_game game;
float xa, ya, za;

float eyex, eyey, eyez;
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
					case SDLK_LEFT: xa+=0.05; break;
					case SDLK_RIGHT: xa-=0.05; break;
					default: break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:  
				break;
			case SDL_QUIT: ft_exit(NULL);
		}
	return (1);
}

t_vec3 refract(t_vec3 I, t_vec3 N, const float eta_t, const float eta_i) { // Snell's law
	float cosi = -max(-1.f, min(1.f, ft_vec3_dot_multiply(I,N)));
    if (cosi<0) return refract(I, ft_vec3_neg(N), eta_i, eta_t); // if the ray comes from the inside the object, swap the air and the media
    float eta = eta_i / eta_t;
    float k = 1 - eta*eta*(1 - cosi*cosi);
    return k<0 ? (t_vec3){1,0,0,1} : ft_vec3_sum(ft_vec3_scalar_multiply(I,eta), ft_vec3_scalar_multiply(N,(eta*cosi - sqrtf(k)))); // k<0 = total reflection, no ray to refract. I refract it anyways, this has no physical meaning
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

static	int	is_any_figure_closer(t_game *game, double cache)
{
	if (cache > 0 && cache < game->closest)
	{
		game->closest = cache;
		return (1);
	}
	return (0);
}

/*
*	Fucntion: checks all objects on the scene
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/

int scene_intersect(t_game *game, t_vec3 *orig, t_vec3 *dir, t_vec3 *hit, t_vec3 *N, t_material *material)
{
 	game->closest = FLT_MAX; // WHY
// 	// ft_vec3_print(&spheres[1].center);
// 	//ft_exit(NULL);
// 		float cone_dist = FLT_MAX; // WHY
// 			size_t i = -1;

// 		while (++i < game->n_cones)
// 	{
// 		float dist_i = 0;

// 		if (cone_intersection1(&game->cones[i], orig, dir, &dist_i) && dist_i < cone_dist)
// 		{
// 			cone_dist = dist_i;
// 			t_vec3 temp = ft_vec3_scalar_multiply(*dir, dist_i);
// 			if (temp.y > 0.5 || -0.5 > temp.y)
// 				continue;
// 			*hit = ft_vec3_sum(*orig, temp);
// 			temp = ft_vec3_substract(*hit, game->cones[i].center);
// 			*N = ft_vec3_normalize(temp);
// 			*material = game->cones[i].material;
// 			is_any_figure_closer(game, dist_i); 

// 		}
// 	}
// 	float spheres_dist = FLT_MAX; // WHY
// 	i = -1;
// 	while (++i < game->n_spheres)
// 	{
// 		float dist_i;

// 		if (ray_intersect_sphere_book(&game->spheres[i], orig, dir, &dist_i) && dist_i < spheres_dist)
// 		{
// 			is_any_figure_closer(game, dist_i); 
// 			spheres_dist = dist_i;
// 			t_vec3 temp = ft_vec3_scalar_multiply(*dir, dist_i);
// 			*hit = ft_vec3_sum(*orig, temp);
// 			temp = ft_vec3_substract(*hit, game->spheres[i].center);
// 			*N = ft_vec3_normalize(temp);
			
// 			*material = game->spheres[i].material;
// 		}
// 	}


// float cylinder_dist = FLT_MAX; // WHY
// 	i = -1;
// 	while (++i < game->n_cylinders)
// 	{
// 		float dist_i;

// 		if (cylinder_intersection1(&game->cylinders[i], orig, dir, &dist_i) && dist_i < spheres_dist)
// 		{
// 			is_any_figure_closer(game, dist_i); 
// 			spheres_dist = dist_i;
// 			t_vec3 temp = ft_vec3_scalar_multiply(*dir, dist_i);
// 			*hit = ft_vec3_sum(*orig, temp);
// 			temp = ft_vec3_substract(*hit, game->cylinders[i].center);
// 			*N = ft_vec3_normalize(temp);
			
// 			*material = game->cylinders[i].material;
// 		}
// 	}


// 	// ft_vec3_print(&spheres[0].center);
// 	// ft_vec3_print(&spheres[1].center);
// 	//ft_exit(NULL);
	



// 	float checkerboard_dist = FLT_MAX;


	// float dist_i;
// 	// t_plane plane = (t_plane){(t_vec3){10, 10, 10}, (t_normal3){0, 1, 0},\
// 	// .material = spheres[0].material};
// 	// if(plane_intersection2((t_ray){.orig = *orig, .dir = *dir}, plane, &dist_i))
// 	// {
// 	// 	checkerboard_dist = dist_i;
		
// 	// }
//     // if (fabs(dir->y) > 1e-3)
// 	// {
//     //     float d = -(orig->y + 4) / dir->y; // the checkerboard plane has equation y = -4
//     //     t_vec3 board = ft_vec3_sum(*orig, ft_vec3_scalar_multiply(*dir, d));
//     //     if (d > 0 && fabs(board.x) < 10 && board.z < -10 && board.z > -30 && d < spheres_dist)
// 	// 	{
// 	// 		is_any_figure_closer(game, d); 
//     //         checkerboard_dist = d;
//     //         *hit = board;
//     //         *N = ft_vec3_create(0, 1, 0);
// 	// 		*material = (t_material){(t_vec3){0.3, 0.1, 0.1}, .albendo= (t_vec3){0.9, 0.1, .1, 0}, .specular_exponent=10};
//     //         material->diffuse_color = ((int)(0.5*(hit->x+1000)) + (int)(0.5*(hit->z)) & 1) ? ft_vec3_create(0.1, 0.1, 0.1) : ft_vec3_create(0.8, 0.7, 0.6);
//     //     }
//     // }
	float dist_i;
	float spheres_dist = FLT_MAX; // WHY
	int i = 0;
	while (i < 1)//game->n_figures)
	{
		// float dist_i;

		if (((t_object)game->figures[i]).intersect(&game->figures[i], orig, dir, &dist_i) && dist_i < spheres_dist)
		{
			is_any_figure_closer(game, dist_i); 
			spheres_dist = dist_i;
			t_vec3 temp = ft_vec3_scalar_multiply(*dir, dist_i);
			*hit = ft_vec3_sum(*orig, temp);
			temp = ft_vec3_substract(*hit, ((t_sphere *)((t_object)game->figures[i]).object)->center); // problem
			*N = ft_vec3_normalize(temp);
			
			*material = ((t_sphere *)((t_object)game->figures[i]).object)->material;
		}
		i++;
	}

	return game->closest < 1000;
	//return spheres_dist < 1000;
}





/*
*	Fucntion: casts ray for that pixel
*	Parameters: stuff, sphere, ray
*	Return: returns matiral(color) for that pixel
*/

t_vec3 cast_ray(t_game *game, t_vec3 *orig, t_vec3 *dir, t_sphere *spheres, size_t depth)
{
	t_vec3 point;
	t_vec3 N;
	t_material material; 
	int	i;


	float sphere_dist = FLT_MAX;
	//if (!ray_intersect(&spheres[0], orig, dir, &sphere_dist))
	if( depth > 4 || !scene_intersect(game, orig, dir, &point, &N, &material))
		return ft_vec3_create(0.2, 0.7, 0.8); // background color
	// else
	// {
	// 		return ft_vec3_create(1, 0, 0);
	// }
	
	t_vec3 reflect_dir = ft_vec3_normalize(reflect(*dir, N));
	t_vec3 reflect_orig = ft_vec3_dot_multiply(reflect_dir, N) < 0 ? ft_vec3_substract(point, ft_vec3_scalar_multiply(N, 1e-3)) : ft_vec3_sum(point, ft_vec3_scalar_multiply(N, 1e-3));
	t_vec3 reflect_color = cast_ray(game, &reflect_orig, &reflect_dir, spheres, depth + 1);

	t_vec3 refract_dir = ft_vec3_normalize(refract(*dir, N, material.refractive_index, 1.0f));
	t_vec3 refract_orig = ft_vec3_dot_multiply(refract_dir, N) < 0 ? ft_vec3_substract(point, ft_vec3_scalar_multiply(N, 1e-3)) : ft_vec3_sum(point, ft_vec3_scalar_multiply(N, 1e-3));
	t_vec3 refract_color = cast_ray(game, &refract_orig, &refract_dir , spheres, depth + 1);
	
	float diffuse_light_intensity = 0;
	float specular_light_intensity = 0;
	i = -1;

	while (++i < game->elum.number)
	{
		t_vec3 light_dir      =  ft_vec3_normalize(ft_vec3_substract( game->elum.lights[i].position, point));
		double light_distance = ft_vec3_norm(ft_vec3_substract(game->elum.lights[i].position, point));
		
		t_vec3 shadow_orig = (ft_vec3_dot_multiply(light_dir, N) < 0) ? ft_vec3_substract(point, ft_vec3_scalar_multiply(N, 1e-3)) : ft_vec3_sum(point, ft_vec3_scalar_multiply(N, 1e-3));
		t_vec3 shadow_pt, shadow_N;
		t_material temp_material;
		if (scene_intersect(game, &shadow_orig, &light_dir, &shadow_pt, &shadow_N, &temp_material) && (ft_vec3_norm(ft_vec3_substract(shadow_pt, shadow_orig)) < light_distance))
			continue;
		// if (ft_vec3_dot_multiply(N, light_dir) > 0.9)
		// {
		// 	printf("%f\n",  ft_vec3_dot_multiply(N, light_dir));
		//   diffuse_light_intensity +=  game->elum.lights[i].intensity * ft_vec3_dot_multiply(N, light_dir);// / (ft_vec3_length(N));
		// }
		diffuse_light_intensity  +=  game->elum.lights[i].intensity * max(0.0f, ft_vec3_dot_multiply(ft_vec3_normalize(light_dir), ft_vec3_normalize(N)));
		specular_light_intensity += powf(max(0.f, ft_vec3_dot_multiply(ft_vec3_scalar_multiply(reflect(ft_vec3_scalar_multiply(light_dir, -1), N), -1),*dir)),\
		 	material.specular_exponent)*game->elum.lights[i].intensity;
	}
		
	return ft_vec3_sum(ft_vec3_sum(ft_vec3_sum(ft_vec3_scalar_multiply(material.diffuse_color,\
	 diffuse_light_intensity * material.albendo.x), \
	 	ft_vec3_scalar_multiply((t_vec3){1,1,1}, specular_light_intensity *  material.albendo.y)), ft_vec3_scalar_multiply(reflect_color,  material.albendo.z)), ft_vec3_scalar_multiply(refract_color,  material.albendo.w));					//ft_vec3_scalar_multiply(&material.diffuse_color, diffuse_light_intensity);
	// return ft_vec3_sum(ft_vec3_scalar_multiply(material.diffuse_color, diffuse_light_intensity * material.albendo.x), \
	// 	ft_vec3_scalar_multiply((t_vec3){1,1,1}, specular_light_intensity *  material.albendo.y));
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
	t_mat4 m;
	while (++j < height)
	{
		i = -1;
		while (++i < width)
		{
			float x = (2 * (i + 0.5) / (float)width  - 1) * tan(fov / 2.) * width / (float)height;
			float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
			t_vec3 dir = ft_vec3_normalize((t_vec3){x, y, -1});
			game->origin = ft_vec3_multiply_matrix((t_vec3){0,0,0,1}, m = ft_mat4_multiply_mat4(ft_mat4_translation_matrix((t_vec3){eyex,eyey,eyez}), ft_mat4_rotation_matrix((t_vec3) {0,-1,0}, xa)));
			game->origin =ft_vec3_create(eyex,eyey,eyez);
			dir = ft_vec3_multiply_matrix(dir, ft_mat4_rotation_matrix((t_vec3) {0,-1,0}, xa));
			t_vec3 temp = cast_ray(game, &game->origin, &dir, game->spheres, 0);
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

void ft_update(t_game *game)
{
	t_rectangle r = (t_rectangle){(t_point){0,0},(t_size){WIN_W, WIN_H}};
	t_sphere sphere = {(t_vec3){-3, 0, -16}, 2};
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	while(1)
	{
		//game->spheres[0].center = ft_vec3_sum(game->elum.lights[0].position, (t_vec3){1,1,1});
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
		//
		// game->wsad[0] ? eyez -= 1: 0;
		// game->wsad[1] ? eyez += 1 : 0;
		// game->wsad[2] ? eyex -= 1 : 0;
		// game->wsad[3] ? eyex += 1 : 0;
		// game->wsad[4] ? eyey += 1 : 0;
		// game->wsad[5] ? eyey -= 1 : 0;
		ft_render(game, &sphere);
		ft_surface_present(game->sdl, game->sdl->surface);
	#ifdef FPS
				 delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
    if(delta_ticks > 0)
        fps = CLOCKS_PER_SEC / delta_ticks;
		
			printf("fps :%lu\n", fps);
	#endif
	 }

}


void ft_object_push(t_game *game, t_object *object)
{
	// if (game->figures == NULL)
	// {
	// 	game->n_figures = 0;
	// 	game->figures = malloc(sizeof(t_object));
	// }
	// else
	// 	game->figures = ft_realloc(game->figures, sizeof(t_object) * (game->n_figures + 1));
	// game->figures[game->n_figures] = *object;
	// game->n_figures += 1;

	if (game->figures == NULL)
		game->n_figures = 0;
	game->figures = ft_realloc(game->figures, sizeof(t_object) * (game->n_figures + 1));
	game->figures[game->n_figures] = *object;
	game->n_figures += 1;
}

t_sphere *ft_sphere_create(t_sphere sphere)
{
	t_sphere *new = ft_memalloc(sizeof(t_sphere));
	*new = sphere;
	return (new); 
}

int	main(int argc, char **argv)
{



	printf("move light source with wasdqe \nchange intensity with zx\n");
	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	t_material ivory = (t_material){(t_vec3){0.4, 0.4, 0.3},.albendo= (t_vec3){0.6, 0.3, 0, 0}, .specular_exponent=50};
	t_material glass = (t_material){(t_vec3){.6, 0.7, 0.8}, .albendo =(t_vec3){0, 0.5, 0.1, 0.8}, .specular_exponent=125.};
	t_material red_rubber = (t_material){(t_vec3){0.3, 0.1, 0.1}, .albendo= (t_vec3){0.9, 0.1, .0, 0}, .specular_exponent=10};
	t_material mirror = (t_material){(t_vec3){1.0, 1.0, 1.0}, .albendo =(t_vec3){0, 10, 0.8, 1}, .specular_exponent=1425.};
	game.elum.lights = ft_memalloc(sizeof(t_light) * 5);
	game.elum.lights[0] = (t_light){(t_vec3){0, 0, -5}, 1.5};
	game.elum.lights[1] = (t_light){(t_vec3){-5, 0, -5}, 1.5};
	game.elum.lights[2] = (t_light){(t_vec3){-2, 0, -5}, 1.8};
	game.elum.lights[3] = (t_light){(t_vec3){5, 0, -5}, 1.7};
	game.elum.number = 1; // number of light sources
	// game.n_cones = 1;
	// game.cones = ft_memalloc(sizeof(t_cone) * 6);
	// game.n_spheres = 1;
	// game.n_cylinders = 0;
	// game.spheres = ft_memalloc(sizeof(t_sphere) * 6);
	// game.cylinders = ft_memalloc(sizeof(t_cylinder) * 6);
	//game.cones[0] = (t_cone){(t_vec3){0, 2, -50}, ivory, 2, (t_vec3){0, 1, 0}, 30, (t_vec3){0, 2, -5}};
	// game.spheres[0] = (t_sphere){(t_vec3){0, 2, -10}, glass, .1, (t_vec3){0.4, -0.8, 0.6}};
	// game.spheres[1] = (t_sphere){(t_vec3){-1.0, -1.5, -12}, glass, 2, 5};
	// game.spheres[3] = (t_sphere){(t_vec3){1.5, -0.5, -18}, red_rubber, 3, 5};
	// game.spheres[4] = (t_sphere){(t_vec3){7, 5, -18}, ivory, 4, 5};
	ft_object_push(&game, &(t_object){&(t_sphere){(t_vec3){1.5, -0.5, -18}, red_rubber, 3, 5},ray_intersect_sphere_book});
	ft_object_push(&game, &(t_object){&(t_sphere){(t_vec3){1.5, -0.5, -18}, red_rubber, 3, 5},ray_intersect_sphere_book});
	game.origin = (t_vec3){0,0,5,1};
	ft_init_window(game.sdl, WIN_W, WIN_H);
	ft_update(&game);
	ft_exit(NULL);
}