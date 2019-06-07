/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jblack-b <jblack-b@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 15:34:45 by sdurgan           #+#    #+#             */
/*   Updated: 2019/06/07 21:49:49 by jblack-b         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include <time.h>

//https://github.com/fastball20/RTv1/blob/master/vectorlib/vector.h
//home
/*
* ! We can't use global variables 
*/

//#define FPS

t_game game;
float xa, ya, za;

float eyex, eyey, eyez;
/*
*	Funtion: handles presses mouse/keyboard
* 	Return: value, doesnt change any parameters
*
*	- can handle multiple presses at once
*	- that goes into libsdl void ft_input(void *main, int (*f)(void *main, SDL_Event *ev))
*/
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
					case 'w': game.wsad[0] = ev->type==SDL_KEYDOWN; break;
					case 's': game.wsad[1] = ev->type==SDL_KEYDOWN; break;
					case 'a': game.wsad[2] = ev->type==SDL_KEYDOWN; break;
					case 'd': game.wsad[3] = ev->type==SDL_KEYDOWN; break;
					case 'q': game.wsad[4] = ev->type==SDL_KEYDOWN; break;
					case 'e': game.wsad[5] = ev->type==SDL_KEYDOWN; break;
					case 'z': game.wsad[6] = ev->type==SDL_KEYDOWN; break;
					case 'x': game.wsad[7] = ev->type==SDL_KEYDOWN; break;
					case 'p': ya+=0.2; break;
					case ';': ya-=0.2; break;
					case 'l': xa+=0.2; break;
					case '\'': xa-=0.2; break;
					case '.': za+=0.2; break;
					case '/': za-=0.2; break;
					default: break;
				}
				break;
			case SDL_MOUSEBUTTONDOWN:  
				break;
			case SDL_QUIT: ft_exit(NULL);
		}
	return (1);
}

/*
*	Fucntion:
*	Parameters:
*	Return:
*/

t_vec3	reflect(t_vec3 I, t_vec3 n)
{
	t_vec3 temp;
	
	temp = ft_vec3_scalar_multiply(n, 2.f * ft_vec3_dot_multiply(I, n));
	return ft_vec3_substract(I, temp);
}



/*
*	Fucntion: checks all objects on the scene
*	Parameters: stuff, sphere, ray
*	Return: true or false
*/

int scene_intersect(t_vec3 *orig, t_vec3 *dir, t_sphere *spheres, t_vec3 *hit, t_vec3 *N, t_material *material)
{
	float spheres_dist = FLT_MAX; // WHY
	size_t	i = -1;
	// ft_vec3_print(&spheres[0].center);
	// ft_vec3_print(&spheres[1].center);
	//ft_exit(NULL);
	
	while (++i < game.n_spheres)
	{
		float dist_i;

		if (ray_intersect_sphere_book(&spheres[i], orig, dir, &dist_i) && dist_i < spheres_dist)
		{
			spheres_dist = dist_i;
			t_vec3 temp = ft_vec3_scalar_multiply(*dir, dist_i);
			*hit = ft_vec3_sum(*orig, temp);
			temp = ft_vec3_substract(*hit, spheres[i].center);
			*N = ft_vec3_normalize(temp);
			*material = spheres[i].material;
		}
	}
	float checkerboard_dist = FLT_MAX;
    if (fabs(dir->y) > 1e-3)
	{
        float d = -(orig->y + 4) / dir->y; // the checkerboard plane has equation y = -4
        t_vec3 board = ft_vec3_sum(*orig, ft_vec3_scalar_multiply(*dir, d));
        if (d > 0 && fabs(board.x) < 10 && board.z < -10 && board.z > -30 && d < spheres_dist)
		{
            checkerboard_dist = d;
            *hit = board;
            *N = ft_vec3_create(0, 1, 0);
            material->diffuse_color = ((int)(0.5*(hit->x+1000)) + (int)(0.5*(hit->z)) & 1) ? ft_vec3_create(0.1, 0.1, 0.1) : ft_vec3_create(0.8, 0.7, 0.6);
        }
    }
	return spheres_dist < checkerboard_dist ? spheres_dist < 1000 : checkerboard_dist < 1000;
	//return spheres_dist < 1000;
}

/*
*	Fucntion: casts ray for that pixel
*	Parameters: stuff, sphere, ray
*	Return: returns matiral(color) for that pixel
*/

