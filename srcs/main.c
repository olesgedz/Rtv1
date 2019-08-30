/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/08/30 21:36:19 by olesgedz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>
#include "libsdl.h"
#include "libvect.h"
#include "libcl.h"
//aelinor-
//home
/*
* ! We can't use global variables 
*/

//#define FPS

t_game game;

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
					default: break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:  
				break;
			case SDL_QUIT: ft_exit(NULL);
		}
	return (1);
}





static float u_clamp(float x)
{
	return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
}

static int toInt(float x)
{ 
	return (int)(u_clamp(x) * 255);
}

 int getSurroundingAverage(t_game * game, int x, int y) {
    unsigned int index = ( game->sdl->surface->height - y - 1) *  game->sdl->surface->width + x;
   cl_float3 avg;
   cl_float3 temp;
    int total = 1;
	int color = 0;
	// if(x == 0 || y == 0)
	// 	return 0;
	for(int j = y - 1; j < y + 1; j++)
	{
		for(int k = x - 1; k < x + 1; k++)
		{
			temp =  game->gpu->vec_temp[k + j * game->sdl->surface->width];
			avg = (cl_float3){(avg.v4[0] + temp.v4[0]), (avg.v4[1] + temp.v4[1]), (avg.v4[2] + temp.v4[2])};
			total++;
		}
	}
	//avg = game->sdl->surface->data[x + y * game->sdl->surface->width];
    return ft_rgb_to_hex(toInt(avg.v4[0] / total), toInt(avg.v4[1]/ total), toInt(avg.v4[2]/ total));
  }

void ft_filter(t_game* game)
{
	int		i;
	int		j;
	int width = game->sdl->surface->width;
	int height = game->sdl->surface->height;
	j = 0;
	while (++j < height)
	{
		i = 0;
		while (++i < width)	
		{
			game->sdl->surface->data[i+j*width] = getSurroundingAverage(game, i, j); //game->gpu->cpuOutput[i+ j *width];

		}
	}
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
	//ft_run_gpu(game->gpu);
	while (++j < height)
	{
		i = -1;
		while (++i < width)	
			game->sdl->surface->data[i+j*width] =  game->gpuOutput[i+ j *width];
	}
	//ft_filter(game);
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
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	while(TRUE)
	{
		current_ticks = clock();
		ft_surface_clear(game->sdl->surface);
		ft_input(game->sdl, &ft_input_keys);
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


void opencl()
{
	game.kernels = ft_memalloc(sizeof(t_cl_krl) * 2);
	game.cl_info = ft_memalloc(sizeof(t_cl_info));
	game.gpuOutput = ft_memalloc(sizeof(int) * WIN_H * WIN_W);

	cl_init(game.cl_info);
	ERROR(game.cl_info->ret);
	int fd = open("srcs/mix.cl", O_RDONLY);
	size_t global = WIN_W * WIN_H;

	t_vect vect;
	vect_init(&vect);
	VECT_STRADD(&vect, "render_kernel" ":");
	VECT_STRADD(&vect, "-I srcs/cl_files/");
	//cl_krl_init(game.kernels, 1);	
//	cl_mem cl_bufferOut = clCreateBuffer(game.cl_info->ctxt, CL_MEM_WRITE_ONLY, WIN_H * WIN_W * sizeof(cl_int), NULL, &game.cl_info->ret);
//	game.kernels->sizes[0] = sizeof(cl_int) * WIN_H * WIN_W;
	// game.kernels->sizes[1] = sizeof(cl_int);
	// game.kernels->sizes[2] = sizeof(cl_int);
//	game.kernels->args[0] = cl_bufferOut;
	game.cl_info->ret = cl_krl_build(game.cl_info, game.kernels, fd, &vect);
	// size_t size = 0;
	// char *ker = ft_strnew(0);
	// ker = read_file(fd, &size);
	// game.cl_info->ctxt = clCreateContext(0, 1, &game.cl_info->dev_id, NULL, NULL, &game.cl_info->ret);
	// //game.cl_info->prog = clCreateProgramWithSource(game.cl_info->ctxt, 1, (const char **)&ker, NULL, &game.cl_info->ret);
	// //clGetProgramBuildInfo(game.cl_info->prog, game.cl_info->dev_id, CL_PROGRAM_BUILD_LOG, 10000, buffer, &len);
	// ERROR(game.cl_info->ret);
	// //cl_write(game.cl_info, cl_bufferOut, sizeof(cl_mem)
	// game.cl_info->ret |= clSetKernelArg(game.kernels->krl, 0, sizeof(cl_mem), &cl_bufferOut);
	// ERROR(game.cl_info->ret);
	// game.cl_info->ret = cl_krl_exec(game.cl_info, game.kernels->krl, 1, &global);
	// ERROR(game.cl_info->ret);
	// game.cl_info->ret = cl_read(game.cl_info, cl_bufferOut, sizeof(cl_int) * WIN_H * WIN_W, game.gpuOutput);
	// printf("%d\n",game.cl_info->ret);
	// ERROR(game.cl_info->ret);
}

int	main(int argc, char **argv)
{
	// t_cl_info cl_info;
	// cl_init(&cl_info);
	//VECT_ADD(v, "hello");
	//printf("%s", (char *)v->data);
	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	game.init_render = 1;
	game.origin = (t_vec3){0,0,5};
	game.gpu = (t_gpu *)malloc(sizeof(t_gpu));
	opencl();
	// opencl_init(game.gpu, &game);
	ft_init_window(game.sdl, WIN_W, WIN_H);

	ft_update(&game);
	// clReleaseMemObject(game.gpu->cl_bufferOut);
	// release_gpu(game.gpu);

	ft_exit(NULL);
}