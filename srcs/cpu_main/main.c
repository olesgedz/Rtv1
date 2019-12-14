/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/12/14 18:01:53 by jblack-b         ###   ########.fr       */
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

static void	cam_shot(char *name)
{
	char	*buff;
	char	*res;

	buff = ft_strjoin("./gui/ImageSnap-v0.2.5/imagesnap '", name);
	res = ft_strjoin(buff, "' >> /dev/null");
	free(buff);
	system(res);
	free(res);
}

static void	main_loop_free(t_game *game, t_gui *gui)
{
	free_list(game);
	game->texture_list = NULL;
	game->textures_num = 0;
	game->normal_list = NULL;
	game->normals_num = 0;
	main_screen_free(gui);
	cam_free(gui);
}

static void	main_loop(t_game *game, t_gui *gui, int argc)
{
	KW_HideWidget(gui->s_s.frame);
	gui_bar(game, gui);
	while (game->av)
	{
		free(game->music);
		game->music = 0;
		SDL_SetWindowTitle(game->sdl.window, game->av);
		opencl(game, game->av);
		main_screen(gui, game);
		cam_screen(gui, game);
		if (argc != 2)
			ft_strdel(&game->av);
		argc = 0;
		gui->av = 0;
		game->quit = 0;
		gui->quit = 0;
		game->flag = 1;
		play_stop_music(game->music);
		main_render(game, gui);
		play_stop_music(0);
		main_loop_free(game, gui);
	}
}

int			main(int argc, char **argv)
{
	t_game	game;
	t_gui	gui;

	gui.game = &game;
	cam_shot("./textures/sviborg_you.jpg");
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
