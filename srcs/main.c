/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/11/15 18:12:21 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libgnl.h"
#include <unistd.h>
// static void	set_icon(t_gui *gui, const char *filename)
// {
// 	SDL_Surface		*surf;

// 	if (!(surf = IMG_Load(filename)))
// 	{
// 		print_error_gui("No picture for you: ", SDL_GetError());
// 		exit(1);
// 	}
// 	SDL_SetWindowIcon(gui->sdl.window, surf);
// 	SDL_FreeSurface(surf);
// }

// static void	main_loop(t_game *game, t_gui *gui, int argc)
// {
// 	KW_HideWidget(gui->s_s.frame);
// 	gui_bar(game, gui);
// 	while (game->av)
// 	{
// 		opencl(game, game->av);
// 		main_screen(gui, game);
// 		if (argc != 2)
// 			ft_strdel(&game->av);
// 		argc = 0;
// 		gui->av = 0;
// 		game->quit = 0;
// 		gui->quit = 0;
// 		game->flag = 1;
// 		main_render(game, gui);
// 		main_screen_free(gui);
// 	}
// }
cl_int  cl_krl_set_all_args(t_cl_krl *krl)
{
	cl_int	ret;
	int		i;

	ret = 0;
	i = 0;
	while (i < krl->nargs)
		cl_krl_set_arg(krl, i++);
	return (ret);
}
int			main(int argc, char **argv)
{
	t_game	game;
	t_gui	gui;

	gui.main_screen = 0;
	ft_init_window(&game.sdl, WIN_W, WIN_H);
	game.cl_info = ft_memalloc(sizeof(t_cl_info));
	game.cl_info->ret = cl_init(game.cl_info);
	ERROR(game.cl_info->ret);
	cl_program_new_push(game.cl_info, "program1");
	cl_program_init_sources(&game.cl_info->progs[0], "test.cl");
	cl_program_init_flags(&game.cl_info->progs[0], "-w");
	game.cl_info->ret = cl_prog_build(game.cl_info, &game.cl_info->progs[0]);
	ERROR(game.cl_info->ret);
	cl_krl_new_push(&game.cl_info->progs[0], "kerlnel_vect");
	ERROR(game.cl_info->ret);

	cl_krl_init(&game.cl_info->progs[0].krls[0], 3);
	cl_krl_create(game.cl_info, &game.cl_info->progs[0], &game.cl_info->progs[0].krls[0]);
	cl_krl_init_arg(&game.cl_info->progs[0].krls[0], 0, sizeof(int) * WIN_H * WIN_W,\
	game.sdl.surface->pixels);
	cl_krl_init_arg(&game.cl_info->progs[0].krls[0], 1, sizeof(cl_int),\
	&game.sdl.surface->w);
	cl_krl_init_arg(&game.cl_info->progs[0].krls[0], 2, sizeof(cl_int),\
	&game.sdl.surface->h);
	game.cl_info->ret = cl_krl_mem_create(game.cl_info, &game.cl_info->progs[0].krls[0], 0, CL_MEM_READ_WRITE);
	ERROR(game.cl_info->ret);

	game.gpu.cl_buffer_out = clCreateBuffer(game.cl_info->ctxt, CL_MEM_READ_WRITE,
	game.cl_info->progs[0].krls[0].sizes[0], NULL, &game.cl_info->ret);

	// game.cl_info->ret = cl_write(game.cl_info, game.cl_info->progs[0].krls[0].args[0],\
	//  game.cl_info->progs[0].krls[0].sizes[0], game.sdl.surface->pixels);
	ERROR(game.cl_info->ret);
	// //CL_BUILD_ERROR
	int i = 0;
	// while (i < 3)
	// {
	// 	cl_krl_set_arg (&game.cl_info->progs[0].krls[0], i);
	// 	i++;
	// }
	ERROR(game.cl_info->ret);

	size_t global[2] = {
		WIN_W,
		WIN_H
	};
	SDL_Event test_event;
	cl_krl_set_all_args(&game.cl_info->progs[0].krls[0]);
	while (1)
	{
		SDL_PollEvent(&test_event);
		if (test_event.type == SDL_QUIT)
			break;
	cl_krl_exec(game.cl_info, game.cl_info->progs[0].krls[0].krl, 2, global);
	cl_read(game.cl_info, game.cl_info->progs[0].krls[0].args[0],
	sizeof(cl_int) * WIN_W * WIN_H, game.sdl.surface->pixels);
	ft_surface_present(&game.sdl, game.sdl.surface);

	}
	// set_const(&game, &gui);
	// set_icon(&gui, "gui/res/icon.png");
	// init_kiwi(&gui);
	// opencl_init(&game);
	// if (argc != 2)
	// 	game.av = start_gui(&game, &gui);
	// else
	// {
	// 	scene_select(&gui, -1, 0);
	// 	game.av = argv[1];
	// }
	// SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
	// gui.main_screen = 1;
	// main_loop(&game, &gui, argc);
	// quit_kiwi_main(&gui);
	// ft_exit(NULL);
}
