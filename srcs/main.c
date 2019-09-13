/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/09/13 22:14:52 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>
#include "libsdl.h"
#include "libvect.h"
#define SAMPLES 5
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

void	camera_reposition(t_game *game, SDL_Keycode sym)
{
	// game->gpu->vec_temp = ft_memset(game->gpuOutput, 0, sizeof(cl_float3) * game->image->height * game->image->width);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game->gpu->vec_temp);
	ERROR(game->cl_info->ret);
	game->gpu->samples = 0;
	switch (sym)
	{
		case 'w':  game->gpu->camera[game->cam_num].position = sum_cfloat3(game->gpu->camera[game->cam_num].position, mult_cfloat3(game->gpu->camera[game->cam_num].direction, 0.1)); reconfigure_camera( &game->gpu->camera[game->cam_num]); break;
		case 's':  game->gpu->camera[game->cam_num].position = sum_cfloat3(game->gpu->camera[game->cam_num].position, mult_cfloat3(game->gpu->camera[game->cam_num].direction, -0.1)); reconfigure_camera( &game->gpu->camera[game->cam_num]); break;
		case 'a':  game->gpu->camera[game->cam_num].position = sum_cfloat3(game->gpu->camera[game->cam_num].position, mult_cfloat3(normalize(cross(game->gpu->camera[game->cam_num].normal, game->gpu->camera[game->cam_num].direction)), 0.1)); reconfigure_camera( &game->gpu->camera[game->cam_num]); break;
		case 'd':  game->gpu->camera[game->cam_num].position = sum_cfloat3(game->gpu->camera[game->cam_num].position, mult_cfloat3(normalize(cross(game->gpu->camera[game->cam_num].normal, game->gpu->camera[game->cam_num].direction)), -0.1)); reconfigure_camera( &game->gpu->camera[game->cam_num]); break;
		case 'q':  game->gpu->camera[game->cam_num].direction = rotate(game->gpu->camera[game->cam_num].normal, game->gpu->camera[game->cam_num].direction, M_PI / 60); reconfigure_camera( &game->gpu->camera[game->cam_num]); break;
		case 'e':  game->gpu->camera[game->cam_num].direction = rotate(game->gpu->camera[game->cam_num].normal, game->gpu->camera[game->cam_num].direction, -M_PI / 60); reconfigure_camera( &game->gpu->camera[game->cam_num]); break;
		case 'z':  game->gpu->camera[game->cam_num].position = sum_cfloat3(game->gpu->camera[game->cam_num].position, mult_cfloat3(game->gpu->camera[game->cam_num].normal, 0.1)); reconfigure_camera( &game->gpu->camera[game->cam_num]); break;
		case 'x':  game->gpu->camera[game->cam_num].position = sum_cfloat3(game->gpu->camera[game->cam_num].position, mult_cfloat3(game->gpu->camera[game->cam_num].normal, -0.1)); reconfigure_camera( &game->gpu->camera[game->cam_num]); break;
		default: break;
	}
}

