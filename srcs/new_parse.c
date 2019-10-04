/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 16:16:59 by david             #+#    #+#             */
/*   Updated: 2019/10/04 16:03:48 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "errno.h"

//если при добавлении очередного объекта в json файл программа не работает,
//попробуй увеличить размер buffer в функции read_scene



// typedef struct  s_json
// {
//     cJSON *position;
//     cJSON *color;
//     cJSON *emition;
//     cJSON *reflection;
//     cJSON *texture;
//     cJSON *radius;
//     cJSON *v;
//     cJSON *x;
//     cJSON *y;
//     cJSON *z;
// }               t_json;

void	reconfigure_camera(t_cam *camera)
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

void parse_plane(const cJSON *object, t_game *game)
{
    t_obj *plane;
    cJSON *position;
    cJSON *color;
    cJSON *emition;
    cJSON *reflection;
    cJSON *texture;
    cJSON *v;
    cJSON *x;
    cJSON *y;
    cJSON *z;

    plane = (t_obj*)malloc(sizeof(t_obj));
    plane->type = PLANE;
    position = cJSON_GetObjectItemCaseSensitive(object, "position");
    x = cJSON_GetArrayItem(position, 0);
    y = cJSON_GetArrayItem(position, 1);
    z = cJSON_GetArrayItem(position, 2);
    if (x != NULL && y != NULL && z != NULL)
        plane->position = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
        //printf("my start pos: %f,%f,%f\n", x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of plane start pos vector!\n");
    // killer(x, y, z);
    color = cJSON_GetObjectItemCaseSensitive(object, "color");
    x = cJSON_GetArrayItem(color, 0);
    y = cJSON_GetArrayItem(color, 1);
    z = cJSON_GetArrayItem(color, 2);
    if (x != NULL && y != NULL && z != NULL)
        plane->color = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of plane color vector!\n");
    // killer(x, y, z);
    v = cJSON_GetObjectItemCaseSensitive(object, "dir");
    x = cJSON_GetArrayItem(v, 0);
    y = cJSON_GetArrayItem(v, 1);
    z = cJSON_GetArrayItem(v, 2);
    if (x != NULL && y != NULL && z != NULL)
        plane->v = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of plane dir vector!\n");
    // killer(x, y, z);
    emition = cJSON_GetObjectItemCaseSensitive(object, "emition");
    if (emition != NULL)
    {
        x = cJSON_GetArrayItem(emition, 0);
        y = cJSON_GetArrayItem(emition, 1);
        z = cJSON_GetArrayItem(emition, 2);
        if (x != NULL && y != NULL && z != NULL)
            plane->emission = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
        else
           terminate("missing data of plane emition vector!\n");
        // killer(x, y, z); 
    }
    else
        plane->emission = create_cfloat3(0.0, 0.0, 0.0);
    reflection = cJSON_GetObjectItemCaseSensitive(object, "reflection");
    if (reflection != NULL)
        plane->reflection = reflection->valuedouble;
    else
        plane->reflection = 0.0;
    texture = cJSON_GetObjectItemCaseSensitive(object, "texture");
    if (texture != NULL)
        plane->texture = (int)texture->valuedouble;
    else
        plane->texture = 0;
    // cJSON_Delete(position);
    // cJSON_Delete(color);
    // cJSON_Delete(emition);
    // cJSON_Delete(v);
    // cJSON_Delete(reflection);
    // cJSON_Delete(texture);
    // cJSON_Delete(x);
    // cJSON_Delete(y);
    // cJSON_Delete(z);
    ft_object_push(game, plane);
}

void parse_sphere(const cJSON *object, t_game *game)
{
    t_obj *sphere;

    cJSON *position;
    cJSON *color;
    cJSON *emition;
    cJSON *reflection;
    cJSON *texture;
    cJSON *radius;
    cJSON *x;
    cJSON *y;
    cJSON *z;

    sphere = (t_obj*)malloc(sizeof(t_obj));
    sphere->type = SPHERE;
    position = cJSON_GetObjectItemCaseSensitive(object, "position");
    x = cJSON_GetArrayItem(position, 0);
    y = cJSON_GetArrayItem(position, 1);
    z = cJSON_GetArrayItem(position, 2);
    if (x != NULL && y != NULL && z != NULL)
        sphere->position = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of sphere start pos vector!\n");
    color = cJSON_GetObjectItemCaseSensitive(object, "color");
    x = cJSON_GetArrayItem(color, 0);
    y = cJSON_GetArrayItem(color, 1);
    z = cJSON_GetArrayItem(color, 2);
    if (x != NULL && y != NULL && z != NULL)
        sphere->color = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of sphere color vector!\n");
    radius = cJSON_GetObjectItemCaseSensitive(object, "radius");
    if (radius != NULL)
        sphere->radius = radius->valuedouble;
    else
        terminate("missing data of sphere radius!\n");
    emition = cJSON_GetObjectItemCaseSensitive(object, "emition");
    if (emition != NULL)
    {
        x = cJSON_GetArrayItem(emition, 0);
        y = cJSON_GetArrayItem(emition, 1);
        z = cJSON_GetArrayItem(emition, 2);
        if (x != NULL && y != NULL && z != NULL)
            sphere->emission = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
        else
           terminate("missing data of sphere emition vector!\n"); 
    }
    else
        sphere->emission = create_cfloat3(0.0, 0.0, 0.0);
    reflection = cJSON_GetObjectItemCaseSensitive(object, "reflection");
    if (reflection != NULL)
        sphere->reflection = reflection->valuedouble;
    else
        sphere->reflection = 0.0;
    texture = cJSON_GetObjectItemCaseSensitive(object, "texture");
    if (texture != NULL)
        sphere->texture = (int)texture->valuedouble;
    else
        sphere->texture = 0;
    ft_object_push(game, sphere);
}

void parse_cylinder(const cJSON *object, t_game *game)
{
    t_obj *cylinder;

    cJSON *position;
    cJSON *color;
    cJSON *emition;
    cJSON *reflection;
    cJSON *texture;
    cJSON *radius;
    cJSON *type;
    cJSON *v;
    cJSON *x;
    cJSON *y;
    cJSON *z;

    cylinder = (t_obj*)malloc(sizeof(t_obj));
    
    cylinder->type = CYLINDER;
    type = cJSON_GetObjectItemCaseSensitive(object, "type");
    if (ft_strcmp(type->valuestring, "cone") == 0)
        cylinder->type = CONE;
    position = cJSON_GetObjectItemCaseSensitive(object, "position");
    x = cJSON_GetArrayItem(position, 0);
    y = cJSON_GetArrayItem(position, 1);
    z = cJSON_GetArrayItem(position, 2);
    if (x != NULL && y != NULL && z != NULL)
        cylinder->position = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of cylinder start pos vector!\n");
    color = cJSON_GetObjectItemCaseSensitive(object, "color");
    x = cJSON_GetArrayItem(color, 0);
    y = cJSON_GetArrayItem(color, 1);
    z = cJSON_GetArrayItem(color, 2);
    if (x != NULL && y != NULL && z != NULL)
        cylinder->color = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of cylinder color vector!\n");
    radius = cJSON_GetObjectItemCaseSensitive(object, "radius");
    if (radius != NULL)
        cylinder->radius = radius->valuedouble;
    else
        terminate("missing data of cylinder radius!\n");
    emition = cJSON_GetObjectItemCaseSensitive(object, "emition");
    if (emition != NULL)
    {
        x = cJSON_GetArrayItem(emition, 0);
        y = cJSON_GetArrayItem(emition, 1);
        z = cJSON_GetArrayItem(emition, 2);
        if (x != NULL && y != NULL && z != NULL)
            cylinder->emission = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
        else
           terminate("missing data of cylinder emition vector!\n"); 
    }
    else
        cylinder->emission = create_cfloat3(0.0, 0.0, 0.0);
    reflection = cJSON_GetObjectItemCaseSensitive(object, "reflection");
    if (reflection != NULL)
        cylinder->reflection = reflection->valuedouble;
    else
        cylinder->reflection = 0.0;
    texture = cJSON_GetObjectItemCaseSensitive(object, "texture");
    if (texture != NULL)
        cylinder->texture = (int)texture->valuedouble;
    else
        cylinder->texture = 0;
    v = cJSON_GetObjectItemCaseSensitive(object, "dir");
    x = cJSON_GetArrayItem(v, 0);
    y = cJSON_GetArrayItem(v, 1);
    z = cJSON_GetArrayItem(v, 2);
    if (x != NULL && y != NULL && z != NULL)
        cylinder->v = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of cylinder dir vector!\n");
    ft_object_push(game, cylinder);
}

cl_float3 triangle_norm(cl_float3 *vertices)
{
    cl_float3 ab;
	cl_float3 ac;

	ab = vector_diff(vertices[1], vertices[0]);
	ac = vector_diff(vertices[2], vertices[0]);
    return(normalize(cross(ab, ac)));
}

void parse_triangle(const cJSON *object, t_game *game)
{
    cJSON *color;
    cJSON *emition;
    cJSON *reflection;
    cJSON *texture;
    cJSON *a;
    cJSON *b;
    cJSON *c;
    cJSON *x;
    cJSON *y;
    cJSON *z;
    t_obj *triangle;

    triangle = (t_obj*)malloc(sizeof(t_obj));
    triangle->type = TRIANGLE;
    a = cJSON_GetObjectItemCaseSensitive(object, "a");
    x = cJSON_GetArrayItem(a, 0);
    y = cJSON_GetArrayItem(a, 1);
    z = cJSON_GetArrayItem(a, 2);
    if (x != NULL && y != NULL && z != NULL)
        triangle->vertices[0] = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of triangle's first vertice!\n");
    b = cJSON_GetObjectItemCaseSensitive(object, "b");
    x = cJSON_GetArrayItem(b, 0);
    y = cJSON_GetArrayItem(b, 1);
    z = cJSON_GetArrayItem(b, 2);
    if (x != NULL && y != NULL && z != NULL)
        triangle->vertices[1] = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of triangle's second vertice!\n");
    c = cJSON_GetObjectItemCaseSensitive(object, "c");
    x = cJSON_GetArrayItem(c, 0);
    y = cJSON_GetArrayItem(c, 1);
    z = cJSON_GetArrayItem(c, 2);
    if (x != NULL && y != NULL && z != NULL)
        triangle->vertices[2] = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of triangle's third vertice!\n");
    color = cJSON_GetObjectItemCaseSensitive(object, "color");
    x = cJSON_GetArrayItem(color, 0);
    y = cJSON_GetArrayItem(color, 1);
    z = cJSON_GetArrayItem(color, 2);
    if (x != NULL && y != NULL && z != NULL)
        triangle->color = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of triangle color vector!\n");
    emition = cJSON_GetObjectItemCaseSensitive(object, "emition");
    if (emition != NULL)
    {
        x = cJSON_GetArrayItem(emition, 0);
        y = cJSON_GetArrayItem(emition, 1);
        z = cJSON_GetArrayItem(emition, 2);
        if (x != NULL && y != NULL && z != NULL)
            triangle->emission = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
        else
           terminate("missing data of triangle emition vector!\n"); 
    }
    else
        triangle->emission = create_cfloat3(0.0, 0.0, 0.0);
    reflection = cJSON_GetObjectItemCaseSensitive(object, "reflection");
    if (reflection != NULL)
        triangle->reflection = reflection->valuedouble;
    else
        triangle->reflection = 0.0;
    texture = cJSON_GetObjectItemCaseSensitive(object, "texture");
    if (texture != NULL)
        triangle->texture = (int)texture->valuedouble;
    else
        triangle->texture = 0;
    triangle->v = triangle_norm(triangle->vertices);
    ft_object_push(game, triangle);
}

void check_object(const cJSON *object, t_game *game)
{
    cJSON *type; 
    type = cJSON_GetObjectItemCaseSensitive(object, "type");
	if (ft_strcmp(type->valuestring, "plane") == 0)
		parse_plane(object, game);
	else if (ft_strcmp(type->valuestring, "sphere") == 0)
		parse_sphere(object, game);
	else if (ft_strcmp(type->valuestring, "cylinder") == 0)
		parse_cylinder(object, game);
	else if (ft_strcmp(type->valuestring, "cone") == 0)
		parse_cylinder(object, game);
	else if (ft_strcmp(type->valuestring, "triangle") == 0)
	    parse_triangle(object, game);
}

void check_cam(const cJSON *cam, t_game *game)
{
    cJSON *position;
	cJSON *v;
	cJSON *normal;
    cJSON *x;
    cJSON *y;
    cJSON *z;
    t_cam *camera;

	camera = (t_cam*)malloc(sizeof(t_cam));
    position = cJSON_GetObjectItemCaseSensitive(cam, "position");
    x = cJSON_GetArrayItem(position, 0);
    y = cJSON_GetArrayItem(position, 1);
    z = cJSON_GetArrayItem(position, 2);
    if (x != NULL && y != NULL && z != NULL){
        camera->position = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
        printf("cam start pos: %f,%f,%f\n", x->valuedouble, y->valuedouble, z->valuedouble);
    }
    else
        terminate("missing data of cam start pos vector!\n");
    v = cJSON_GetObjectItemCaseSensitive(cam, "dir");
    x = cJSON_GetArrayItem(v, 0);
    y = cJSON_GetArrayItem(v, 1);
    z = cJSON_GetArrayItem(v, 2);
    if (x != NULL && y != NULL && z != NULL)
        camera->direction = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of cam dir vector!\n");
    normal = cJSON_GetObjectItemCaseSensitive(cam, "normal");
    if (normal != NULL)
    {
        x = cJSON_GetArrayItem(normal, 0);
        y = cJSON_GetArrayItem(normal, 1);
        z = cJSON_GetArrayItem(normal, 2);
        if (x != NULL && y != NULL && z != NULL)
            camera->normal = create_cfloat3(x->valuedouble, y->valuedouble, z->valuedouble);
        else
           terminate("missing data of cam normal vector!\n"); 
    }
    else
        camera->normal = create_cfloat3(0.0, 1.0, 0.0);
    camera->fov = M_PI / 3;
	reconfigure_camera(camera);
    ft_cam_push(game, camera);
}

void read_scene(char *argv, t_game *game)
{
    FILE *fp;
    char buffer[8096];
    fp = fopen(argv, "r");
    if (!fp || ft_strcmp(&argv[ft_strlen(argv) - 5], ".json") != 0)
        terminate("fuck you and your file!\n");
    fread(buffer, 8096, 1, fp);
    cJSON *json = cJSON_Parse(buffer);

    const cJSON *texture = NULL;
    const cJSON *textures = NULL;
    int i = 0;
    textures = cJSON_GetObjectItemCaseSensitive(json, "textures");
    printf("texture array size = %d\n", cJSON_GetArraySize(textures));
    game->textures_num = cJSON_GetArraySize(textures);
    game->textures = (t_txture*)malloc(sizeof(t_txture) * game->textures_num);
    cJSON_ArrayForEach(texture, textures)
    {
        get_texture(texture->valuestring, &(game->textures[i]));
        i++;
    }
    const cJSON *object = NULL;
    const cJSON *objects = NULL;
    objects = cJSON_GetObjectItemCaseSensitive(json, "objects");
    cJSON_ArrayForEach(object, objects)
    {
        check_object(object, game);
    }
    const cJSON *cam = NULL;
    const cJSON *cameras = NULL;
    cameras = cJSON_GetObjectItemCaseSensitive(json, "cameras");
    cJSON_ArrayForEach(cam, cameras)
    {
        check_cam(cam, game);
    }
    cJSON_Delete(json);
}
