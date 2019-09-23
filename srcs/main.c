/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/09/23 16:01:58 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

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
	// init_kiwi(&gui);
	// while (game.av)
	opencl(&game, game.av);
	game.quit = 0;

	poopa(&game, &gui);
	//clReleaseMemObject(game.gpu.cl_bufferOut);
	//release_gpu(game.gpu);
	ft_exit(NULL);
}
