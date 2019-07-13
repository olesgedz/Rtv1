/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/07/03 12:21:34 by olesgedz         ###   ########.fr       */
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
			game->sdl->surface->data[i+j*width] =  game->gpu->cpuOutput[i+ j *width];
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
		if (game->init_render || game->wsad[0] || game->wsad[1] ||
			game->wsad[2] || game->wsad[3] || game->wsad[4] || game->wsad[5] ||
			game->wsad[6] || game->wsad[7])
			{
				game->init_render = 0;
				ft_render(game);
				ft_surface_present(game->sdl, game->sdl->surface);
			}
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
	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	t_material ivory = (t_material){(t_vec3){0.4, 0.4, 0.3},.albendo= (t_vec3){0.6, 0.3, .0, .0}, .specular_exponent=50};
	t_material glass = (t_material){(t_vec3){.6, 0.7, 0.8}, .albendo =(t_vec3){0, 0.5, 0.1, 0.8}, .specular_exponent=125.};
	t_material red_rubber = (t_material){(t_vec3){0.3, 0.1, 0.1}, .albendo= (t_vec3){0.9, 0.1, .0, .0}, .specular_exponent=10};
	t_material mirror = (t_material){(t_vec3){1.0, 1.0, 1.0}, .albendo =(t_vec3){0, 10, 0.8, .1}, .specular_exponent=1425.};
	game.main_objs.lights = ft_memalloc(sizeof(t_light) * 5);
	game.main_objs.lights[0] = (t_light){(t_vec3){0, 0, -5}, 2};
	game.main_objs.lights[1] = (t_light){(t_vec3){-5, 0, -5}, 2};
	game.main_objs.lights[2] = (t_light){(t_vec3){-2, 0, -5}, 2};
	game.main_objs.lights[3] = (t_light){(t_vec3){5, 0, -5}, 2};
	game.main_objs.elum_num = 5; // number of light sources
	game.init_render = 1;
	game.origin = (t_vec3){0,0,5,1};
	game.gpu = (t_gpu *)malloc(sizeof(t_gpu));
	opencl_init(game.gpu, &game);
	ft_init_window(game.sdl, WIN_W, WIN_H);

	ft_update(&game);
	clReleaseMemObject(game.gpu->cl_bufferOut);
	release_gpu(game.gpu);

	ft_exit(NULL);
}