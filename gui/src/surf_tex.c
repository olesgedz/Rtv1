/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surf_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 18:04:29 by lminta            #+#    #+#             */
/*   Updated: 2019/12/01 19:14:18 by lminta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rt.h"
#include <unistd.h>

void		print_error_gui(const char *message, const char *error_message)
{
	if (!error_message || !message)
		write(2,
"FUCK MAN! YOUR WHOLE FUCKING PROGRAM IS FUCKING BROCKEN! FUCKING SHIT!\n", 71);
	else
	{
		write(2, message, ft_strlen(message));
		write(2, error_message, ft_strlen(error_message));
		write(2, "\n", 1);
	}
}

SDL_Texture	*surf_to_text(t_gui *gui, SDL_Surface *surf)
{
	SDL_Texture	*buff;

	if (!(buff =
SDL_CreateTextureFromSurface(gui->sdl.renderer, surf)))
	{
		print_error_gui("No texture for you: ", SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(surf);
	return (buff);
}

SDL_Texture	*load_picture(t_gui *gui, const char *filename)
{
	SDL_Surface		*surf;
	SDL_Surface		*opt;
	SDL_PixelFormat	fmt;

	if (!(surf = SDL_LoadBMP(filename)))
	{
		print_error_gui("No picture for you: ", SDL_GetError());
		exit(1);
	}
	fmt = *surf->format;
	fmt.BytesPerPixel = 4;
	fmt.BitsPerPixel = 32;
	if (!(opt = SDL_ConvertSurface(surf, &fmt, 0)))
	{
		print_error_gui("No optimization for you: ", SDL_GetError());
		exit(1);
	}
	SDL_FreeSurface(surf);
	return (surf_to_text(gui, opt));
}

void	norma_from_obj_select(t_gui *gui, KW_Widget *widget, KW_Widget *wid)
{
	KW_Widget	*label;
	int			i;

	i = -1;
	while (++i < 3)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->c_o.buttons[i], 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->c_o.buttons[i], 0);
		KW_RemoveWidgetMouseDownHandler(gui->c_o.buttons[i], 0);
	}
	i = -1;
	while (gui->c_o.ed_b[++i] && i < 30)
	{
		KW_RemoveWidgetMouseUpHandler(gui->c_o.ed_b[i], 0);
		KW_RemoveWidgetMouseOverHandler(gui->c_o.ed_b[i], 0);
		KW_RemoveWidgetMouseLeaveHandler(gui->c_o.ed_b[i], 0);
		KW_RemoveWidgetFocusGainHandler(gui->c_o.ed_b[i], 0);
		KW_RemoveWidgetFocusLoseHandler(gui->c_o.ed_b[i], 0);
		KW_RemoveWidgetKeyDownHandler(gui->c_o.ed_b[i], 0);
		KW_RemoveWidgetTextInputHandler(gui->c_o.ed_b[i], 0);
		KW_RemoveWidgetMouseDownHandler(gui->c_o.ed_b[i], 0);
	}
	KW_RemoveWidgetGeometryChangeHandler(gui->c_o.frame, 0);
	KW_RemoveWidgetTilesetChangeHandler(gui->c_o.frame, 0);
	KW_HideWidget(gui->c_o.frame);
	destr(gui, gui->c_o.frame);
	i = -1;
	while (++i < 30)
		gui->c_o.ed_b[i] = 0;
	gui->c_o.frame = 0;
	if (wid && widget)
	{
		label = KW_GetButtonLabel(wid);
		if (label)
			KW_SetLabelTextColor(label, (KW_Color){0, 0, 0, 255});
	}
	gui->c_o.show = 0;
}

void	norma_from_cam_select(t_gui *gui, KW_Widget *widget, KW_Widget *wid)
{
	KW_Widget	*label;
	int			i;

	i = -1;
	while (++i < 5)
	{
		KW_RemoveWidgetGeometryChangeHandler(gui->c_c.buttons[i], 0);
		KW_RemoveWidgetTilesetChangeHandler(gui->c_c.buttons[i], 0);
		KW_RemoveWidgetMouseDownHandler(gui->c_c.buttons[i], 0);
	}
	i = -1;
	while (gui->c_c.ed_b[++i] && i < 30)
	{
		KW_RemoveWidgetMouseUpHandler(gui->c_c.ed_b[i], 0);
		KW_RemoveWidgetMouseOverHandler(gui->c_c.ed_b[i], 0);
		KW_RemoveWidgetMouseLeaveHandler(gui->c_c.ed_b[i], 0);
		KW_RemoveWidgetFocusGainHandler(gui->c_c.ed_b[i], 0);
		KW_RemoveWidgetFocusLoseHandler(gui->c_c.ed_b[i], 0);
		KW_RemoveWidgetKeyDownHandler(gui->c_c.ed_b[i], 0);
		KW_RemoveWidgetTextInputHandler(gui->c_c.ed_b[i], 0);
		KW_RemoveWidgetMouseDownHandler(gui->c_c.ed_b[i], 0);
	}
	KW_RemoveWidgetGeometryChangeHandler(gui->c_c.frame, 0);
	KW_RemoveWidgetTilesetChangeHandler(gui->c_c.frame, 0);
	KW_HideWidget(gui->c_c.frame);
	destr(gui, gui->c_c.frame);
	i = -1;
	while (++i < 30)
		gui->c_c.ed_b[i] = 0;
	gui->c_c.frame = 0;
	if (wid && widget)
	{
		label = KW_GetButtonLabel(wid);
		if (label)
			KW_SetLabelTextColor(label, (KW_Color){0, 0, 0, 255});
	}
	gui->c_c.show = 0;
}