int		ft_input_keys(void *game1, SDL_Event *ev)
{
	t_game *game = game1;
	switch (ev->type)
		{
			//case SDL_KEYDOWN:
			case SDL_KEYDOWN:
				camera_reposition(game, ev->key.keysym.sym);
				switch (ev->key.keysym.sym)
				{
					case SDLK_LCTRL:
					case SDLK_RCTRL:
					case SDLK_ESCAPE: ft_exit(NULL); break;
					case 's': game->wsad[1] = ev->type==SDL_KEYDOWN; break;
					case 'a': game->wsad[2] = ev->type==SDL_KEYDOWN; break;
					case 'd': game->wsad[3] = ev->type==SDL_KEYDOWN; break;
					case 'q': game->wsad[4] = ev->type==SDL_KEYDOWN; break;
					case 'e': game->wsad[5] = ev->type==SDL_KEYDOWN; break;
					case 'w': game->wsad[0] = ev->type==SDL_KEYDOWN; break;
					case 'z': game->wsad[6] = ev->type==SDL_KEYDOWN; break;
					case 'x': game->wsad[7] = ev->type==SDL_KEYDOWN; break;
					case ',': game->wsad[8] = ev->type==SDL_KEYDOWN;
					game->gpu->samples = SAMPLES;
					// game->gpu->vec_temp = ft_memset(game->gpuOutput, 0, sizeof(cl_float3) * game->image->height * game->image->width);
					game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game->gpu->vec_temp);

					game->cam_num--;
					if (game->cam_num < 0)
						game->cam_num = game->cam_quantity - 1;
					break;
					case '.': game->wsad[9] = ev->type==SDL_KEYDOWN;
					game->gpu->samples = 5;
					// game->gpu->vec_temp = ft_memset(game->gpuOutput, 0, sizeof(cl_float3) * game->image->height * game->image->width);
					game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game->gpu->vec_temp);

					game->cam_num++;
					if (game->cam_num >= game->cam_quantity)
						game->cam_num = 0;
					break;
					default: break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN: game->mouse = !game->mouse;
				break;
			case SDL_MOUSEBUTTONUP: game->mouse = !game->mouse;
				break;
			case SDL_MOUSEMOTION:
			if (game->mouse != 0)
			{
				game->gpu->samples = SAMPLES;
				// game->gpu->vec_temp = ft_memset(game->gpuOutput, 0, sizeof(cl_float3) * game->image->height * game->image->width);
				game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game->gpu->vec_temp);
				rotate_horizontal(&(game->gpu->camera[game->cam_num]), game->gpu->camera[game->cam_num].fov / WIN_W * ev->motion.xrel);
				rotate_vertical(&(game->gpu->camera[game->cam_num]), game->gpu->camera[game->cam_num].fov /WIN_H * -ev->motion.yrel);
				reconfigure_camera( &game->gpu->camera[game->cam_num]);
			}
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
	char						*name = "sobenin.bmp";
	char						*secname = "sun.bmp";
	char						*thirdname = "seamless_pawnment.bmp";
	char						*fourthname = "concrete.bmp";
	char						*fivename = "ice.bmp";
	char						*sixname = "stars.bmp";

	game->textures_num 			= 6;
	game->textures 				= (t_txture*)malloc(sizeof(t_txture) * game->textures_num);
	game->gpu->camera			= NULL;
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
	game->gpu->samples += SAMPLES;
	const size_t count = global;
	game->cl_info->ret |= clSetKernelArg(kernel, 5, sizeof(cl_int), &w);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 6, sizeof(cl_int), &h);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 7, sizeof(cl_int), &game->obj_quantity);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 8, sizeof(cl_int), &game->gpu->samples);
	ERROR(game->cl_info->ret);
	game->cl_info->ret |= clSetKernelArg(kernel, 9, sizeof(t_cam), &game->gpu->camera[game->cam_num]);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_krl_exec(game->cl_info, kernel, 1, &global);
	ERROR(game->cl_info->ret);
	clFinish(game->cl_info->cmd_queue);
	game->cl_info->ret = cl_read(game->cl_info, game->kernels->args[0], sizeof(cl_int) * count, game->gpuOutput);
	ERROR(game->cl_info->ret);
 }

int blur_extent = 0;


void blur(t_surface * surface) //This manipulates with SDL_Surface and gives it box blur effect
{


	for( int j = 0; j < surface->height; j++)
	{
			for( int k = 0; k < surface->width; k++)
			{
				printf("fuck You !\n");
			}
	}

}