t_vec3 cast_ray(t_vec3 *orig, t_vec3 *dir, t_sphere *spheres)
{
	t_vec3 point;
	t_vec3 N;
	t_material material;
	int	i;

	// ft_vec3_print(&spheres[0].center);
	// ft_vec3_print(&spheres[1].center);
	float sphere_dist = FLT_MAX;
	//if (!ray_intersect(&spheres[0], orig, dir, &sphere_dist))
	if(!scene_intersect(orig, dir, spheres, &point, &N, &material))
		return ft_vec3_create(0.4, 0.4, 0.4); // background color
	float diffuse_light_intensity = 0;
	float specular_light_intensity = 0;
	i = -1;
	while (++i < game.elum.number)
	{
		t_vec3 light_dir      = ft_vec3_normalize(ft_vec3_substract(game.elum.lights[i].position, point));
		float light_distance = ft_vec3_norm(ft_vec3_substract(game.elum.lights[i].position, point));
		t_vec3 shadow_orig = ((ft_vec3_dot_multiply(light_dir, N) < 0) ? ft_vec3_substract(point, ft_vec3_scalar_multiply(N, 1e-3)) : ft_vec3_sum(point, ft_vec3_scalar_multiply(N, 1e-3)));
		t_vec3 shadow_pt, shadow_N;
		t_material temp_material;
		if (scene_intersect(&shadow_orig, &light_dir, spheres, &shadow_pt, &shadow_N, &temp_material) && ft_vec3_norm(ft_vec3_substract(shadow_pt, shadow_orig)) < light_distance)
			continue ;
		diffuse_light_intensity  += game.elum.lights[i].intensity * max(0, ft_vec3_dot_multiply(light_dir, N));
		specular_light_intensity += powf(max(0.f, ft_vec3_dot_multiply(ft_vec3_scalar_multiply(reflect(ft_vec3_scalar_multiply(light_dir, -1), N), -1),*dir)),\
		 	material.specular_exponent)*game.elum.lights[i].intensity;
	}
	return ft_vec3_sum(ft_vec3_scalar_multiply(material.diffuse_color, diffuse_light_intensity * material.albendo.x), \
	 	ft_vec3_scalar_multiply((t_vec3){1,1,1}, specular_light_intensity *  material.albendo.y));					//ft_vec3_scalar_multiply(&material.diffuse_color, diffuse_light_intensity);
}



	const float fov      = M_PI/2.; // field of vision




/*
*	Fucntion: render all pixels on the surface
*	Parameters: game, sdl
*	Return: none
*/
void 	ft_render(t_game* game, t_sphere *sphere)
{
	int		i;
	int		j;
	int width = game->sdl->surface->width;
	int height = game->sdl->surface->height;
	j = -1;
	while (++j < height)
	{
		i = -1;
		while (++i < width)
		{
			float x = (2 * (i + 0.5) / (float)width  - 1) * tan(fov / 2.) * width / (float)height;
			float y = -(2 * (j + 0.5) / (float)height - 1) * tan(fov / 2.);
			t_vec3 dir = ft_vec3_normalize((t_vec3){x, y, -1});
			game->origin = ft_vec3_multiply_matrix((t_vec3){0,0,0,1}, ft_mat4_translation_matrix((t_vec3){eyex,eyey,eyez}));//ft_vec3_multiply_matrix(ft_vec3_create(1, 1, 1),ft_look_at((t_vec3){0,50,5}, (t_vec3) {0,1,0}));
			//ft_vec3_print(ft_vec3_multiply_matrix(ft_vec3_create(0, 0, 5),ft_look_at((t_vec3){1,1,1}, (t_vec3) {0,1,0})));
			//ft_mat4_print(ft_mat4_translation_matrix((t_vec3){eyex,eyey,eyez}));
			//game->origin =ft_vec3_create(eyex,eyey,eyez);
			if (j == 0 && i == 0)
			{
				ft_mat4_print(ft_mat4_translation_matrix((t_vec3){eyex,eyey,eyez}));
				printf("result:");
				ft_vec3_print(ft_vec3_multiply_matrix((t_vec3){1,1,1,1}, ft_mat4_translation_matrix((t_vec3){eyex,eyey,eyez})));
				printf("\n");
			}
			t_vec3 temp = cast_ray(&game->origin, &dir, game->spheres);
			game->sdl->surface->data[i+j*width] = ft_rgb_to_hex(225 * max(0, min(1, temp.x)), 225 * max(0, min(1, temp.y)), 225 * max(0, min(1, temp.z)));
		}
	}
}


