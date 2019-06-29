/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/06/27 21:32:47 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>
#include "libsdl.h"
//aelinor-
//home
/*
* ! We can't use global variables 
*/

#define FPS

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

static	int	is_any_figure_closer(t_main_obj *main, double cache)
{
	if (cache > 0 && cache < main->closest)
	{
		main->closest = cache;
		return (1);
	}
	return (0);
}


t_vec3 sphere_get_normal(t_ray *ray, t_object *figure)
{
	return (ft_vec3_substract(ray->hit, ((t_sphere *)figure->object)->center));
}

t_vec3 plane_get_normal(t_ray *ray, t_object *figure)
{
	t_plane *plane = (t_plane *)figure->object;
	if (ft_vec3_dot_multiply(ray->dir, plane->normal) < 0)
		return (plane->normal);
	return (ft_vec3_scalar_multiply(plane->normal, -1));
}

t_vec3 cylinder_get_normal(t_ray *ray, t_object *figure) // Some how works. but that isn't right, I was just pressing buttons .---.
{
	t_cylinder *cylinder = (t_cylinder *) figure->object;
	
	double	m;
	t_vec3	n;
	t_vec3	p;
	
	m = ft_vec3_dot_multiply(ray->dir, cylinder->v) * ray->t
		+ ft_vec3_dot_multiply(ft_vec3_substract(ray->orig, cylinder->center), cylinder->v);
	p = ft_vec3_sum(ray->orig, ft_vec3_scalar_multiply(ray->dir, ray->t));
	n = ft_vec3_normalize(ft_vec3_substract(ft_vec3_substract(p, cylinder->center), ft_vec3_scalar_multiply(cylinder->v, m)));
	if (ft_vec3_dot_multiply(ray->dir, n) > 0.0001)
		n = ft_vec3_scalar_multiply(n, -1);
	return (n);
}

t_vec3 cone_get_normal(t_ray *ray, t_object *figure)
{
	t_vec3	n;
	double	m;
	t_cone *cone = (t_cone *) figure->object;
	m = ft_vec3_dot_multiply(ray->dir, cone->v) * ray->t
		+ ft_vec3_dot_multiply(ft_vec3_substract(ray->orig, cone->center), cone->v);
	n = ft_vec3_scalar_multiply(ft_vec3_scalar_multiply(cone->v, m), (1 + cone->radius * cone->radius));
	n = ft_vec3_normalize(ft_vec3_substract(ft_vec3_substract(ray->hit, cone->center), n));
	if (ft_vec3_dot_multiply(ray->dir, n) > 0.0001)
		n = ft_vec3_scalar_multiply(n, -1);
	return (n);
}
/*
*	Fucntion: checks all objects on the scene
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/

int scene_intersect(t_main_obj *main, t_ray *ray, t_vec3 *hit, t_vec3 *N, t_material *material)
{
 	main->closest = FLT_MAX; 
	float dist_i;
	float object_dist = FLT_MAX; 
	int i = 0;
	while (i < main->figures_num)
	{
		if (main->figures[i].intersect(&main->figures[i], ray, &dist_i) && dist_i < object_dist)
		{
			is_any_figure_closer(main, dist_i); 
			object_dist = dist_i;
			ray->t = dist_i;
			t_vec3 temp = ft_vec3_scalar_multiply(ray->dir, dist_i);
			*hit = ft_vec3_sum(ray->orig, temp);
			ray->hit = *hit;
			temp = main->figures[i].get_normal(ray, &main->figures[i]); // problem also cause of shading not working
			*N = ft_vec3_normalize(temp);
			*material = ((t_sphere *)main->figures[i].object)->material; // mm not suppose to be  t_sphere, but works
		}
		i++;
	}
	return main->closest < 1000;
}

/*
*	Fucntion: casts ray for that pixel
*	Parameters: stuff, sphere, ray
*	Return: returns matiral(color) for that pixel
*/

