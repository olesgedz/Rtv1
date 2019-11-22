/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/11/21 18:24:45 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include "libgnl.h"
#include <unistd.h>
static void	set_icon(t_gui *gui, const char *filename)
{
	SDL_Surface		*surf;

	if (!(surf = IMG_Load(filename)))
	{
		print_error_gui("No picture for you: ", SDL_GetError());
		exit(1);
	}
	SDL_SetWindowIcon(gui->sdl.window, surf);
	SDL_FreeSurface(surf);
}

static void	main_loop(t_game *game, t_gui *gui, int argc)
{
	KW_HideWidget(gui->s_s.frame);
	gui_bar(game, gui);
	while (game->av)
	{
		SDL_SetWindowTitle(game->sdl.window, game->av);
		opencl(game, game->av);
		main_screen(gui, game);
		if (argc != 2)
			ft_strdel(&game->av);
		argc = 0;
		gui->av = 0;
		game->quit = 0;
		gui->quit = 0;
		game->flag = 1;
		main_render(game, gui);
		free_list(game);
		game->texture_list = NULL;
		game->textures_num = 0;
		game->normal_list = NULL;
		game->normals_num = 0;
		main_screen_free(gui);
	}
}

int			main(int argc, char **argv)
{
	t_game	game;
	t_gui	gui;

	gui.game = &game;
	system("./gui/ImageSnap-v0.2.5/imagesnap './textures/sviborg_you.jpg'");
	gui.main_screen = 0;
	ft_init_window(&game.sdl, WIN_W, WIN_H);
	set_const(&game, &gui);
	set_icon(&gui, "gui/res/icon.png");
	init_kiwi(&gui);
	opencl_init(&game);
	if (argc != 2)
		game.av = start_gui(&game, &gui);
	else
	{
		scene_select(&gui, -1, 0);
		game.av = argv[1];
	}
	SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
	gui.main_screen = 1;
	main_loop(&game, &gui, argc);
	quit_kiwi_main(&gui);
	ft_exit(NULL);
}
