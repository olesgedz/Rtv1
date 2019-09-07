/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: srobert- <srobert-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/09/07 21:54:06 by srobert-         ###   ########.fr       */
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

void	camera_reposition(SDL_Keycode sym)
{
	game.gpu->vec_temp = ft_memset(game.gpuOutput, 0, sizeof(cl_float3) * game.image->height * game.image->width);
	game.cl_info->ret = cl_write(game.cl_info, game.kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game.gpu->vec_temp);
	ERROR(game.cl_info->ret);
	game.gpu->samples = 0;
	switch (sym)
	{
		case 'w':  game.gpu->camera[game.cam_num].position = sum_cfloat3(game.gpu->camera[game.cam_num].position, mult_cfloat3(game.gpu->camera[game.cam_num].direction, 0.1)); break;
		case 's':  game.gpu->camera[game.cam_num].position = sum_cfloat3(game.gpu->camera[game.cam_num].position, mult_cfloat3(game.gpu->camera[game.cam_num].direction, -0.1)); break;
		case 'a':  game.gpu->camera[game.cam_num].position = sum_cfloat3(game.gpu->camera[game.cam_num].position, mult_cfloat3(normalize(cross(game.gpu->camera[game.cam_num].normal, game.gpu->camera[game.cam_num].direction)), 0.1)); break;
		case 'd':  game.gpu->camera[game.cam_num].position = sum_cfloat3(game.gpu->camera[game.cam_num].position, mult_cfloat3(normalize(cross(game.gpu->camera[game.cam_num].normal, game.gpu->camera[game.cam_num].direction)), -0.1)); break;
		case 'q':  game.gpu->camera[game.cam_num].direction = rotate(game.gpu->camera[game.cam_num].normal, game.gpu->camera[game.cam_num].direction, M_PI / 60); reconfigure_camera(&game.gpu->camera[game.cam_num]); break;
		case 'e':  game.gpu->camera[game.cam_num].direction = rotate(game.gpu->camera[game.cam_num].normal, game.gpu->camera[game.cam_num].direction, -M_PI / 60); reconfigure_camera(&game.gpu->camera[game.cam_num]); break;
		case 'z':  break;
		case 'x':  break;
		default: break;
	}
}

