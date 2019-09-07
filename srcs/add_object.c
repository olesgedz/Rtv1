#include "rtv1.h"

t_obj *add_sphere(cl_float3 position, float radius, cl_float3 color, cl_float3 emition, cl_int texture, cl_float reflection)
{
    t_obj *sphere;
    
    sphere = (t_obj*)malloc(sizeof(t_obj));
    sphere->type = SPHERE;
    sphere->position = position;
    sphere->radius = radius;
    sphere->color = color;
	sphere->emission = emition;
	sphere->texture = texture;
	sphere->reflection = reflection;
    return (sphere);
}

t_obj *add_plane(cl_float3 position, cl_float3 color, cl_float3 emition, cl_int texture, cl_float reflection, cl_float3 v)
{
    t_obj *plane;

    plane = (t_obj*)malloc(sizeof(t_obj));
    plane->type = PLANE;
    plane->position = position;
    plane->v = v;
    plane->color = color;
	plane->emission = emition;
	plane->reflection = reflection;
	plane->texture = texture;
    return (plane);
}

t_obj *add_cylinder(cl_float3 position, float radius, cl_float3 color, cl_float3 emition, cl_int texture, cl_float reflection, cl_float3 v)
{
    t_obj *cylinder;

    cylinder = (t_obj*)malloc(sizeof(t_obj));
    cylinder->type = CYLINDER;
    cylinder->position = position;
    cylinder->v = v;
    cylinder->radius = radius;
    cylinder->color = color;
	cylinder->emission = emition;
	cylinder->texture = texture;
	cylinder->reflection = reflection;
    return (cylinder);
}

t_obj *add_cone(cl_float3 position, float radius, cl_float3 color, cl_float3 emition, cl_int texture, cl_float reflection, cl_float3 v)
{
    t_obj *cone;
    
    cone = (t_obj*)malloc(sizeof(t_obj));
    cone->type = CONE;
    cone->position = position;
    cone->v = v;
    cone->radius = radius;
    cone->color = color;
	cone->emission = emition;
	cone->texture = texture;
	cone->reflection = reflection;
    return(cone);
}

void			reconfigure_camera(t_cam *camera)
{
	cl_float3	up;
	cl_float3	down;
	cl_float3	right;
	cl_float3	left;
	float		x_fov;
	float		y_fov;

	x_fov = camera->fov / 2;
	y_fov = camera->fov / 2;
	left = rotate(camera->normal, camera->direction, x_fov);
	right = rotate(camera->normal, camera->direction, -x_fov);
	up = rotate(cross(camera->direction, camera->normal), camera->direction, y_fov);
	down = rotate(cross(camera->direction, camera->normal), camera->direction, -y_fov);
	camera->border_y = vector_diff(left, right);
	camera->border_x = vector_diff(up, down);
}

t_cam *add_cam(cl_float3 position, cl_float3 direction, cl_float3 normal)
{
    t_cam		*camera;

	camera = (t_cam*)malloc(sizeof(t_cam));
	camera->normal = normal;
	camera->direction = direction;
	camera->position =position;
    camera->fov = M_PI / 3;
	reconfigure_camera(camera);
	return (camera);
}
// t_obj *add_triangle(t_vector *vertices, int color)
// {
//     t_obj *triangle;
//     t_vector ab;
// 	t_vector ac;

// 	ab = vector_diff(vertices[1], vertices[0]);
// 	ac = vector_diff(vertices[2], vertices[0]);
//     triangle = (t_obj*)malloc(sizeof(t_obj));
//     // triangle->plane_norm = vector_normalize(cross_product(ab, ac));
//     triangle->plane_norm = cross_product(ab, ac);
//     triangle->type = TRIANGLE;
//     triangle->vertices = vertices;
//     triangle->color = color;
//     return(triangle);
// }