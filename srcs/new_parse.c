/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbrella <sbrella@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 16:16:59 by david             #+#    #+#             */
/*   Updated: 2019/10/23 21:54:43 by sbrella          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "errno.h"

//если при добавлении очередного объекта в json файл программа не работает,
//попробуй увеличить размер buffer в функции read_scene



typedef struct  s_json
{
    cJSON *position;
    cJSON *color;
    cJSON *emition;
    cJSON *reflection;
    cJSON *texture;
    cJSON *radius;
    cJSON *v;
    cJSON *x;
    cJSON *y;
    cJSON *z;
    cJSON *a;
    cJSON *b;
    cJSON *c;
    cJSON *shift;
    cJSON *x_basis;
    cJSON *y_basis;
    cJSON *z_basis;
    cJSON *rotation;
    cJSON *prolapse;
    cJSON *type;
    cJSON *normal;
}               t_json;

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
    t_json parse;

    plane = (t_obj*)malloc(sizeof(t_obj));
    plane->type = PLANE;
    parse.position = cJSON_GetObjectItemCaseSensitive(object, "position");
    parse.x = cJSON_GetArrayItem(parse.position, 0);
    parse.y = cJSON_GetArrayItem(parse.position, 1);
    parse.z = cJSON_GetArrayItem(parse.position, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        plane->position = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        //printf("my start pos: %f,%f,%f\n", x->valuedouble, y->valuedouble, z->valuedouble);
    else
        terminate("missing data of plane start pos vector!\n");
    // killer(x, y, z);
    parse.color = cJSON_GetObjectItemCaseSensitive(object, "color");
    parse.x = cJSON_GetArrayItem(parse.color, 0);
    parse.y = cJSON_GetArrayItem(parse.color, 1);
    parse.z = cJSON_GetArrayItem(parse.color, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        plane->color = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of plane color vector!\n");
    // killer(x, y, z);
    parse.v = cJSON_GetObjectItemCaseSensitive(object, "dir");
    parse.x = cJSON_GetArrayItem(parse.v, 0);
    parse.y = cJSON_GetArrayItem(parse.v, 1);
    parse.z = cJSON_GetArrayItem(parse.v, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        plane->v = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of plane dir vector!\n");
    // killer(x, y, z);
    parse.emition = cJSON_GetObjectItemCaseSensitive(object, "emition");
    if (parse.emition != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.emition, 0);
        parse.y = cJSON_GetArrayItem(parse.emition, 1);
        parse.z = cJSON_GetArrayItem(parse.emition, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            plane->emission = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of plane emition vector!\n");
        // killer(x, y, z); 
    }
    else
        plane->emission = create_cfloat3(0.0, 0.0, 0.0);
    parse.reflection = cJSON_GetObjectItemCaseSensitive(object, "reflection");
    if (parse.reflection != NULL)
        plane->reflection = parse.reflection->valuedouble;
    else
        plane->reflection = 0.0;
    parse.texture = cJSON_GetObjectItemCaseSensitive(object, "texture");
    if (parse.texture != NULL)
        plane->texture = (int)parse.texture->valuedouble;
    else
        plane->texture = 0;
    parse.normal = cJSON_GetObjectItemCaseSensitive(object, "normal");
    if (parse.normal != NULL)
        plane->normal = (int)parse.normal->valuedouble;
    else
        plane->normal = 0;
    parse.shift = cJSON_GetObjectItemCaseSensitive(object, "shift");
    if (parse.shift != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.shift, 0);
        parse.y = cJSON_GetArrayItem(parse.shift, 1);
        if (parse.x != NULL && parse.y != NULL)
            plane->shift = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of plane shift vector!\n");
    }
    else
        plane->shift = create_cfloat2(0.0, 0.0);
    parse.x_basis = cJSON_GetObjectItemCaseSensitive(object, "x_basis");
    if (parse.x_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.x_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.x_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.x_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            plane->basis[0] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of plane x_basis vector!\n");    
    }
    else
    {
        if (plane->v.s[0] != 0.0f || plane->v.s[1] != 0.0f)
            plane->basis[0] = normalize(create_cfloat3(plane->v.s[1], -plane->v.s[0], 0));
        else
            plane->basis[0] = create_cfloat3(0.0f, 1.0f, 0.0f);
    }
    parse.y_basis = cJSON_GetObjectItemCaseSensitive(object, "y_basis");
    if (parse.y_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.y_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.y_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.y_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            plane->basis[1] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of plane y_basis vector!\n");    
    }
    else
        plane->basis[1] = cross(plane->v, plane->basis[0]);
    parse.z_basis = cJSON_GetObjectItemCaseSensitive(object, "z_basis");
    if (parse.z_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.z_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.z_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.z_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            plane->basis[2] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of plane z_basis vector!\n");    
    }
    else
        plane->basis[2] = create_cfloat3(0.0, 0.0, 1.0);
    parse.rotation = cJSON_GetObjectItemCaseSensitive(object, "rotation");
    if (parse.rotation != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.rotation, 0);
        parse.y = cJSON_GetArrayItem(parse.rotation, 1);
        if (parse.x != NULL && parse.y != NULL)
            plane->rotation = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of plane rotation vector!\n");
    }
    else
        plane->rotation = create_cfloat2(0.0, 0.0);
    parse.prolapse = cJSON_GetObjectItemCaseSensitive(object, "prolapse");
    if (parse.prolapse != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.prolapse, 0);
        parse.y = cJSON_GetArrayItem(parse.prolapse, 1);
        if (parse.x != NULL && parse.y != NULL)
            plane->prolapse = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of plane prolapse vector!\n");
    }
    else
        plane->prolapse = create_cfloat2(1000.0, 1000.0);
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
    t_json parse;

    sphere = (t_obj*)malloc(sizeof(t_obj));
    sphere->type = SPHERE;
    parse.position = cJSON_GetObjectItemCaseSensitive(object, "position");
    parse.x = cJSON_GetArrayItem(parse.position, 0);
    parse.y = cJSON_GetArrayItem(parse.position, 1);
    parse.z = cJSON_GetArrayItem(parse.position, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        sphere->position = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of sphere start pos vector!\n");
    parse.color = cJSON_GetObjectItemCaseSensitive(object, "color");
    parse.x = cJSON_GetArrayItem(parse.color, 0);
    parse.y = cJSON_GetArrayItem(parse.color, 1);
    parse.z = cJSON_GetArrayItem(parse.color, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        sphere->color = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of sphere color vector!\n");
    parse.radius = cJSON_GetObjectItemCaseSensitive(object, "radius");
    if (parse.radius != NULL)
        sphere->radius = parse.radius->valuedouble;
    else
        terminate("missing data of sphere radius!\n");
    parse.emition = cJSON_GetObjectItemCaseSensitive(object, "emition");
    if (parse.emition != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.emition, 0);
        parse.y = cJSON_GetArrayItem(parse.emition, 1);
        parse.z = cJSON_GetArrayItem(parse.emition, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            sphere->emission = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of sphere emition vector!\n"); 
    }
    else
        sphere->emission = create_cfloat3(0.0, 0.0, 0.0);
    parse.reflection = cJSON_GetObjectItemCaseSensitive(object, "reflection");
    if (parse.reflection != NULL)
        sphere->reflection = parse.reflection->valuedouble;
    else
        sphere->reflection = 0.0;
    parse.texture = cJSON_GetObjectItemCaseSensitive(object, "texture");
    if (parse.texture != NULL)
        sphere->texture = (int)parse.texture->valuedouble;
    else
        sphere->texture = 0;
    parse.normal = cJSON_GetObjectItemCaseSensitive(object, "normal");
    if (parse.normal != NULL)
        sphere->normal = (int)parse.normal->valuedouble;
    else
        sphere->normal = 0;
    parse.shift = cJSON_GetObjectItemCaseSensitive(object, "shift");
    if (parse.shift != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.shift, 0);
        parse.y = cJSON_GetArrayItem(parse.shift, 1);
        if (parse.x != NULL && parse.y != NULL)
            sphere->shift = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of sphere shift vector!\n");
    }
    else
        sphere->shift = create_cfloat2(0.0, 0.0);
    parse.x_basis = cJSON_GetObjectItemCaseSensitive(object, "x_basis");
    if (parse.x_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.x_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.x_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.x_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            sphere->basis[0] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of sphere x_basis vector!\n");    
    }
    else
        sphere->basis[0] = create_cfloat3(1.0, 0.0, 0.0);
    parse.y_basis = cJSON_GetObjectItemCaseSensitive(object, "y_basis");
    if (parse.y_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.y_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.y_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.y_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            sphere->basis[1] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of sphere y_basis vector!\n");
    }
    else
        sphere->basis[1] = create_cfloat3(0.0, 1.0, 0.0);
    parse.z_basis = cJSON_GetObjectItemCaseSensitive(object, "z_basis");
    if (parse.z_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.z_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.z_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.z_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            sphere->basis[2] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of sphere z_basis vector!\n");    
    }
    else
        sphere->basis[2] = create_cfloat3(0.0, 0.0, 1.0);
    parse.rotation = cJSON_GetObjectItemCaseSensitive(object, "rotation");
    if (parse.rotation != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.rotation, 0);
        parse.y = cJSON_GetArrayItem(parse.rotation, 1);
        if (parse.x != NULL && parse.y != NULL)
            sphere->rotation = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of sphere rotation vector!\n");
    }
    else
        sphere->rotation = create_cfloat2(0.0, 0.0);
    parse.prolapse = cJSON_GetObjectItemCaseSensitive(object, "prolapse");
    if (parse.prolapse != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.prolapse, 0);
        parse.y = cJSON_GetArrayItem(parse.prolapse, 1);
        if (parse.x != NULL && parse.y != NULL)
            sphere->prolapse = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of sphere prolapse vector!\n");
    }
    else
        sphere->prolapse = create_cfloat2(1000.0, 1000.0);
    ft_object_push(game, sphere);
}

void parse_cylinder(const cJSON *object, t_game *game)
{
    t_obj *cylinder;
    t_json parse;

    cylinder = (t_obj*)malloc(sizeof(t_obj));
    
    cylinder->type = CYLINDER;
    parse.type = cJSON_GetObjectItemCaseSensitive(object, "type");
    if (ft_strcmp(parse.type->valuestring, "cone") == 0)
        cylinder->type = CONE;
    parse.position = cJSON_GetObjectItemCaseSensitive(object, "position");
    parse.x = cJSON_GetArrayItem(parse.position, 0);
    parse.y = cJSON_GetArrayItem(parse.position, 1);
    parse.z = cJSON_GetArrayItem(parse.position, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        cylinder->position = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of cylinder start pos vector!\n");
    parse.color = cJSON_GetObjectItemCaseSensitive(object, "color");
    parse.x = cJSON_GetArrayItem(parse.color, 0);
    parse.y = cJSON_GetArrayItem(parse.color, 1);
    parse.z = cJSON_GetArrayItem(parse.color, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        cylinder->color = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of cylinder color vector!\n");
    parse.radius = cJSON_GetObjectItemCaseSensitive(object, "radius");
    if (parse.radius != NULL)
        cylinder->radius = parse.radius->valuedouble;
    else
        terminate("missing data of cylinder radius!\n");
    parse.emition = cJSON_GetObjectItemCaseSensitive(object, "emition");
    if (parse.emition != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.emition, 0);
        parse.y = cJSON_GetArrayItem(parse.emition, 1);
        parse.z = cJSON_GetArrayItem(parse.emition, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            cylinder->emission = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of cylinder emition vector!\n"); 
    }
    else
        cylinder->emission = create_cfloat3(0.0, 0.0, 0.0);
    parse.reflection = cJSON_GetObjectItemCaseSensitive(object, "reflection");
    if (parse.reflection != NULL)
        cylinder->reflection = parse.reflection->valuedouble;
    else
        cylinder->reflection = 0.0;
    parse.texture = cJSON_GetObjectItemCaseSensitive(object, "texture");
    if (parse.texture != NULL)
        cylinder->texture = (int)parse.texture->valuedouble;
    else
        cylinder->texture = 0;
    parse.normal = cJSON_GetObjectItemCaseSensitive(object, "normal");
    if (parse.normal != NULL)
        cylinder->normal = (int)parse.normal->valuedouble;
    else
        cylinder->normal = 0;
    parse.v = cJSON_GetObjectItemCaseSensitive(object, "dir");
    parse.x = cJSON_GetArrayItem(parse.v, 0);
    parse.y = cJSON_GetArrayItem(parse.v, 1);
    parse.z = cJSON_GetArrayItem(parse.v, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        cylinder->v = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of cylinder dir vector!\n");
    parse.shift = cJSON_GetObjectItemCaseSensitive(object, "shift");
    if (parse.shift != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.shift, 0);
        parse.y = cJSON_GetArrayItem(parse.shift, 1);
        if (parse.x != NULL && parse.y != NULL)
            cylinder->shift = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of cylinder shift vector!\n");
    }
    else
        cylinder->shift = create_cfloat2(0.0, 0.0);
    parse.x_basis = cJSON_GetObjectItemCaseSensitive(object, "x_basis");
    if (parse.x_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.x_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.x_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.x_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            cylinder->basis[0] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of cylinder x_basis vector!\n");    
    }
    else
    {
        if (cylinder->v.s[0] != 0.0f || cylinder->v.s[1] != 0.0f)
            cylinder->basis[0] = normalize(create_cfloat3(cylinder->v.s[1], -cylinder->v.s[0], 0));
        else
            cylinder->basis[0] = create_cfloat3(0.0f, 1.0f, 0.0f);
    }
    parse.y_basis = cJSON_GetObjectItemCaseSensitive(object, "y_basis");
    if (parse.y_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.y_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.y_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.y_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            cylinder->basis[1] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of cylinder y_basis vector!\n");    
    }
    else
        cylinder->basis[1] = cross(cylinder->basis[0], cylinder->v);
    parse.z_basis = cJSON_GetObjectItemCaseSensitive(object, "z_basis");
    if (parse.z_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.z_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.z_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.z_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            cylinder->basis[2] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of cylinder z_basis vector!\n");    
    }
    else
        cylinder->basis[2] = create_cfloat3(0.0, 0.0, 1.0);
    parse.rotation = cJSON_GetObjectItemCaseSensitive(object, "rotation");
    if (parse.rotation != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.rotation, 0);
        parse.y = cJSON_GetArrayItem(parse.rotation, 1);
        if (parse.x != NULL && parse.y != NULL)
            cylinder->rotation = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of cylinder rotation vector!\n");
    }
    else
        cylinder->rotation = create_cfloat2(0.0, 0.0);
    parse.prolapse = cJSON_GetObjectItemCaseSensitive(object, "prolapse");
    if (parse.prolapse != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.prolapse, 0);
        parse.y = cJSON_GetArrayItem(parse.prolapse, 1);
        if (parse.x != NULL && parse.y != NULL)
            cylinder->prolapse = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of cylinder prolapse vector!\n");
    }
    else
        cylinder->prolapse = create_cfloat2(1000.0, 1000.0);
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
    t_json parse;
    t_obj *triangle;

    triangle = (t_obj*)malloc(sizeof(t_obj));
    triangle->type = TRIANGLE;
    parse.a = cJSON_GetObjectItemCaseSensitive(object, "a");
    parse.x = cJSON_GetArrayItem(parse.a, 0);
    parse.y = cJSON_GetArrayItem(parse.a, 1);
    parse.z = cJSON_GetArrayItem(parse.a, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        triangle->vertices[0] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of triangle's first vertice!\n");
    parse.b = cJSON_GetObjectItemCaseSensitive(object, "b");
    parse.x = cJSON_GetArrayItem(parse.b, 0);
    parse.y = cJSON_GetArrayItem(parse.b, 1);
    parse.z = cJSON_GetArrayItem(parse.b, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        triangle->vertices[1] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of triangle's second vertice!\n");
    parse.c = cJSON_GetObjectItemCaseSensitive(object, "c");
    parse.x = cJSON_GetArrayItem(parse.c, 0);
    parse.y = cJSON_GetArrayItem(parse.c, 1);
    parse.z = cJSON_GetArrayItem(parse.c, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        triangle->vertices[2] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of triangle's third vertice!\n");
    parse.color = cJSON_GetObjectItemCaseSensitive(object, "color");
    parse.x = cJSON_GetArrayItem(parse.color, 0);
    parse.y = cJSON_GetArrayItem(parse.color, 1);
    parse.z = cJSON_GetArrayItem(parse.color, 2);
    if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
        triangle->color = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
    else
        terminate("missing data of triangle color vector!\n");
    parse.emition = cJSON_GetObjectItemCaseSensitive(object, "emition");
    if (parse.emition != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.emition, 0);
        parse.y = cJSON_GetArrayItem(parse.emition, 1);
        parse.z = cJSON_GetArrayItem(parse.emition, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            triangle->emission = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of triangle emition vector!\n"); 
    }
    else
        triangle->emission = create_cfloat3(0.0, 0.0, 0.0);
    parse.reflection = cJSON_GetObjectItemCaseSensitive(object, "reflection");
    if (parse.reflection != NULL)
        triangle->reflection = parse.reflection->valuedouble;
    else
        triangle->reflection = 0.0;
    parse.texture = cJSON_GetObjectItemCaseSensitive(object, "texture");
    if (parse.texture != NULL)
        triangle->texture = (int)parse.texture->valuedouble;
    else
        triangle->texture = 0;
    parse.normal = cJSON_GetObjectItemCaseSensitive(object, "normal");
    if (parse.normal != NULL)
        triangle->normal = (int)parse.normal->valuedouble;
    else
        triangle->normal = 0;
    triangle->v = triangle_norm(triangle->vertices);
    parse.shift = cJSON_GetObjectItemCaseSensitive(object, "shift");
    if (parse.shift != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.shift, 0);
        parse.y = cJSON_GetArrayItem(parse.shift, 1);
        if (parse.x != NULL && parse.y != NULL)
            triangle->shift = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of triangle shift vector!\n");
    }
    else
        triangle->shift = create_cfloat2(0.0, 0.0);
    parse.x_basis = cJSON_GetObjectItemCaseSensitive(object, "x_basis");
    if (parse.x_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.x_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.x_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.x_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            triangle->basis[0] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of triangle x_basis vector!\n");    
    }
    else
        triangle->basis[0] = create_cfloat3(1.0, 0.0, 0.0);
    parse.y_basis = cJSON_GetObjectItemCaseSensitive(object, "y_basis");
    if (parse.y_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.y_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.y_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.y_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            triangle->basis[1] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of triangle y_basis vector!\n");    
    }
    else
        triangle->basis[1] = create_cfloat3(0.0, 1.0, 0.0);
    parse.z_basis = cJSON_GetObjectItemCaseSensitive(object, "z_basis");
    if (parse.z_basis != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.z_basis, 0);
        parse.y = cJSON_GetArrayItem(parse.z_basis, 1);
        parse.z = cJSON_GetArrayItem(parse.z_basis, 2);
        if (parse.x != NULL && parse.y != NULL && parse.z != NULL)
            triangle->basis[2] = create_cfloat3(parse.x->valuedouble, parse.y->valuedouble, parse.z->valuedouble);
        else
           terminate("missing data of triangle z_basis vector!\n");    
    }
    else
        triangle->basis[2] = create_cfloat3(0.0, 0.0, 1.0);
    parse.rotation = cJSON_GetObjectItemCaseSensitive(object, "rotation");
    if (parse.rotation != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.rotation, 0);
        parse.y = cJSON_GetArrayItem(parse.rotation, 1);
        if (parse.x != NULL && parse.y != NULL)
            triangle->rotation = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of triangle rotation vector!\n");
    }
    else
        triangle->rotation = create_cfloat2(0.0, 0.0);
    parse.prolapse = cJSON_GetObjectItemCaseSensitive(object, "prolapse");
    if (parse.prolapse != NULL)
    {
        parse.x = cJSON_GetArrayItem(parse.prolapse, 0);
        parse.y = cJSON_GetArrayItem(parse.prolapse, 1);
        if (parse.x != NULL && parse.y != NULL)
            triangle->prolapse = create_cfloat2(parse.x->valuedouble, parse.y->valuedouble);
        else
           terminate("missing data of cylinder prolapse vector!\n");
    }
    else
        triangle->prolapse = create_cfloat2(1000.0, 1000.0);
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
        get_texture(texture->valuestring, &(game->textures[i]), "./textures/");
        i++;
    }
    const cJSON *normal = NULL;
    const cJSON *normals = NULL;
    int k = 0;
    normals = cJSON_GetObjectItemCaseSensitive(json, "normals");
    printf("normals array size = %d\n", cJSON_GetArraySize(normals));
    game->normals_num = cJSON_GetArraySize(normals);
    game->normals = (t_txture*)malloc(sizeof(t_txture) * game->normals_num);
    cJSON_ArrayForEach(normal, normals)
    {
        get_texture(normal->valuestring, &(game->normals[k]), "./normals/");
        k++;
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