t_vec3 cube[8];


/*
*	Fucntion: Main loop
*		1. Clear the screen
*		2. Handle input
*		3. Render
*	!	4. surface_combine is redrawing only part of the screen, not used yet
*		5. Put surface to texture and then to on Screen
*			? don't use surfaces and use just textures for speed
*	Parameters: game, sdl
*	Return: none
*/

void ft_cube(t_game *game)
{
	t_vec3 cube_r[8];
	for(int i = 0; i < 8; i++)
	{
		cube_r[i] = ft_vec3_project_test1(ft_vec3_rotate_quaterion(ya * 30,cube[i],(t_vec3){1,0,0}));//ft_vec3_rotate_test2(cube[i], (t_vec3){xa,ya,za})); 
	}
	for (int i = 0; i<4; i++)         // Actual drawing
	{
		// ft_plot_wline(game->sdl->surface, &(t_fpoint){cube_r[i].x, cube_r[i].y}, &(t_fpoint){cube_r[i+4].x, cube_r[i+4].y}, 0xFF0000);
		// ft_plot_wline(game->sdl->surface, &(t_fpoint){cube_r[i].x, cube_r[i].y}, &(t_fpoint){cube_r[(i+1)%4].x, cube_r[(i+1)%4].y}, 0xFF0000);
		// ft_plot_wline(game->sdl->surface, &(t_fpoint){cube_r[i + 4].x, cube_r[i + 4].y}, &(t_fpoint){cube_r[(i+1)%4 + 4].x, cube_r[(i+1)%4 + 4].y}, 0xFF0000);
		ft_draw_poly(game->sdl->surface, (t_point){cube_r[i].x, cube_r[i].y}, (t_point){cube_r[i+4].x, cube_r[i+4].y}, (t_point){cube_r[(i+1)%4].x, cube_r[(i+1)%4].y});
		ft_draw_poly(game->sdl->surface, (t_point){cube_r[i].x, cube_r[i].y}, (t_point){cube_r[i+4].x, cube_r[(i+1)%4 + 4].y}, (t_point){cube_r[(i+1)%4].x, cube_r[(i+1)%4].y});
	}
}
void ft_update(t_game *game)
{
	t_rectangle r = (t_rectangle){(t_point){0,0},(t_size){WIN_W, WIN_H}};
	t_sphere sphere = {(t_vec3){-3, 0, -16}, 2};
	clock_t current_ticks, delta_ticks;
	clock_t fps = 0;
	while(1)
	{
		
		// ((t_light *)game->elum.light.get(&game->elum.light, 0))->position = game->elum.lights[0].position; //  Because VECTORS!
		// game->spheres[2].center =  ((t_light *)game->elum.light.get(&game->elum.light, 0))->position;       //game->elum.lights[0].position;
		//printf("%f %f\n", ((t_light *)game->elum.light.get(&game->elum.light, 0))->position.x);
		//game->spheres[2].center = game->elum.lights[0].position;
		current_ticks = clock();
		ft_surface_clear(game->sdl->surface);
		ft_input(game->sdl, &ft_input_keys);
		game->wsad[0] ? game->elum.lights[0].position.z -= 1: 0;
		game->wsad[1] ? game->elum.lights[0].position.z += 1 : 0;
		game->wsad[2] ? game->elum.lights[0].position.x -= 1 : 0;
		game->wsad[3] ? game->elum.lights[0].position.x += 1 : 0;
		game->wsad[4] ? game->elum.lights[0].position.y += 1 : 0;
		game->wsad[5] ? game->elum.lights[0].position.y -= 1 : 0;
		game->wsad[6] ? game->elum.lights[0].intensity += 0.1 : 0;
		game->wsad[7] ? game->elum.lights[0].intensity -= 0.1 : 0;
		//
		game->wsad[0] ? eyez -= 1: 0;
		game->wsad[1] ? eyez += 1 : 0;
		game->wsad[2] ? eyex -= 1 : 0;
		game->wsad[3] ? eyex += 1 : 0;
		game->wsad[4] ? eyey += 1 : 0;
		game->wsad[5] ? eyey -= 1 : 0;
		ft_render(game, &sphere);
		//ft_cube(game);
		//DrawTriangle(game->sdl->surface, (t_point){10,2}, (t_point){10,50}, (t_point){5,37});
		//ft_surface_combine(game->sdl->surface, game->image, &r);
		ft_surface_present(game->sdl, game->sdl->surface);
	#ifdef FPS
				 delta_ticks = clock() - current_ticks; //the time, in ms, that took to render the scene
    if(delta_ticks > 0)
        fps = CLOCKS_PER_SEC / delta_ticks;
		
			printf("fps :%lu\n", fps);
	#endif
	 }

}


