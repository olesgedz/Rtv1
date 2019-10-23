/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/10/23 22:04:48 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void	main_loop(t_game *game, t_gui *gui, int argc)
{
	while (game->av)
	{
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
		main_screen_free(gui);
	}
}

int			main(int argc, char **argv)
{
	t_game	game;
	t_gui	gui;

	gui.main_screen = 0;
	ft_init_window(&game.sdl, WIN_W, WIN_H);
	set_const(&game, &gui);
	init_kiwi(&gui);
	if (argc != 2)
		game.av = start_gui(&gui);
	else
	{
		scene_select(&gui, -1, 0);
		game.av = argv[1];
	}
	SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
	gui.main_screen = 1;
	opencl_init(&game);
	main_loop(&game, &gui, argc);
	quit_kiwi_main(&gui);
	ft_exit(NULL);
}
