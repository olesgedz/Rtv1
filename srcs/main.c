/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurgan <sdurgan@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/18 12:53:03 by jblack-b          #+#    #+#             */
/*   Updated: 2019/05/15 16:25:29 by sdurgan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "rtv1.h"

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

int		ft_input_keys(void *sdl, SDL_Event *ev)
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

t_p3d *ft_p3d_create(float x, float y, float z)
{
	t_p3d *new;
	
	new = malloc (sizeof(t_p3d));
	new->x = x;
	new->y = y;
	new->z = z;
	return (new);
}

t_p3d *ft_p3d_substract(t_p3d *a, t_p3d *b)
{
	t_p3d *new;
	
	new = malloc (sizeof(t_p3d));
	new->x = (a->x - b->x);
	new->y = (a->y - b->y);
	new->z = (a->z - b->z);
	return (new);
}

void ft_p3d_print(t_p3d *a)
{
	printf("x:%f y:%f z:%f\n", a->x, a->y, a->z);
}

float ft_p3d_scalar_multiply(t_p3d *a, t_p3d *b)
{
	return (a->x * b->x + a->y * b->y + a->z * b->z);
}

int ray_intersect(t_sphere *sphere, t_p3d *orig, t_p3d *dir, float t0)
{
	t_p3d L = *ft_p3d_substract(&sphere->center, orig);
	 printf("%f %f %f, dir: %f %f %f\n", L.x, L.y, L.z, dir->x, dir->y, dir->z);
	float tca = ft_p3d_scalar_multiply(&L, dir);
	printf("tca %f\n", tca);
	float d2 = ft_p3d_scalar_multiply(&L,&L) - tca*tca;
	//printf("d2 %f %f \n", d2, sphere->radius * sphere->radius);
	if (d2 > sphere->radius * sphere->radius) return FALSE;
	float thc = sqrtf( sphere->radius * sphere->radius - d2);
	t0	= tca - thc;
	float t1 = tca + thc;
	if (t0 < 0) t0 = t1;
	if (t0 < 0) return FALSE;
	return TRUE;
}


t_p3d *cast_ray (t_p3d *orig, t_p3d *dir, t_sphere *sphere) {
    float sphere_dist = FLT_MAX;
    if (!ray_intersect(sphere, orig, dir, sphere_dist)) {
        return ft_p3d_create(0, 255, 0); // background color
    }
    return ft_p3d_create(255, 0, 0);
}

float ft_p3d_norm(t_p3d *vect)
{
	return (sqrt(vect->x* vect->x+ vect->y* vect->y+ vect->z * vect->z));
}

//*this = (*this)*(l/norm())
t_p3d *ft_p3d_normalize(t_p3d *vect, float l)
{
	float norm = ft_p3d_norm(vect);
	vect->x = vect->x * (l / norm);
	vect->y = vect->y * (l / norm);
	vect->z = vect->z * (l / norm);
	return (vect);
}

  const float fov      = M_PI/3.;

void 	ft_render(t_game* game, t_sphere *sphere)
{
	int width = game->sdl->surface->width;
	int height = game->sdl->surface->height;
	for (size_t j = 0; j<height ; j++)
	{
		for (size_t i = 0; i< width; i++) {
			float x =  (2*(i + 0.5)/(float)width  - 1)*tan(fov/2.)*width/(float)height;
			float y = -(2*(j + 0.5)/(float)height - 1)*tan(fov/2.);
			t_p3d dir = *ft_p3d_normalize(&(t_p3d){x, y, -1}, 1);//.normalize();
			t_p3d temp = *cast_ray(ft_p3d_create(0,0,0), &dir, sphere);
			game->sdl->surface->data[i+j*width] = ft_rgb_to_hex(temp.x, temp.y, temp.z);
			// if (sqrt(pow(i - sphere->center.x, 2) + pow(j - sphere->center.y, 2)) <= sphere->radius)
			// {
			// 	game->sdl->surface->data[i+j*width] = 0xFF0000;
			//  	game->sdl->surface->data[i+j*width] = ft_rgb_to_hex(temp.x, temp.y, temp.z);
				 
			// }
		}
	}
}


void ft_update(t_game *game)
{
	t_rectangle r = (t_rectangle){(t_point){0,0},(t_size){WIN_W, WIN_H}};
	t_sphere sphere = {(t_p3d){-3, 0, -16}, 2};
	while(1)
	{
		ft_surface_clear(game->sdl->surface);
		ft_input(game->sdl, &ft_input_keys);
		ft_render(game, &sphere);
		//ft_put_pixel(game->sdl->surface, &(t_point){500,500}, 0xFF0000);
		ft_surface_combine(game->sdl->surface, game->image, &r);
		ft_surface_present(game->sdl, game->sdl->surface);
		SDL_Delay(2000);
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


int	main(int argc, char **argv)
{
	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	t_sphere sphere;
	configure_sphere(argv[1], &sphere);
	//printf("%d",ray_intersect(&sphere, ft_p3d_create(0,0,0), ft_p3d_normalize(&(t_p3d){650, 650, -1}, 1), FLT_MAX));
	ft_init_window(game.sdl, WIN_W, WIN_H);
	printf("%zu, %zu\n", game.sdl->surface->height, game.sdl->surface->width);

	ft_update(&game);
	ft_exit(NULL);
}