t_vec3 cast_ray(t_main_obj *main, t_ray *ray, size_t depth)
{
	t_vec3 point;
	t_vec3 N;
	t_material material; 
	int	i;

	float sphere_dist = FLT_MAX;
	//if (!ray_intersect(&spheres[0], orig, dir, &sphere_dist))
	if( depth > 4 || !scene_intersect(main, ray, &point, &N, &material))
		return ft_vec3_create(0.2, 0.7, 0.8); // background color
	// else
	// {
	// 		return ft_vec3_create(1, 0, 0);
	// }
	t_ray reflect_ray;
	reflect_ray.dir = ft_vec3_normalize(reflect(ray->dir, N));
	reflect_ray.orig  = ft_vec3_dot_multiply(reflect_ray.dir, N) < 0
		? ft_vec3_substract(point, ft_vec3_scalar_multiply(N, 1e-3))
		: ft_vec3_sum(point, ft_vec3_scalar_multiply(N, 1e-3));
	t_vec3 reflect_color = cast_ray(main, &reflect_ray, depth + 1);
	t_ray refract_ray;
	refract_ray.dir = ft_vec3_normalize(refract(ray->dir, N, material.refractive_index, 1.0f));
	refract_ray.orig = ft_vec3_dot_multiply(refract_ray.dir, N) < 0
		? ft_vec3_substract(point, ft_vec3_scalar_multiply(N, 1e-3))
		: ft_vec3_sum(point, ft_vec3_scalar_multiply(N, 1e-3));
	t_vec3 refract_color = cast_ray(main, &refract_ray, depth + 1);
	
	float diffuse_light_intensity = 0;
	float specular_light_intensity = 0;
	i = -1;

	while (++i < main->elum_num)
	{
		t_vec3 light_dir      =  ft_vec3_normalize(ft_vec3_substract(main->lights[i].position, point));
		double light_distance = ft_vec3_norm(ft_vec3_substract(main->lights[i].position, point));
		t_ray shadow_ray;
		shadow_ray.orig = (ft_vec3_dot_multiply(light_dir, N) < 0)
			? ft_vec3_substract(point, ft_vec3_scalar_multiply(N, 1e-3))
			: ft_vec3_sum(point, ft_vec3_scalar_multiply(N, 1e-3));
		shadow_ray.dir = light_dir;
		t_vec3 shadow_pt, shadow_N;
		t_material temp_material;
		if (scene_intersect(main, &shadow_ray, &shadow_pt, &shadow_N, &temp_material)
			&& (ft_vec3_norm(ft_vec3_substract(shadow_pt, shadow_ray.orig)) < light_distance))
			continue;
		diffuse_light_intensity  +=  main->lights[i].intensity * max(0.0f, 
			ft_vec3_dot_multiply(ft_vec3_normalize(light_dir), ft_vec3_normalize(N)));
		specular_light_intensity += powf(max(0.f, ft_vec3_dot_multiply(ft_vec3_scalar_multiply(
			reflect(ft_vec3_scalar_multiply(light_dir, -1), N), -1), ray->dir)),
		 	material.specular_exponent)*main->lights[i].intensity;
	}
		
	return ft_vec3_sum(ft_vec3_sum(ft_vec3_sum(ft_vec3_scalar_multiply(material.diffuse_color,\
		diffuse_light_intensity * material.albendo.x), \
	 	ft_vec3_scalar_multiply((t_vec3){1,1,1}, specular_light_intensity *  material.albendo.y)),\
		ft_vec3_scalar_multiply(reflect_color,  material.albendo.z)), ft_vec3_scalar_multiply(refract_color,  material.albendo.w));					//ft_vec3_scalar_multiply(&material.diffuse_color, diffuse_light_intensity);
	// return ft_vec3_sum(ft_vec3_scalar_multiply(material.diffuse_color, diffuse_light_intensity * material.albendo.x), \
	// 	ft_vec3_scalar_multiply((t_vec3){1,1,1}, specular_light_intensity *  material.albendo.y));
}

	const float fov      = M_PI/2.; // field of vision

