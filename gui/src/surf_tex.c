/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   surf_tex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lminta <lminta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/15 18:04:29 by lminta            #+#    #+#             */
/*   Updated: 2019/11/22 19:12:14 by lminta           ###   ########.fr       */
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
	//KW_DestroyWidget(gui->c_o.frame, 1);
	gui->c_o.dest = 1;
	if (wid && widget)
		KW_SetLabelTextColor(KW_GetButtonLabel(wid), (KW_Color){0, 0, 0, 255});
	gui->c_o.show = 0;
}

void destr(t_gui *gui)
{
	if (!gui->c_o.dest)
		return ;
	KW_DestroyWidget(gui->c_o.frame, 1);
}
