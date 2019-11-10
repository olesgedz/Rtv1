/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/11/10 19:53:35 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#define LOG_BUFSIZ 20480
#include "libgnl.h"

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
t_cl_prog *cl_program_get_by_name(t_cl_info *cl, char *name)
{
	int i;

	while (i < cl->n_progs)
	{
		if (!ft_strcmp(cl->progs[i].name, name))
			return (&cl->progs[i]);
	}
	return (NULL);
}

cl_int		cl_program_new_push(t_cl_info *cl, char *name)
{
	cl->progs = ft_realloc(cl->progs, sizeof(t_cl_prog));
	cl->n_progs++;
	cl->progs[cl->n_progs - 1].name = ft_strdup(name);
	cl->progs[cl->n_progs - 1].krls = 0;
	cl->progs[cl->n_progs - 1].n_krls = 0;
	return (0);
}

cl_int cl_program_init_sources(t_cl_prog *program, char *sources)
{
	if (!(program->sources = ft_strdup(sources)))
		ft_malloc_err(sizeof(sources), __FUNCTION__ , __FILE__, __LINE__);
	return (0);
} 
cl_int cl_program_init_flags(t_cl_prog *program, char *flags)
{
	if (!(program->flags = ft_strdup(flags)))
		ft_malloc_err(sizeof(flags), __FUNCTION__ , __FILE__, __LINE__);
	return (0);
} 

void cl_program_build_inf(t_cl_info *cl, t_cl_prog * prog)
{
	char		buffer[LOG_BUFSIZ];

	clGetProgramBuildInfo(prog->program, cl->dev_id, CL_PROGRAM_BUILD_LOG
			, LOG_BUFSIZ, buffer, NULL);
		write(1, buffer, ft_strlen(buffer));
}


cl_int			cl_prog_buildn(t_cl_info *cl, t_cl_prog *prog)
{
	cl_int		ret;
	t_vect		*lines;

	lines = ft_memalloc(sizeof(t_vect));
	vect_init(lines);
	if ((prog->fd = open(prog->sources, O_RDONLY)) < 3)
		ft_terminate("Can't open file\n");
	gnl_lines(prog->fd, lines, GNL_APPEND_CHAR);
	prog->program = clCreateProgramWithSource(cl->ctxt,
	lines->used / sizeof(void *),
	(const char **)lines->data, NULL, &ret);
	if (ret != CL_SUCCESS)
		return (ret);
	if ((ret = clBuildProgram(prog->program,
		cl->dev_num, &cl->dev_id, prog->flags, NULL, NULL)) != CL_SUCCESS)
	{
		cl_program_build_inf(cl, prog);
		return (ret);
	}
	vect_del(lines);
	return (ret);
}

cl_int		cl_krl_new_push(t_cl_prog *prog, char *name)
{
	prog->krls = ft_realloc(prog->krls, sizeof(t_cl_krl));
	prog->n_krls++;
	prog->krls[prog->n_krls - 1].name = ft_strdup(name);
	return (0);
}

cl_int  cl_krl_init_arg(t_cl_krl *krl, cl_uint arg_index, size_t arg_size,  void *arg_value)
{
	cl_int ret;

	// if (!krl->args[arg_index] || !krl->sizes[arg_index])
	// 	ft_terminate("Kernel doesn't exist.");
	krl->cpu_srcs[arg_index] = arg_value;
	krl->sizes[arg_index] = arg_size;
	krl->args[arg_index] = NULL;
	return (ret);
}

cl_int  cl_krl_mem_create(t_cl_info *cl, t_cl_krl *krl,\
 cl_uint arg_index, cl_mem_flags FLAG)
{
	cl_int ret;
	krl->args[arg_index] = clCreateBuffer(cl->ctxt, FLAG,
	krl->sizes[arg_index], NULL, &ret);
	return (ret);
}

cl_int cl_krl_set_arg (t_cl_krl * krl, int index)
{
	int ret;
	
	if (krl->args[index] == NULL)
		ret = clSetKernelArg(krl->krl, index,\
		sizeof(krl->sizes[index]), (void*)krl->cpu_srcs[index]);
	else
	ret = clSetKernelArg(krl->krl, index,\
		sizeof(cl_mem), (void*)&krl->args[index]);
	return (ret);	
}

cl_int				cl_krl_create(t_cl_info *cl, t_cl_prog *prog, t_cl_krl *krl)
{
	cl_int			ret;

	krl->krl =  clCreateKernel(prog->program, krl->name, &ret); 
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
	game.cl_info->ret = cl_prog_buildn(game.cl_info, &game.cl_info->progs[0]);
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
	while (i < 3)
	{
		cl_krl_set_arg (&game.cl_info->progs[0].krls[0], i);
		i++;
	}
	ERROR(game.cl_info->ret);

	size_t global[2] = {
		WIN_W,
		WIN_H
	};
	SDL_Event test_event;
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
