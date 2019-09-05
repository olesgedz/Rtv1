/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/09/05 17:31:29 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>
#include "libsdl.h"
#include "libvect.h"
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
cl_ulong * get_random(cl_ulong * random)
{
	int i;
	i = -1;
	random = ft_memalloc(sizeof(cl_ulong) * WIN_H * WIN_W);
	srand(21);
	while (++i < WIN_H * WIN_W)
	{
		random[i] = rand(); 
	}
	return (random);
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
cl_float3 create_cfloat3 (float x, float y, float z)
{
	cl_float3 re;

	re.v4[0] = x;
	re.v4[1] = y;
	re.v4[2] = z;
	return re;
}


void initScene(t_obj* cpu_spheres, t_game *game)
{
	char						*name = "sviborg.bmp";
	char						*secname = "sun.bmp";
	char						*thirdname = "seamless_pawnment.bmp";
	char						*fourthname = "concrete.bmp";
	char						*fivename = "dead_soil.bmp";


	game->textures_num 			= 5;
	game->textures 				= (t_txture*)malloc(sizeof(t_txture) * game->textures_num);
	get_texture(name, &(game->textures[0]));
	get_texture(secname, &(game->textures[1]));
	get_texture(thirdname, &(game->textures[2]));
	get_texture(fourthname, &(game->textures[3]));
	get_texture(fivename, &(game->textures[4]));
	// left sphere
	cpu_spheres[0].radius   	= 0.1f;
	cpu_spheres[0].position 	= create_cfloat3 (-0.4f, 0.f, -0.1f);
	cpu_spheres[0].color    	= create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[0].v 			= create_cfloat3 (0.f, 1.0f, 0.0f);
	cpu_spheres[0].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[0].type 		= CYLINDER;
	cpu_spheres[0].reflection 	= 0.f;
	cpu_spheres[0].texture 		= 3;

	// right sphere
	cpu_spheres[1].radius   	= 0.16f;
	cpu_spheres[1].position 	= create_cfloat3 (0.0f, -0.f, 0.1f);
	cpu_spheres[1].color    	= create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[1].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[1].v 			= create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[1].type 		= SPHERE;
	cpu_spheres[1].texture 		= 1;
	cpu_spheres[1].reflection 	= 0.f;

	// lightsource
	cpu_spheres[2].radius   	= 0.1f; 
	cpu_spheres[2].position 	= create_cfloat3 (0.0f, 0.2f, 1.0f);
	cpu_spheres[2].color    	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[2].emission 	= create_cfloat3 (40.0f, 40.0f, 40.0f);
	cpu_spheres[2].type 		= SPHERE;
	cpu_spheres[2].reflection 	= 0;
	cpu_spheres[2].texture 		= 2;

		// left wall
	cpu_spheres[6].radius		= 200.0f;
	cpu_spheres[6].position 	= create_cfloat3 (-1.0f, 0.0f, 0.0f);
	cpu_spheres[6].color    	= create_cfloat3 (0.75f, 0.25f, 0.25f);
	cpu_spheres[6].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[6].v 			= create_cfloat3 (1.0f, 0.0f, 0.0f);
	cpu_spheres[6].type 		= PLANE;
	cpu_spheres[6].reflection 	= 0;
	cpu_spheres[6].texture 		= 0;

	// right wall
	cpu_spheres[7].radius		= 200.0f;
	cpu_spheres[7].position 	= create_cfloat3 (1.f, 0.0f, 0.0f);
	cpu_spheres[7].color    	= create_cfloat3 (0.25f, 0.25f, 0.75f);
	cpu_spheres[7].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[7].v 			= create_cfloat3 (1.0f, 0.0f, 0.0f);
	cpu_spheres[7].type 		= PLANE;
	cpu_spheres[7].reflection 	= 0;
	cpu_spheres[7].texture 		= 0;

	// floor
	cpu_spheres[8].radius		= 200.0f;
	cpu_spheres[8].position 	= create_cfloat3 (0.0f, 0.5f, 0.0f);
	cpu_spheres[8].color		= create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[8].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[8].v 			= create_cfloat3 (0.0f, -1.0f, 0.0f);
	cpu_spheres[8].type 		= PLANE;
	cpu_spheres[8].reflection	= 0;
	cpu_spheres[8].texture 		= 4;
	// ceiling
	cpu_spheres[3].radius		= 200.0f;
	cpu_spheres[3].position 	= create_cfloat3 (0.0f, -0.5f, 0.0f);
	cpu_spheres[3].color		= create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[3].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[3].v 			= create_cfloat3 (0.0f, 1.0f, 0.0f);
	cpu_spheres[3].type 		= PLANE;
	cpu_spheres[3].reflection 	= 0;
	cpu_spheres[3].texture 		= 5;


	// back wall
	cpu_spheres[4].radius   	= 1.0f;
	cpu_spheres[4].position 	= create_cfloat3 (0.0f, 0.0f, -0.3f);
	cpu_spheres[4].color    	= create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[4].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[4].v 			= create_cfloat3 (0.0f, 0.0f, 1.0f);
	cpu_spheres[4].type 		= PLANE;
 	cpu_spheres[4].reflection 	= 0;
	cpu_spheres[4].reflection 	= 0;
	cpu_spheres[4].texture 		= 4;


	// front wall 
	cpu_spheres[5].radius   	= 200.0f;
	cpu_spheres[5].position 	= create_cfloat3 (0.0f, 0.0f, 2.0f);
	cpu_spheres[5].color    	= create_cfloat3 (0.9f, 0.8f, 0.7f);
	cpu_spheres[5].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	cpu_spheres[5].v 			= create_cfloat3 (0.0f, 0.0f, 1.0f);
	cpu_spheres[5].type 		= PLANE;
	cpu_spheres[5].reflection 	= 0;
	cpu_spheres[5].texture 		= 0;
}

 void ft_run_kernel(cl_kernel kernel)
 {
	 int w = WIN_W;
	int h = WIN_H;
	size_t global = WIN_W * WIN_H;
	int n_objects = 9;
	game.gpu->samples += 15;
	const int count = global;
	game.cl_info->ret |= clSetKernelArg(kernel, 5, sizeof(cl_int), &w);
	ERROR(game.cl_info->ret);
	game.cl_info->ret |= clSetKernelArg(kernel, 6, sizeof(cl_int), &h);
	ERROR(game.cl_info->ret);
	game.cl_info->ret |= clSetKernelArg(kernel, 7, sizeof(cl_int), &n_objects);
	ERROR(game.cl_info->ret);
	game.cl_info->ret |= clSetKernelArg(kernel, 8, sizeof(cl_int), &game.gpu->samples);
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



void opencl()
{
	game.kernels = ft_memalloc(sizeof(t_cl_krl) * 2);
	game.cl_info = ft_memalloc(sizeof(t_cl_info));
	game.gpuOutput = ft_memalloc(sizeof(int) * WIN_H * WIN_W);
	game.gpu->spheres = ft_memalloc(sizeof(t_obj) * 9);
	game.gpu->vec_temp = ft_memalloc(sizeof(cl_float3) * WIN_H * WIN_W);
	game.gpu->random = get_random(game.gpu->random);
	game.gpu->samples = 15;
	cl_mem			textures;
	initScene(game.gpu->spheres, &game);
	cl_init(game.cl_info);
	ERROR(game.cl_info->ret);
	int fd = open("srcs/cl_files/main.cl", O_RDONLY);
	size_t global = WIN_W * WIN_H;
	cl_krl_init(&game.kernels[0], 5);
	t_vect options;
	vect_init(&options);
	VECT_STRADD(&options, "-I srcs/cl_files/ -I includes/cl_headers/");
	game.kernels[0].sizes[0] = sizeof(cl_int) * WIN_H * WIN_W;
	game.kernels[0].sizes[1] =  sizeof(t_obj) * 9;
	game.kernels[0].sizes[2] = sizeof(cl_float3) * WIN_H * WIN_W;
	game.kernels[0].sizes[3] = WIN_H * WIN_W * sizeof(cl_ulong);
	game.kernels[0].sizes[4] = sizeof(t_txture) * game.textures_num;

	t_vect names;
	vect_init(&names);
	VECT_STRADD(&names, "render_kernel");
	game.cl_info->ret = cl_krl_build(game.cl_info, game.kernels, fd, &options, &names);
	ERROR(game.cl_info->ret);
	game.cl_info->ret = cl_write(game.cl_info, game.kernels[0].args[0], sizeof(cl_int) * WIN_H * WIN_W, game.gpuOutput);
	ERROR(game.cl_info->ret);
	game.cl_info->ret = cl_write(game.cl_info, game.kernels[0].args[1], sizeof(t_obj) * 9, game.gpu->spheres);
	ERROR(game.cl_info->ret);
	game.cl_info->ret = cl_write(game.cl_info, game.kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game.gpu->vec_temp);
	ERROR(game.cl_info->ret);
	game.cl_info->ret = cl_write(game.cl_info, game.kernels[0].args[3], WIN_H * WIN_W * sizeof(cl_ulong), game.gpu->random);
	ERROR(game.cl_info->ret);
	game.cl_info->ret = cl_write(game.cl_info, game.kernels[0].args[4], sizeof(t_txture) * game.textures_num, game.textures);
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
	// clReleaseMemObject(game.gpu->cl_bufferOut);
	// release_gpu(game.gpu);

	ft_exit(NULL);
}