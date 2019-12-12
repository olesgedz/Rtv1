/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_mov.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:06:44 by jblack-b          #+#    #+#             */
/*   Updated: 2019/12/10 18:08:42 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"

void		reconfigure_camera(t_cam *camera)
{
	float		x_fov;
	float		y_fov;

	x_fov = (float)WIN_W / (float)WIN_H > 1 ? camera->fov / 2 :
	camera->fov / 2 * (float)WIN_W / (float)WIN_H;
	y_fov = (float)WIN_H / (float)WIN_W > 1 ? (camera->fov / 2) :
	(camera->fov / 2) * ((float)WIN_H / (float)WIN_W);
	camera->border_y = vector_diff(
	rotate(camera->normal, camera->direction, x_fov),
	rotate(camera->normal, camera->direction, -x_fov));
	camera->border_x = vector_diff(
	rotate(cross(camera->direction, camera->normal), camera->direction, y_fov),
	rotate(cross(camera->direction, camera->normal),
	camera->direction, -y_fov));
}

void		pos_check(t_game *game, t_gui *gui)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	SDL_GetMouseState(&x, &y);
	gui->over_gui = 0;
	check_gui_entrance(game, gui, x, y);
	if (game->keys.show_gui && gui->over_gui)
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW));
	else
		SDL_SetCursor(SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_CROSSHAIR));
}
