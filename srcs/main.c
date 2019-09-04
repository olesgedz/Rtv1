/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olesgedz <olesgedz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/09/04 03:16:18 by olesgedz         ###   ########.fr       */
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


 void ft_run_kernel(cl_kernel kernel)
 {
	 int w = WIN_W;
	int h = WIN_H;
	size_t global = WIN_W * WIN_H;

	const int count = global;
	// game.cl_info->ret |= clSetKernelArg(kernel, 0, sizeof(cl_mem), &game.kernels->args[0]);
	// ERROR(game.cl_info->ret);
	game.cl_info->ret |= clSetKernelArg(kernel, 1, sizeof(cl_int), &w);
	ERROR(game.cl_info->ret);
	game.cl_info->ret |= clSetKernelArg(kernel, 2, sizeof(cl_int), &h);
	ERROR(game.cl_info->ret);
	game.cl_info->ret = cl_krl_exec(game.cl_info, kernel, 1, &global);
	ERROR(game.cl_info->ret);
	clFinish(game.cl_info->cmd_queue);
	game.cl_info->ret = cl_read(game.cl_info, game.kernels->args[0], sizeof(cl_int) * count, game.gpuOutput);
	ERROR(game.cl_info->ret);
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
	int r = rand() % 2;
	printf("%d\n", r);
	ft_run_kernel(game->kernels[0].krl);
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

// #include "libft.h"
// #include "malloc.h"
// #include "libgnl.h"
// #include "libcl.h"
// #include <stdio.h>
// #define LOG_BUFSIZ 20480

// static cl_int
// 	krl_set_args
// 	(cl_context ctxt
// 	, t_cl_krl *krl)
// {
// 	cl_int		ret;
// 	size_t		i;

// 	i = 0;
// 	while (i < krl->nargs)
// 	{
// 		krl->args[i] = clCreateBuffer(ctxt, 0, krl->sizes[i], NULL, &ret);
// 		if (ret != CL_SUCCESS)
// 			return (ret);
// 		if ((ret = CL_KRL_ARG(krl->krl, i, krl->args[i])) != CL_SUCCESS)
// 			return (ret);
// 		i++;
// 	}
// 	return (CL_SUCCESS);
// }

// static void
// 	krl_get_opts
// 	(t_vect *build_line
// 	, char **opts)
// {

// 	*opts = build_line->data;
// }
// static void
// 	krl_source_free
// 	(t_vect lines
// 	)
// {
// 	size_t	i;
// 	i = 0;
// 	while (i < lines.used / 8)
// 	{
// 		free(((char **)lines.data)[i]);
// 		i++;
// 	}
// 	free(lines.data);
// }

// cl_int
// 	cl_krl_build
// 	(t_cl_info *cl
// 	, t_cl_krl *krl
// 	, int fd
// 	, t_vect *build_line, t_vect *kernel_names)
// {
// 	char		*krlname;
// 	char		buffer[LOG_BUFSIZ];
// 	cl_int		ret;
// 	t_vect		lines;
// 	int i;
// 	i = -1;
// 	unsigned char **names;
// 	names = VSPLIT(*kernel_names,":");
	
// 	vect_init(&lines);
// 	gnl_lines(fd, &lines, GNL_APPEND_CHAR);
// 	cl->prog = clCreateProgramWithSource(cl->ctxt, lines.used / sizeof(void *),
// 		(const char **)lines.data, NULL, &ret);
// 	if (ret != CL_SUCCESS)
// 		return (ret);
// 	if ((ret = clBuildProgram(cl->prog,
// 		cl->dev_num, &cl->dev_id, "-w", NULL, NULL)) != CL_SUCCESS)
// 	{
// 		clGetProgramBuildInfo(cl->prog, cl->dev_id, CL_PROGRAM_BUILD_LOG
// 			, LOG_BUFSIZ, buffer, NULL);
// 		write(1, buffer, ft_strlen(buffer));
// 		return (ret);
// 	}
// 	while((char *)names[++i])
// 	{
// 		if (!(krl[i].krl = clCreateKernel(cl->prog, (char *)names[i], &ret)))
// 			return (ret);
// 		ret = krl_set_args(cl->ctxt, &krl[i]);
// 	}
// 	krl_source_free(lines);
// 	return (ret);
// }



void opencl()
{
	game.kernels = ft_memalloc(sizeof(t_cl_krl) * 2);
	game.cl_info = ft_memalloc(sizeof(t_cl_info));
	game.gpuOutput = ft_memalloc(sizeof(int) * WIN_H * WIN_W);

	cl_init(game.cl_info);
	ERROR(game.cl_info->ret);
	int fd = open("srcs/cl_files/main.cl", O_RDONLY);
	size_t global = WIN_W * WIN_H;
	cl_krl_init(&game.kernels[0], 1);
	t_vect options;
	vect_init(&options);
	VECT_STRADD(&options, "-I srcs/cl_files/ -I includes/cl_headers/");
	game.kernels[0].sizes[0] = sizeof(cl_int) * WIN_H * WIN_W;
	// game.kernels[0].sizes[1] = sizeof(cl_int);
	// game.kernels[0].sizes[2] = sizeof(cl_int);
	
	t_vect names;
	vect_init(&names);
	VECT_STRADD(&names, "render_kernel");
	game.cl_info->ret = cl_krl_build(game.cl_info, game.kernels, fd, &options, &names);
	ERROR(game.cl_info->ret);
	game.cl_info->ret = cl_write(game.cl_info, game.kernels[0].args[0], sizeof(cl_int) * WIN_H * WIN_W, game.gpuOutput);
	ERROR(game.cl_info->ret);
}



int	main(int argc, char **argv)
{

	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	game.init_render = 1;
	game.origin = (t_vec3){0,0,5};
	game.gpu = (t_gpu *)malloc(sizeof(t_gpu));
	opencl();
	// opencl_init(game.gpu, &game);
	ft_init_window(game.sdl, WIN_W, WIN_H);

	ft_update(&game);
	clReleaseMemObject(game.gpu->cl_bufferOut);
	release_gpu(game.gpu);

	ft_exit(NULL);
}