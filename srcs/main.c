/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/09/22 13:54:29 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>
#include "libsdl.h"
#include "libvect.h"
/*
* ! We can't use global variables
*/

//#define FPS

/*
*	Funtion: handles presses mouse/keyboard
* 	Return: value, doesnt change any parameters
*
*	- can handle multiple presses at once
*	- that goes into libsdl void ft_input(void *main, int (*f)(void *main, SDL_Event *ev))
*/

static float u_clamp(float x)
{
	return x < 0.0f ? 0.0f : x > 1.0f ? 1.0f : x;
}

static int toInt(float x)
{
	return (int)(u_clamp(x) * 255);
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

t_cam			*init_camera(t_game *game)
{
	t_cam		*camera;

	camera = (t_cam*)malloc(sizeof(t_cam));
	camera->normal = create_cfloat3 (0.0f, 1.0f, 0.0f);
	camera->direction = create_cfloat3 (0.0f, 0.0f, -1.0f);
	camera->position = create_cfloat3 (0.0f, 0.1f, 2.f);
	camera->fov = M_PI / 3;
	reconfigure_camera( camera);
	return (camera);
}

void initScene(t_obj* objects, t_game *game, char *argv)
{
	char						*name = "sobenin.jpg";
	char						*secname = "sun.bmp";
	char						*thirdname = "seamless_pawnment.bmp";
	char						*fourthname = "grass_rock.bmp";
	char						*fivename = "ice.bmp";
	char						*sixname = "stars.bmp";

	game->textures_num 			= 6;
	game->textures 				= (t_txture*)malloc(sizeof(t_txture) * game->textures_num);
	game->gpu.camera			= NULL;
	get_texture(name, &(game->textures[0]));
	get_texture(secname, &(game->textures[1]));
	get_texture(thirdname, &(game->textures[2]));
	get_texture(fourthname, &(game->textures[3]));
	get_texture(fivename, &(game->textures[4]));
	get_texture(sixname, &(game->textures[5]));
	read_scene(argv, game);
}

 void ft_run_kernel(t_game *game, cl_kernel kernel)
 {
	int w = WIN_W;
	int h = WIN_H;
	size_t global = WIN_W * WIN_H;
	game->gpu.samples += SAMPLES;
	const size_t count = global;
	game->cl_info->ret |= clSetKernelArg(kernel, 5, sizeof(cl_int), &w);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 6, sizeof(cl_int), &h);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 7, sizeof(cl_int), &game->obj_quantity);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 8, sizeof(cl_int), &game->gpu.samples);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 9, sizeof(t_cam), &game->gpu.camera[game->cam_num]);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_krl_exec(game->cl_info, kernel, 1, &global);
	ERROR(game->cl_info->ret);
	clFinish(game->cl_info->cmd_queue);
	game->cl_info->ret = cl_read(game->cl_info, game->kernels->args[0], sizeof(cl_int) * count, game->gpuOutput);
	ERROR(game->cl_info->ret);
 }

/*
*	Fucntion: render all pixels on the surface
*	Parameters: game, sdl
*	Return: none
* when
*/
void 	ft_render(t_game* game)
{
	if(!game->flag)
		return ;
	game->flag = 0;
	ft_run_kernel(game, game->kernels[0].krl);
	game->sdl.surface->data =  (Uint32 *)game->gpuOutput;
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

void poopa(t_game *game)
{
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	ft_surface_clear(game->sdl.surface);
	while(!game->quit)
	{
		key_check(game);
		camera_reposition(game);
		ft_render(game);
		ft_surface_present(&game->sdl, game->sdl.surface);
	}
}

void opencl(t_game *game, char *argv)
{
	game->kernels = ft_memalloc(sizeof(t_cl_krl) * 2);
	game->cl_info = ft_memalloc(sizeof(t_cl_info));
	game->gpuOutput = ft_memalloc(sizeof(int) * WIN_H * WIN_W);
	// game->gpu.objects = ft_memalloc(sizeof(t_obj) * 9);
	game->gpu.objects = NULL;
	game->gpu.vec_temp = ft_memalloc(sizeof(cl_float3) * WIN_H * WIN_W);
	game->gpu.random = get_random(game->gpu.random);
	game->gpu.samples = 0;
	game->cam_num = 0;
	cl_mem			textures;
	initScene(game->gpu.objects, game, argv);
	cl_init(game->cl_info);
	ERROR(game->cl_info->ret);
	int fd = open("srcs/cl_files/main.cl", O_RDONLY);
	size_t global = WIN_W * WIN_H;
	cl_krl_init(&game->kernels[0], 5);
	game->kernels[0].sizes[0] = sizeof(cl_int) * WIN_H * WIN_W;
	game->kernels[0].sizes[1] =  sizeof(t_obj) * game->obj_quantity;
	game->kernels[0].sizes[2] = sizeof(cl_float3) * WIN_H * WIN_W;
	game->kernels[0].sizes[3] = WIN_H * WIN_W * sizeof(cl_ulong);
	game->kernels[0].sizes[4] = sizeof(t_txture) * game->textures_num;

	t_vect names;
	vect_init(&names);
	VECT_STRADD(&names, "render_kernel");
	game->cl_info->ret = cl_krl_build(game->cl_info, game->kernels, fd, "-w -I srcs/cl_files/ -I includes/cl_headers/", &names);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[0], sizeof(cl_int) * WIN_H * WIN_W, game->gpuOutput);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[1], sizeof(t_obj) * game->obj_quantity, game->gpu.objects);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game->gpu.vec_temp);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[3], WIN_H * WIN_W * sizeof(cl_ulong), game->gpu.random);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[4], sizeof(t_txture) * game->textures_num, game->textures);
	ERROR(game->cl_info->ret);
}

int	main(int argc, char **argv)
{
	t_game	game;
	t_gui	gui;

	ft_init_window(&game.sdl, WIN_W, WIN_H);
	set_const(&game, &gui);
	if (argc != 2)
		game.av = start_gui(&gui);
	else
		game.av = argv[1];
	SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
	opencl(&game, game.av);
	game.quit = 0;
	poopa(&game);
//	clReleaseMemObject(game.gpu.cl_bufferOut);
	//release_gpu(game.gpu);
	ft_exit(NULL);
}
