/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2019/09/25 18:03:41 by lminta           ###   ########.fr       */
=======
/*   Updated: 2019/06/27 22:48:02 by jblack-b         ###   ########.fr       */
>>>>>>> ed1cfb85ba72997255856a89f2b3e944b1c6335d
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

static void the_loopa(t_game *game, t_gui *gui, int argc)
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
		poopa(game, gui);
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
	if (argc != 2)
		game.av = start_gui(&gui);
	else
		game.av = argv[1];
	SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
	init_kiwi(&gui);
	gui.main_screen = 1;
	scene_select(&gui);
	the_loopa(&game, &gui, argc);
	quit_kiwi_main(&gui);
	//release_gpu(game.gpu);
	ft_exit(NULL);
}