/*
*	Fucntion: render all pixels on the surface
*	Parameters: game, sdl
*	Return: none
* when
*/
void 	ft_render(t_game* game)
{
	int		i;
	int		j;
	int width = game->sdl.surface->width;
	int height = game->sdl.surface->height;
	j = -1;
	int r = rand() % 2;
	printf("%d\n", r);
	ft_run_kernel(game, game->kernels[0].krl);
	game->sdl.surface->data =  (Uint32 *)game->gpuOutput;
	//blur(game->sdl.surface);
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
	ft_surface_clear(game->sdl.surface);
	while(TRUE)
	{
		current_ticks = clock();

		ft_input(game, &ft_input_keys);
		if (game->init_render || game->wsad[0] || game->wsad[1] ||
			game->wsad[2] || game->wsad[3] || game->wsad[4] || game->wsad[5] ||
			game->wsad[6] || game->wsad[7] || game->wsad[8] || game->wsad[9] || game->mouse)
			{
				game->init_render = 0;
				ft_memset(game->wsad, 0, sizeof(game->wsad));
				ft_render(game);
				ft_surface_present(&game->sdl, game->sdl.surface);
			}
	#ifdef FPS
				 delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
    if(delta_ticks > 0)
        fps = CLOCKS_PER_SEC / delta_ticks;

			printf("fps :%lu\n", fps);
	#endif
	//SDL_Delay(5);
	}
}

void opencl(t_game *game, char *argv)
{
	game->kernels = ft_memalloc(sizeof(t_cl_krl) * 2);
	game->cl_info = ft_memalloc(sizeof(t_cl_info));
	game->gpuOutput = ft_memalloc(sizeof(int) * WIN_H * WIN_W);
	// game->gpu->objects = ft_memalloc(sizeof(t_obj) * 9);
	game->gpu->objects = NULL;
	game->gpu->vec_temp = ft_memalloc(sizeof(cl_float3) * WIN_H * WIN_W);
	game->gpu->random = get_random(game->gpu->random);
	game->gpu->samples = 0;
	game->cam_num = 0;
	cl_mem			textures;
	initScene(game->gpu->objects, game, argv);
	cl_init(game->cl_info);
	ERROR(game->cl_info->ret);
	int fd = open("srcs/cl_files/main.cl", O_RDONLY);
	size_t global = WIN_W * WIN_H;
	cl_krl_init(&game->kernels[0], 5);
	t_vect options;
	vect_init(&options);
	VECT_STRADD(&options, "-w -I srcs/cl_files/ -I includes/cl_headers/");
	game->kernels[0].sizes[0] = sizeof(cl_int) * WIN_H * WIN_W;
	game->kernels[0].sizes[1] =  sizeof(t_obj) * game->obj_quantity;
	game->kernels[0].sizes[2] = sizeof(cl_float3) * WIN_H * WIN_W;
	game->kernels[0].sizes[3] = WIN_H * WIN_W * sizeof(cl_ulong);
	game->kernels[0].sizes[4] = sizeof(t_txture) * game->textures_num;

	t_vect names;
	vect_init(&names);
	VECT_STRADD(&names, "render_kernel");
	game->cl_info->ret = cl_krl_build(game->cl_info, game->kernels, fd, &options, &names);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[0], sizeof(cl_int) * WIN_H * WIN_W, game->gpuOutput);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[1], sizeof(t_obj) * game->obj_quantity, game->gpu->objects);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game->gpu->vec_temp);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[3], WIN_H * WIN_W * sizeof(cl_ulong), game->gpu->random);
	ERROR(game->cl_info->ret);
	game->cl_info->ret = cl_write(game->cl_info, game->kernels[0].args[4], sizeof(t_txture) * game->textures_num, game->textures);
	ERROR(game->cl_info->ret);
}



int	main(int argc, char **argv)
{
	t_game game;
	game.image = ft_surface_create(WIN_W, WIN_H);
	game.init_render = 1;
	game.origin = (t_vec3){0,0,5};
	game.gpu = (t_gpu *)malloc(sizeof(t_gpu));
	game.mouse = 0;
	ft_init_window(&game.sdl, WIN_W, WIN_H);
	game.quit = 0;
	g_game(&game, 1);
	if (argc != 2)
		start_screen(&game);
	else
		game.av = argv[1];
	opencl(&game, game.av);
	ft_update(&game);
	clReleaseMemObject(game.gpu->cl_bufferOut);
	//release_gpu(game.gpu);
	quit_kiwi(&game);
	ft_exit(NULL);
}