int	main(int argc, char **argv)
{

	// t_mat3 a = (t_mat3){{{1,2,3}, {4,5,6}, {7,8,9}}};
	// t_vec3 v = (t_vec3){1,1,1};
	// t_mat4 m = (t_mat4){{{1,2,3, 4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}}};
	// m = ft_mat4_transpose(m);
	// ft_mat4_print(m);
	//v = ft_mat3_multiply_vec3(a,v);
	//ft_vec3_print(v);
			ft_vec3_print(ft_vec3_multiply_matrix(ft_vec3_create(0, 0, 0),ft_look_at((t_vec3){0,0,5}, (t_vec3) {0,1,0})));

	printf("move light source with wasdqe \nchange intensity with zx\n");
	game.sdl = malloc(sizeof(t_sdl));
	game.image = ft_surface_create(WIN_W, WIN_H);
	t_material ivory = (t_material){(t_vec3){0.4, 0.4, 0.3}, (t_vec3){0.6, 0.3, 0}, 70};
	t_material red_rubber = (t_material){(t_vec3){0.3, 0.1, 0.1}, (t_vec3){0.3, 0.5, 0}, 10000};
	//printf("%f %f %f\n", bb.albendo.x, bb.albendo.y, bb.specular_exponent);
	game.elum.lights = ft_memalloc(sizeof(t_light) * 5);
	game.elum.lights[0] = (t_light){(t_vec3){7, 10, -16}, 1.5};
	game.elum.lights[1] = (t_light){(t_vec3){-20, 20, 20}, 1.5};
	game.elum.lights[2] = (t_light){(t_vec3){30, 50, -25}, 1.8};
	game.elum.lights[3] = (t_light){(t_vec3){30, 20, 30}, 1.7};
	//vector_init(&game.elum.light);
	//vector_add(&game.elum.light,  &(t_light){(t_vec3){7, 10, -16}, 1.5});
	game.elum.number = 4; // number of light sources
	game.n_spheres = 1;
	game.spheres = ft_memalloc(sizeof(t_sphere) * 6);
	// game.spheres[0].tip = (t_vec3){-3, -1.5, -10};
	// game.spheres[0].v = (t_vec3){0, -0.5, 0};
	// game.spheres[0].angle = 25;
	// game.spheres[0].material = ivory;
	game.spheres[0] = (t_sphere){(t_vec3){0, 2, -13}, ivory, 3, (t_vec3){0.4, -0.8, 0.6}};
	game.spheres[1] = (t_sphere){(t_vec3){-1.0, -1.5, -12}, red_rubber, 2, 5};
	game.spheres[3] = (t_sphere){(t_vec3){1.5, -0.5, -18}, red_rubber, 3, 5};
	game.spheres[4] = (t_sphere){(t_vec3){7, 5, -18}, ivory, 4, 5};

	game.spheres[2] = (t_sphere){(t_vec3){-3.0, 0, -12}, red_rubber, 1, 5}; // this is a light source, move with wasdqe
	game.origin = (t_vec3){0,0,5,1};
	// ft_vec3_print(&game.spheres[0].center);
	// ft_vec3_print(&game.spheres[1].center);
	t_sphere sphere;
	
	for (int i=0; i<8; i++)     // Define the cube
	{
		cube[i].x=(float)(50-100*(((i+1)/2)%2));
		cube[i].y=(float)(50-100*((i/2)%2));
		cube[i].z=(float)(50-100*((i/4)%2));
	}


	configure_sphere(argv[1], &sphere);
	ft_init_window(game.sdl, WIN_W, WIN_H);
	ft_update(&game);
	ft_exit(NULL);
}