/*
*	Fucntion: render all pixels on the surface
*	Parameters: game, sdl
*	Return: none
*/
void 	ft_render(t_game* game)
{
	int		i;
	int		j;
	int width = game->sdl->surface->width;
	int height = game->sdl->surface->height;
	j = -1;
	ft_run_gpu(game->gpu);
	
	while (++j < height)
	{
		i = -1;
		while (++i < width)	
	{
			// game->origin = ft_vec3_multiply_matrix((t_vec3){0,0,0,1}, 
			// 					ft_mat4_multiply_mat4(ft_mat4_translation_matrix((t_vec3){eyex,eyey,eyez}), 
			// 											ft_mat4_rotation_matrix((t_vec3) {0,-1,0}, xa))); //USELESS ITERATION
			//t_vec3 temp = (t_vec3){c}//cast_ray(&game->main_objs, &(t_ray){game->origin, dir}, 0);
			//game->sdl->surface->data[i+j*width] = ft_rgb_to_hex(225 * max(0, min(1, temp.x)), 225 * max(0, min(1, temp.y)), 225 * max(0, min(1, temp.z)));
			game->sdl->surface->data[i+j*width] =  game->gpu->cpuOutput[i+ j *width];
			//ft_rgb_to_hex(225 * max(0, min(1, temp.x)), 225 * max(0, min(1, temp.y)), 225 * max(0, min(1, temp.z)));
		
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
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	while(TRUE)
	{
		current_ticks = clock();
		ft_surface_clear(game->sdl->surface);
		ft_input(game->sdl, &ft_input_keys);
		game->wsad[0] ? game->main_objs.lights[0].position.z -= 1: 0;
		game->wsad[1] ? game->main_objs.lights[0].position.z += 1 : 0;
		game->wsad[2] ? game->main_objs.lights[0].position.x -= 1 : 0;
		game->wsad[3] ? game->main_objs.lights[0].position.x += 1 : 0;
		game->wsad[4] ? game->main_objs.lights[0].position.y += 1 : 0;
		game->wsad[5] ? game->main_objs.lights[0].position.y -= 1 : 0;
		game->wsad[6] ? game->main_objs.lights[0].intensity += 0.1 : 0;
		game->wsad[7] ? game->main_objs.lights[0].intensity -= 0.1 : 0;
		//
		// game->wsad[0] ? eyez -= 1: 0;
		// game->wsad[1] ? eyez += 1 : 0;
		// game->wsad[2] ? eyex -= 1 : 0;
		// game->wsad[3] ? eyex += 1 : 0;
		// game->wsad[4] ? eyey += 1 : 0;
		// game->wsad[5] ? eyey -= 1 : 0;
		ft_render(game);
		ft_surface_present(game->sdl, game->sdl->surface);
	#ifdef FPS
				 delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
    if(delta_ticks > 0)
        fps = CLOCKS_PER_SEC / delta_ticks;
		
			printf("fps :%lu\n", fps);
	#endif
	SDL_Delay(200);
	 }

}

void ft_object_push(t_game *game, t_object *object)
{
	if (game->main_objs.figures == NULL)
		game->main_objs.figures_num = 0;
	game->main_objs.figures = realloc(game->main_objs.figures, sizeof(t_object) * (game->main_objs.figures_num + 1));
	game->main_objs.figures[game->main_objs.figures_num] = *object;
game->main_objs.figures_num += 1;
}

int	main(int argc, char **argv)
{
	printf("move light source with wasdqe \nchange intensity with zx\n");
	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	t_material ivory = (t_material){(t_vec3){0.4, 0.4, 0.3},.albendo= (t_vec3){0.6, 0.3, .0, .0}, .specular_exponent=50};
	t_material glass = (t_material){(t_vec3){.6, 0.7, 0.8}, .albendo =(t_vec3){0, 0.5, 0.1, 0.8}, .specular_exponent=125.};
	t_material red_rubber = (t_material){(t_vec3){0.3, 0.1, 0.1}, .albendo= (t_vec3){0.9, 0.1, .0, .0}, .specular_exponent=10};
	t_material mirror = (t_material){(t_vec3){1.0, 1.0, 1.0}, .albendo =(t_vec3){0, 10, 0.8, .1}, .specular_exponent=1425.};
	//ft_vec3_print(glass.albendo);
	game.main_objs.lights = ft_memalloc(sizeof(t_light) * 5);
	game.main_objs.lights[0] = (t_light){(t_vec3){0, 0, -5}, 2};
	game.main_objs.lights[1] = (t_light){(t_vec3){-5, 0, -5}, 2};
	game.main_objs.lights[2] = (t_light){(t_vec3){-2, 0, -5}, 2};
	game.main_objs.lights[3] = (t_light){(t_vec3){5, 0, -5}, 2};
	game.main_objs.elum_num = 5; // number of light sources

	ft_object_push(&game, &(t_object){&(t_cone){(t_vec3){0, 2, -50}, ivory, 1.5, (t_vec3){0.5, 0.5, 0}, 30, (t_vec3){0, 2, -5}}, cone_intersection, cone_get_normal});
	// ft_object_push(&game, &(t_object){&(t_sphere){(t_vec3){1.5, -0.5, -18}, glass, 3, 5}, sphere_intersection, sphere_get_normal});
	ft_object_push(&game, &(t_object){&(t_sphere){(t_vec3){6, -0.5, -18}, ivory, 3, 5},sphere_intersection, sphere_get_normal});
	ft_object_push(&game, &(t_object){&(t_cylinder){(t_vec3){-7, 2, -20}, red_rubber, 2,(t_vec3){0,1,0}, -2, 2}, cylinder_intersection, cylinder_get_normal});
	// ft_object_push(&game, &(t_object){&(t_plane){(t_vec3){0, 1, 0, 4}, (t_vec3){0,1,0}, red_rubber}, plane_intersection, plane_get_normal});
	
	game.origin = (t_vec3){0,0,5,1};

	game.gpu = (t_gpu *)malloc(sizeof(t_gpu));
	opencl_init(game.gpu, &game);
	ft_init_window(game.sdl, WIN_W, WIN_H);

	//bind_data(game->gpu, &game->main_objs);
	// while (++j < WIN_H)
	// {
	// 	i = -1;
	// 	while (++i < WIN_W)	
	// 	{
		
	// 		if(game.gpu->cpuOutput[i+j*WIN_W] != 0)
	// 			printf("%f\n",game.gpu->cpuOutput[i+j*WIN_W] ); //ft_rgb_to_hex(225 * max(0, min(1, temp.x)), 225 * max(0, min(1, temp.y)), 225 * max(0, min(1, temp.z)));
		
	// 	}
	// }
	//bind_data(game.gpu, &game.main_objs);
	ft_update(&game);
	clReleaseMemObject(game.gpu->cl_bufferOut);
	release_gpu(game.gpu);

	ft_exit(NULL);
}