/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/11/08 19:53:17 by jblack-b         ###   ########.fr       */
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
