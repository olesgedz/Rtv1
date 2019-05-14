/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:53:03 by jblack-b          #+#    #+#             */
/*   Updated: 2019/05/14 22:36:21 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include "libsdl.h"
#include "rtv1.h"
#include <limits.h>
#include <float.h>

	t_game game;

int ft_point_compare(t_list *list, void *target)
{
	if ((((t_point *)list->content)->x == ((t_point *)target)->x) &&
		(((t_point *)list->content)->y == ((t_point *)target)->y))
		{
			printf("S:%d %d %d %d\n", ((t_point *)list->content)->x,((t_point *)target)->x,
			((t_point *)list->content)->y , ((t_point *)target)->y);
			return (1);
		}
	return (0);
}
void ft_lst_free(void *content, size_t size)
{
	ft_memdel((void **)content);
}
t_list		*ft_list_search(t_list *lst, void *target, int (*f)(t_list *, void *))
{
	while (lst != NULL)
	{
		if (f(lst, target))
			return (lst);
		lst = lst->next;
	}
	return (NULL);
}

void ft_put_vertex(t_game *game)
{
	
	ft_put_pixel(game->image, &(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, 0xFF0000);
	if (ft_list_search(game->verties, &(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, ft_point_compare))
	{
		printf("YIIIIS\n");
		//ft_lstdel(&game->verties, ft_lst_free);
	}
	ft_lstadd(&game->verties, ft_lstnew(&(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, sizeof(t_point)));
	printf("%d %d\n", ((t_point *)game->verties->content)->x, ((t_point *)game->verties->content)->y);
}

void ft_mouse_pressed(t_game *game, SDL_Event *ev)
{
	game->sdl->mouse.pressed = 1;
	game->sdl->mouse.last_x = game->sdl->mouse.x;
	game->sdl->mouse.last_y = game->sdl->mouse.y;
	game->sdl->mouse.x = ev->button.x;
	game->sdl->mouse.y = ev->button.y;
	ft_put_vertex(game);
	if (game->sdl->mouse.last_x > 0)
		ft_plot_line(game->image, &(t_point){game->sdl->mouse.last_x, game->sdl->mouse.last_y},\
	 		&(t_point){game->sdl->mouse.x, game->sdl->mouse.y}, 0x00FF00);
}

int		ft_input_keys(t_sdl *sdl, SDL_Event *ev)
{
	switch (ev->type)
		{
			case SDL_KEYDOWN:
			case SDL_KEYUP:
				switch (ev->key.keysym.sym)
				{
					case SDLK_LCTRL:
					case SDLK_RCTRL:
					case SDLK_ESCAPE: ft_exit(NULL); break;
					case SDLK_z: ; break;
					case SDLK_x: ; break;
					case SDLK_c: ; break;
					default: break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:  ft_mouse_pressed(&game, ev);
				break;
			case SDL_QUIT: ft_exit(NULL);
		}
	return (1);
}


int ray_intersect(t_sphere *sphere, t_p3d *orig, t_p3d dir, float t0)
{
	t_p3d L = sphere->center - orig;
	float tca = L*dir;
	float d2 = L*L - tca*tca;
	if (d2 > radius*radius) return false;
	float thc = sqrtf(radius*radius - d2);
	t0       = tca - thc;
	float t1 = tca + thc;
	if (t0 < 0) t0 = t1;
	if (t0 < 0) return false;
	return true;
}


t_p3d *cast_ray (t_p3d *orig, t_p3d *dir, t_sphere *sphere) {
    float sphere_dist = FLT_MAX;
    if (!ray_intersect(orig, dir, sphere_dist)) {
        return Vec3f(0.2, 0.7, 0.8); // background color
    }
    return Vec3f(0.4, 0.4, 0.3);
}


void 	ft_render(t_game* game, t_sphere *sphere)
{
	int width = game->sdl->surface->width;
	int height = game->sdl->surface->height;
	for (size_t j = 0; j<height ; j++)
	{
		for (size_t i = 0; i< width; i++) {
			float x =  (2*(i + 0.5)/(float)width  - 1)*tan(90/2.)*width/(float)height;
			float y = -(2*(j + 0.5)/(float)height - 1)*tan(90/2.);
			t_p3d dir = (t_p3d){x, y, -1};//.normalize();
			game->sdl->surface->data[i+j*width] = cast_ray(Vec3f(0,0,0), dir, sphere);
		}
	}
}


void ft_update(t_game *game)
{
	t_rectangle r = (t_rectangle){(t_point){0,0},(t_size){WIN_W, WIN_H}};
	t_sphere sphere = {(t_p3d){50, 50, 0}, 100};
	while(1)
	{
		ft_surface_clear(game->sdl->surface);
		ft_input(game->sdl, &ft_input_keys);
		ft_render(game, &sphere);
		//ft_put_pixel(game->sdl->surface, &(t_point){500,500}, 0xFF0000);
		ft_surface_combine(game->sdl->surface, game->image, &r);
		ft_surface_present(game->sdl, game->sdl->surface);
	}
}


// void Sphere(const t_p3d *c, const float r)
// {

// }

// bool ray_intersect(const t_p3d *orig, const t_p3d dir, float *t0)
// {
// 	t_p3d L = center - orig;
// 	float tca = L*dir;
// 	float d2 = L*L - tca*tca;
// 	if (d2 > radius*radius) return false;
// 	float thc = sqrtf(radius*radius - d2);
// 	t0       = tca - thc;
// 	float t1 = tca + thc;
// 	if (t0 < 0) t0 = t1;
// 	if (t0 < 0) return false;
// 	return true;
// }


int main()
{

	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	ft_init_window(game.sdl, WIN_W, WIN_H);
	printf("%zu, %zu\n", game.sdl->surface->height, game.sdl->surface->width);

	ft_update(&game);
	ft_exit(NULL);
}