int		ft_input_keys(void *sdl, SDL_Event *ev)
{
	switch (ev->type)
		{
			case SDL_KEYDOWN:
				switch (ev->key.keysym.sym)
				{
					case SDLK_LCTRL:
					case SDLK_RCTRL:
					case SDLK_ESCAPE: ft_exit(NULL); break;
					case 'w': game.wsad[0] = ev->type==SDL_KEYDOWN; camera_reposition(ev->key.keysym.sym); break;
					case 's': game.wsad[1] = ev->type==SDL_KEYDOWN; camera_reposition(ev->key.keysym.sym); break;
					case 'a': game.wsad[2] = ev->type==SDL_KEYDOWN; camera_reposition(ev->key.keysym.sym); break;
					case 'd': game.wsad[3] = ev->type==SDL_KEYDOWN; camera_reposition(ev->key.keysym.sym); break;
					case 'q': game.wsad[4] = ev->type==SDL_KEYDOWN; camera_reposition(ev->key.keysym.sym); break;
					case 'e': game.wsad[5] = ev->type==SDL_KEYDOWN; camera_reposition(ev->key.keysym.sym); break;
					case 'z': game.wsad[6] = ev->type==SDL_KEYDOWN; break;
					case 'x': game.wsad[7] = ev->type==SDL_KEYDOWN; break;
					case ',': game.wsad[8] = ev->type==SDL_KEYDOWN;
					game.gpu->samples = 5;
					game.gpu->vec_temp = ft_memset(game.gpuOutput, 0, sizeof(cl_float3) * game.image->height * game.image->width);
					game.cl_info->ret = cl_write(game.cl_info, game.kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game.gpu->vec_temp);

					game.cam_num--;
					if (game.cam_num < 0)
						game.cam_num = game.cam_quantity - 1; 
					break;
					case '.': game.wsad[9] = ev->type==SDL_KEYDOWN;
					game.gpu->samples = 5;
					game.gpu->vec_temp = ft_memset(game.gpuOutput, 0, sizeof(cl_float3) * game.image->height * game.image->width);
					game.cl_info->ret = cl_write(game.cl_info, game.kernels[0].args[2], sizeof(cl_float3) * WIN_H * WIN_W, game.gpu->vec_temp);

					game.cam_num++;
					if (game.cam_num >= game.cam_quantity)
						game.cam_num = 0; 
					break;
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



t_cam			*init_camera(void)
{
	t_cam		*camera;

	camera = (t_cam*)malloc(sizeof(t_cam));
	camera->normal = create_cfloat3 (0.0f, 1.0f, 0.0f);
	camera->direction = create_cfloat3 (0.0f, 0.0f, -1.0f);
	camera->position = create_cfloat3 (0.0f, 0.1f, 2.f);
	camera->fov = M_PI / 3;
	reconfigure_camera(camera);
	return (camera);
}

void initScene(t_obj* objects, t_game *game, char **argv)
{
	char						*name = "sobenin.bmp";
	char						*secname = "sun.bmp";
	char						*thirdname = "seamless_pawnment.bmp";
	char						*fourthname = "concrete.bmp";
	char						*fivename = "ice.bmp";


	game->textures_num 			= 5;
	game->textures 				= (t_txture*)malloc(sizeof(t_txture) * game->textures_num);
	game->gpu->camera			= NULL;
	get_texture(name, &(game->textures[0]));
	get_texture(secname, &(game->textures[1]));
	get_texture(thirdname, &(game->textures[2]));
	get_texture(fourthname, &(game->textures[3]));
	get_texture(fivename, &(game->textures[4]));
	read_scene(argv, game);
	// // left sphere
	// objects[0].radius   	= 0.1f;
	// objects[0].position 	= create_cfloat3 (-0.4f, 0.f, -0.1f);
	// objects[0].color    	= create_cfloat3 (0.9f, 0.8f, 0.7f);
	// objects[0].v 			= create_cfloat3 (0.f, 1.0f, 0.0f);
	// objects[0].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	// objects[0].type 		= CYLINDER;
	// objects[0].reflection 	= 0.f;
	// objects[0].texture 		= 3;

	// // right sphere
	// objects[1].radius   	= 0.16f;
	// objects[1].position 	= create_cfloat3 (0.0f, -0.f, 0.1f);
	// objects[1].color    	= create_cfloat3 (0.9f, 0.8f, 0.7f);
	// objects[1].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	// objects[1].v 			= create_cfloat3 (0.0f, 0.0f, 0.0f);
	// objects[1].type 		= SPHERE;
	// objects[1].texture 		= 1;
	// objects[1].reflection 	= 0.f;

	// // lightsource
	// objects[2].radius   	= 0.1f; 
	// objects[2].position 	= create_cfloat3 (0.0f, 0.2f, 1.0f);
	// objects[2].color    	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	// objects[2].emission 	= create_cfloat3 (40.0f, 40.0f, 40.0f);
	// objects[2].type 		= SPHERE;
	// objects[2].reflection 	= 0;
	// objects[2].texture 		= 2;

	// 	// left wall
	// objects[6].radius		= .0f;
	// objects[6].position 	= create_cfloat3 (-1.0f, 0.0f, 0.0f);
	// objects[6].color    	= create_cfloat3 (0.75f, 0.25f, 0.25f);
	// objects[6].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	// objects[6].v 			= create_cfloat3 (1.0f, 0.0f, 0.0f);
	// objects[6].type 		= PLANE;
	// objects[6].reflection 	= 0;
	// objects[6].texture 		= 0;

	// // right wall
	// objects[7].radius		= 200.0f;
	// objects[7].position 	= create_cfloat3 (1.f, 0.0f, 0.0f);
	// objects[7].color    	= create_cfloat3 (0.25f, 0.25f, 0.75f);
	// objects[7].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	// objects[7].v 			= create_cfloat3 (1.0f, 0.0f, 0.0f);
	// objects[7].type 		= PLANE;
	// objects[7].reflection 	= 0;
	// objects[7].texture 		= 0;

	// // floor
	// objects[8].radius		= 0.0f;
	// objects[8].position 	= create_cfloat3 (0.0f, 0.5f, 0.0f);
	// objects[8].color		= create_cfloat3 (0.9f, 0.8f, 0.7f);
	// objects[8].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	// objects[8].v 			= create_cfloat3 (0.0f, -1.0f, 0.0f);
	// objects[8].type 		= PLANE;
	// objects[8].reflection	= 0;
	// objects[8].texture 		= 4;
	// // ceiling
	// objects[3].radius		= 200.0f;
	// objects[3].position 	= create_cfloat3 (0.0f, -0.5f, 0.0f);
	// objects[3].color		= create_cfloat3 (0.9f, 0.8f, 0.7f);
	// objects[3].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	// objects[3].v 			= create_cfloat3 (0.0f, 1.0f, 0.0f);
	// objects[3].type 		= PLANE;
	// objects[3].reflection 	= 0;
	// objects[3].texture 		= 5;


	// // back wall
	// objects[4].radius   	= 1.0f;
	// objects[4].position 	= create_cfloat3 (0.0f, 0.0f, -0.3f);
	// objects[4].color    	= create_cfloat3 (0.9f, 0.8f, 0.7f);
	// objects[4].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	// objects[4].v 			= create_cfloat3 (0.0f, 0.0f, 1.0f);
	// objects[4].type 		= PLANE;
 	// objects[4].reflection 	= 0;
	// objects[4].reflection 	= 0;
	// objects[4].texture 		= 4;


	// // front wall 
	// objects[5].radius   	= 200.0f;
	// objects[5].position 	= create_cfloat3 (0.0f, 0.0f, 2.0f);
	// objects[5].color    	= create_cfloat3 (0.9f, 0.8f, 0.7f);
	// objects[5].emission 	= create_cfloat3 (0.0f, 0.0f, 0.0f);
	// objects[5].v 			= create_cfloat3 (0.0f, 0.0f, 1.0f);
	// objects[5].type 		= PLANE;
	// objects[5].reflection 	= 0;
	// objects[5].texture 		= 0;
}

 void ft_run_kernel(cl_kernel kernel)
 {
	int w = WIN_W;
	int h = WIN_H;
	size_t global = WIN_W * WIN_H;
	game.gpu->samples += 5;
	const size_t count = global;
	game.cl_info->ret |= clSetKernelArg(kernel, 5, sizeof(cl_int), &w);
	ERROR(game.cl_info->ret);
	game.cl_info->ret |= clSetKernelArg(kernel, 6, sizeof(cl_int), &h);
	ERROR(game.cl_info->ret);
	game.cl_info->ret |= clSetKernelArg(kernel, 7, sizeof(cl_int), &game.obj_quantity);
	ERROR(game.cl_info->ret);
	game.cl_info->ret |= clSetKernelArg(kernel, 8, sizeof(cl_int), &game.gpu->samples);
	ERROR(game.cl_info->ret);
	game.cl_info->ret |= clSetKernelArg(kernel, 9, sizeof(t_cam), &game.gpu->camera[game.cam_num]);
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
	int r = rand() % 2;
	printf("%d\n", r);
	ft_run_kernel(game->kernels[0].krl);
	while (++j < height)
	{
		i = -1;
		while (++i < width)	
			game->sdl->surface->data[i+j*width] =  game->gpuOutput[i+ j *width];
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
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	while(TRUE)
	{
		current_ticks = clock();
	//	printf("%d cam num\n", game->cam_num);
		ft_surface_clear(game->sdl->surface);
		ft_input(game->sdl, &ft_input_keys);
		if (game->init_render || game->wsad[0] || game->wsad[1] ||
			game->wsad[2] || game->wsad[3] || game->wsad[4] || game->wsad[5] ||
			game->wsad[6] || game->wsad[7] || game->wsad[8] || game->wsad[9] )
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
	//SDL_Delay(5);
	}
}

void opencl(char **argv)
{
	game.kernels = ft_memalloc(sizeof(t_cl_krl) * 2);
	game.cl_info = ft_memalloc(sizeof(t_cl_info));
	game.gpuOutput = ft_memalloc(sizeof(int) * WIN_H * WIN_W);
	// game.gpu->objects = ft_memalloc(sizeof(t_obj) * 9);
	game.gpu->objects = NULL;
	game.gpu->vec_temp = ft_memalloc(sizeof(cl_float3) * WIN_H * WIN_W);
	game.gpu->random = get_random(game.gpu->random);
	game.gpu->samples = 0;
	game.cam_num = 0;	
	cl_mem			textures;
	initScene(game.gpu->objects, &game, argv);
	cl_init(game.cl_info);
	ERROR(game.cl_info->ret);
	int fd = open("srcs/cl_files/main.cl", O_RDONLY);
	size_t global = WIN_W * WIN_H;
	cl_krl_init(&game.kernels[0], 5);
	t_vect options;
	vect_init(&options);
	VECT_STRADD(&options, "-w -I srcs/cl_files/ -I includes/cl_headers/");
	game.kernels[0].sizes[0] = sizeof(cl_int) * WIN_H * WIN_W;
	game.kernels[0].sizes[1] =  sizeof(t_obj) * game.obj_quantity;
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
	game.cl_info->ret = cl_write(game.cl_info, game.kernels[0].args[1], sizeof(t_obj) * game.obj_quantity, game.gpu->objects);
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
	opencl(argv);
	ft_init_window(game.sdl, WIN_W, WIN_H);

	ft_update(&game);
	clReleaseMemObject(game.gpu->cl_bufferOut);
	//release_gpu(game.gpu);

	ft_exit(NULL);
}