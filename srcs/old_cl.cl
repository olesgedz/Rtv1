
typedef	struct 	s_vec3 t_vec3;
typedef struct s_object t_object;

struct 	s_vec3
{
	float x;
	float y;
	float z;
	float w;
};

typedef struct 	s_mat4
{
	double matrix[4][4];
} t_mat4;

typedef struct s_ray
{
	t_vec3 orig;
	t_vec3 dir;
	t_vec3 hit;
	double t;

} t_ray;

typedef struct	Material {
	t_vec3 diffuse_color;
	t_vec3 albendo;
	float specular_exponent;
	float refractive_index;
}				t_material;

struct s_object
{
	void *object;
	double (*intersect)();
	t_vec3 (*get_normal)();
}; 

typedef struct s_sphere
{
	t_vec3		center;
	t_material	material;
	float		radius;
	t_vec3		v;
	double		angle;
	t_vec3		tip;
	int			type;

} t_sphere;


typedef	struct s_cylinder
{
	t_vec3		center;
	t_material	material;
	float		radius;
	t_vec3		v;
	int			min;
	int			max;
	int			type;
}				t_cylinder;

typedef	struct		s_cone
{
	t_vec3		center;
	t_material	material;
	float		radius;
	t_vec3		v;
	double		angle;
	t_vec3		tip;
	int			type;
}					t_cone;

typedef struct s_plane
{
	t_vec3		point;
	t_vec3		normal;
	t_material	material;
	int			type;
}				t_plane;

typedef struct s_light {
	t_vec3 position;
	float intensity;
} t_light;

typedef struct	s_main_obj
{
	t_object	*figures;
	int			figures_num;
	t_light		*lights;
	int			elum_num;
	double		closest;

}				t_main_obj;

enum e_figure {PLANE, SPHERE, CYLINDER, CONE};

double		sphere_intersection(void *figure, t_ray *ray, float *t0);
double		cone_intersection(void *object, t_ray *ray, float *t0);
double		cylinder_intersection(void *object, t_ray *ray, float *t0);
double		plane_intersection(void *object, t_ray *ray, float *t0);
int			have_solutions(double d);
double		get_solution(double a, double b, double c, float *t0);

t_vec3		ft_vec3_scalar_multiply(t_vec3 a, float b);
float		ft_vec3_dot_multiply(t_vec3 a, t_vec3 b);
t_vec3		ft_vec3_substract(t_vec3 a, t_vec3 b);
float		ft_vec3_multiply_cone(t_vec3 a, t_vec3 b);
t_vec3		ft_vec3_create(float x, float y, float z);
t_vec3		ft_vec3_multiply_matrix(t_vec3 v, t_mat4 m);
t_mat4		ft_mat4_multiply_mat4(t_mat4 a, t_mat4 b);
t_mat4		ft_mat4_translation_matrix(t_vec3 v);
t_mat4		ft_mat4_rotation_matrix(t_vec3 axis, double alpha);
t_mat4		ft_mat4_identity_matrix(void);
t_vec3		ft_vec3_normalize(t_vec3 vect);
float 		ft_vec3_norm(t_vec3 vect);
// int			scene_intersect(t_game *game, t_ray *ray, t_vec3 *hit, t_vec3 *N, t_material *material);
// t_vec3		cast_ray(t_game *game, t_ray *ray, size_t depth);

//====================================//

// __kernel void init_calculations(
// 	__global t_vec3 *vecs, 
// 	__global void *objects,
// 	__constant t_light *lights,
// 	int objs_count,
// 	int lights_count,
// 	__global t_vec3 *out_vecs,
// 	const unsigned int count)
// {
// 	t_vec3 origin, dir;
// 	float xa = 0, ya = 0, za = 0;
// 	float eyex = 0, eyey = 0, eyez = 0;
// 	int id = get_global_id(0);
// 	if (id < count)
// 	{
// 		// if (id == 0)
// 		// 	for (int i = 0; i < lights_count; ++i)
// 		// 	{
// 		// 		printf("inside: %i - %f, %f, %f\n", i, lights[i].position.x,
// 		// 												lights[i].position.y,
// 		// 												lights[i].position.z);
// 		// 	}
// 		// out_vecs[id] = (t_vec3){0, vecs[id].y, vecs[id].z};
// 		//printf("%f. %f, %f\n", out_vecs[id].x, out_vecs[id].y, out_vecs[id].z);
// 		origin = ft_vec3_create(eyex, eyey, eyez);
// 		dir = ft_vec3_multiply_matrix(vecs[id], ft_mat4_rotation_matrix((t_vec3) {0,-1,0}, xa));
// 		out_vecs[id] = dir;//cast_ray(game, &(t_ray){origin, dir}, 0);
// 	}
// }


__kernel void init_calculations(__global float* x, __global float* y, __global float* z)
{	
	const int i = get_global_id(0);	
	z[i] = y[i] + x[i];
}
__kernel void render_kernel(__global float3* output, int width, int height)
{
 const int work_item_id = get_global_id(0); /* the unique global id of the work item for the current pixel */
 int x = work_item_id % width; /* x-coordinate of the pixel */
 int y = work_item_id / width; /* y-coordinate of the pixel */
 float fx = (float)x / (float)width; /* convert int to float in range [0-1] */
 float fy = (float)y / (float)height; /* convert int to float in range [0-1] */
 output[work_item_id] = (float3)(fx, fy, 0); /* simple interpolated colour gradient based on pixel coordinates */
}


float ft_vec3_norm(t_vec3 vect)
{
	return (sqrt(vect.x * vect.x + vect.y * vect.y + vect.z * vect.z));
}

float ft_vec3_dot_multiply(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

t_vec3 ft_vec3_create(float x, float y, float z)
{
	t_vec3 new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}

t_vec3 ft_vec3_normalize(t_vec3 vect)
{
	t_vec3 res = vect;
	float norm = ft_vec3_norm(res);
	res.x = vect.x / norm;
	res.y = vect.y / norm;
	res.z = vect.z / norm;
	return (res);
}

t_mat4	ft_mat4_identity_matrix(void)
{
	t_mat4	res;
	int				i;
	int				j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			res.matrix[i][j] = 0;
	}
	res.matrix[0][0] = 1;
	res.matrix[1][1] = 1;
	res.matrix[2][2] = 1;
	res.matrix[3][3] = 1;
	return (res);
}

t_vec3	ft_vec3_multiply_matrix(t_vec3 v, t_mat4 m)
{
	t_vec3	res;

	res.x = v.x * m.matrix[0][0] +
			v.y * m.matrix[0][1] +
			v.z * m.matrix[0][2] +
			v.w * m.matrix[0][3];
	res.y = v.x * m.matrix[1][0] +
			v.y * m.matrix[1][1] +
			v.z * m.matrix[1][2] +
			v.w * m.matrix[1][3];
	res.z = v.x * m.matrix[2][0] +
			v.y * m.matrix[2][1] +
			v.z * m.matrix[2][2] +
			v.w * m.matrix[2][3];
	res.w = v.x * m.matrix[3][0] +
			v.y * m.matrix[3][1] +
			v.z * m.matrix[3][2] +
			v.w * m.matrix[3][3];
	return (res);
}

t_mat4	ft_mat4_multiply_mat4(t_mat4 a, t_mat4 b)
{
	t_mat4	res;
	int				i;
	int				j;

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			res.matrix[i][j] = a.matrix[i][0] * b.matrix[0][j] +
				a.matrix[i][1] * b.matrix[1][j] +
				a.matrix[i][2] * b.matrix[2][j] +
				a.matrix[i][3] * b.matrix[3][j];
		}
	}
	return (res);
}

t_mat4	ft_mat4_translation_matrix(t_vec3 v)
{
	t_mat4	res;

	res = ft_mat4_identity_matrix();
	res.matrix[0][3] = v.x;
	res.matrix[1][3] = v.y;
	res.matrix[2][3] = v.z;
	return (res);
}

t_mat4	ft_mat4_rotation_matrix(t_vec3 axis, double alpha)
{
	t_mat4			res;
	double			sinus;
	double			cosin;
	double			inv_cosin;

	res = ft_mat4_identity_matrix();
	axis = ft_vec3_normalize(axis);
	sinus = sin(alpha);
	cosin = cos(alpha);
	inv_cosin = 1 - cosin;
	res.matrix[0][0] = cosin + inv_cosin * axis.x * axis.x;
	res.matrix[1][0] = inv_cosin * axis.x * axis.y - sinus * axis.z;
	res.matrix[2][0] = inv_cosin * axis.x * axis.z + sinus * axis.y;
	res.matrix[0][1] = inv_cosin * axis.y * axis.x + sinus * axis.z;
	res.matrix[1][1] = cosin + inv_cosin * axis.y * axis.y;
	res.matrix[2][1] = inv_cosin * axis.y * axis.z - sinus * axis.x;
	res.matrix[0][2] = inv_cosin * axis.z * axis.x - sinus * axis.y;
	res.matrix[1][2] = inv_cosin * axis.z * axis.y + sinus * axis.x;
	res.matrix[2][2] = cosin + inv_cosin * axis.z * axis.z;
	return (res);
}

int	have_solutions(double d)
{
	if (d > 0)
		return (2);
	else if (d == 0)
		return (1);
	else
		return (0);
}

double		get_solution(double a, double b, double c, float *t0)
{
	double		d;
	double		tmp1;
	double		tmp2;

	d = b * b - 4.0 * a * c;
	if (have_solutions(d) == 0)
		return (0);
	else if (have_solutions(d) == 1)
		*t0 = - b / (2 * a);
	else
	{
		tmp1 = sqrt(d);
		tmp2 = 1 / (2 * a);
		if (((*t0 = (- b - tmp1) * tmp2)) < 0.003)
			if ((*t0 = ((- b + tmp1) * tmp2)) < 0.003)
				return (0);
	}
		return (1);
}

t_vec3	ft_vec3_substract(t_vec3 a, t_vec3 b)
{
	t_vec3 new;

	new.x = (a.x - b.x);
	new.y = (a.y - b.y);
	new.z = (a.z - b.z);
	return (new);
}

float ft_vec3_multiply_cone(t_vec3 a, t_vec3 b)
{
	return (a.x * b.x - a.y * b.y + a.z * b.z);
}

t_vec3 ft_vec3_scalar_multiply(t_vec3 a, float b)
{
	return ((t_vec3){a.x * b, a.y * b, a.z * b});
}
/*--------------------intersection------------------------- */

double		sphere_intersection(void *figure, t_ray *ray, float *t0)
{
	t_sphere *sphere = (t_sphere *) ((t_object *)figure)->object;
	t_vec3 temp = ft_vec3_substract(ray->orig, sphere->center);
	double a = ft_vec3_dot_multiply(ray->dir, ray->dir);
	double b = ft_vec3_dot_multiply(ft_vec3_scalar_multiply(temp, 2), ray->dir);
	double c = ft_vec3_dot_multiply(temp, temp) - sphere->radius * sphere->radius;
	return (get_solution(a, b, c, t0));
}

double	cone_intersection(void *object, t_ray *ray, float *t0)
{
	t_vec3	x;
	double	a;
	double	b;
	double	c;
	t_cone *cone;

	cone = (t_cone *)((t_object *)object)->object;
	x = ft_vec3_substract(ray->orig, cone->center);
	a = ft_vec3_dot_multiply(ray->dir, cone->v);
	a = ft_vec3_dot_multiply(ray->dir, ray->dir) - (1 + cone->radius * cone->radius) * a * a;
	b = 2.0 * (ft_vec3_dot_multiply(ray->dir, x) - (1 + cone->radius * cone->radius)
		* ft_vec3_dot_multiply(ray->dir, cone->v) * ft_vec3_dot_multiply(x, cone->v));
	c = ft_vec3_dot_multiply(x, cone->v);
	c = ft_vec3_dot_multiply(x, x) - (1 + cone->radius * cone->radius) * c * c;
	return (get_solution(a, b, c, t0));
}

double		plane_intersection(void *object, t_ray *ray, float *t0)
{
	double tmp;
	t_plane *p;

	p = (t_plane *)((t_object *)object)->object;
	tmp = p->point.x * ray->dir.x + p->point.y * ray->dir.y + p->point.z * ray->dir.z;
	if (!tmp)
		return (0);
	*t0 = -(p->point.x * ray->orig.x +  p->point.y * ray->orig.y +  p->point.z * ray->orig.z +  p->point.w) / tmp;
	return ((*t0 >= 0.0003) ? 1 : 0);
}

double		cylinder_intersection(void *object, t_ray *ray, float *t0)
{
	t_vec3	x;
	double	a;
	double	b;
	double	c;
	t_cylinder *cylinder;
	cylinder = (t_cylinder *)((t_object *)object)->object;

	x = ft_vec3_substract(ray->orig, cylinder->center);
	a = ft_vec3_dot_multiply(ray->dir, cylinder->v);
	a = ft_vec3_dot_multiply(ray->dir, ray->dir) - a * a;
	b = 2 * (ft_vec3_dot_multiply(ray->dir, x) - ft_vec3_dot_multiply(ray->dir, cylinder->v)
		* ft_vec3_dot_multiply(x, cylinder->v));
	c = ft_vec3_dot_multiply(x, cylinder->v);
	c = ft_vec3_dot_multiply(x, x) - c * c - cylinder->radius * cylinder->radius;
	return (get_solution(a, b, c, t0));
}


/* ********************************** */


// int scene_intersect(__global t_object *objs, __global t_light *lights, int obj_num, int elum_num, t_ray *ray, t_vec3 *hit, t_vec3 *N, t_material *material)
// {
//  	game->closest = FLT_MAX; 
// 	float dist_i;
// 	float object_dist = FLT_MAX; 
// 	int i = 0;
// 	while (i < obj_num)
// 	{
// 		if (figures[i].intersect(&figures[i], ray, &dist_i) && dist_i < object_dist)
// 		{
// 			is_any_figure_closer(game, dist_i); 
// 			object_dist = dist_i;
// 			ray->t = dist_i;
// 			t_vec3 temp = ft_vec3_scalar_multiply(ray->dir, dist_i);
// 			*hit = ft_vec3_sum(ray->orig, temp);
// 			ray->hit = *hit;
// 			temp = figures[i].get_normal(ray, &figures[i]); // problem also cause of shading not working
// 			*N = ft_vec3_normalize(temp);
// 			*material = ((t_sphere *)figures[i].object)->material; // mm not suppose to be  t_sphere, but works
// 		}
// 		i++;
// 	}
// 	return game->closest < 1000;
// }

// t_vec3 cast_ray(__global t_object *objs, __global t_light *lights, int obj_num, int elum_num, t_ray *ray, size_t depth)
// {//TODO rewrite without recursion, think about 'for' loop
// 	t_vec3 point;
// 	t_vec3 N;
// 	t_material material; 
// 	int	i;
// 	float sphere_dist = FLT_MAX;

// 	if( depth > 4 || !scene_intersect(game, ray, &point, &N, &material))
// 		return ft_vec3_create(0.2, 0.7, 0.8); // background color

// 	t_ray reflect_ray;
// 	reflect_ray.dir = ft_vec3_normalize(reflect(ray->dir, N));
// 	reflect_ray.orig  = ft_vec3_dot_multiply(reflect_ray.dir, N) < 0 
// 						? ft_vec3_substract(point, ft_vec3_scalar_multiply(N, 1e-3)) 
// 						: ft_vec3_sum(point, ft_vec3_scalar_multiply(N, 1e-3));
// 	// t_vec3 reflect_color = cast_ray(game, &reflect_ray, depth + 1);
// 	t_ray refract_ray;
// 	refract_ray.dir = ft_vec3_normalize(refract(ray->dir, N, material.refractive_index, 1.0f));
// 	refract_ray.orig = ft_vec3_dot_multiply(refract_ray.dir, N) < 0 
// 						? ft_vec3_substract(point, ft_vec3_scalar_multiply(N, 1e-3)) 
// 						: ft_vec3_sum(point, ft_vec3_scalar_multiply(N, 1e-3));
// 	// t_vec3 refract_color = cast_ray(game, &refract_ray, depth + 1);
	
// 	float diffuse_light_intensity = 0;
// 	float specular_light_intensity = 0;
// 	i = -1;

// 	while (++i < elum_num)
// 	{
// 		t_vec3 light_dir      =  ft_vec3_normalize(ft_vec3_substract(lights[i].position, point));
// 		double light_distance = ft_vec3_norm(ft_vec3_substract(lights[i].position, point));
// 		t_ray shadow_ray;
// 		shadow_ray.orig = (ft_vec3_dot_multiply(light_dir, N) < 0)
// 			? ft_vec3_substract(point, ft_vec3_scalar_multiply(N, 1e-3))
// 			: ft_vec3_sum(point, ft_vec3_scalar_multiply(N, 1e-3));
// 		shadow_ray.dir = light_dir;
// 		t_vec3 shadow_pt, shadow_N;
// 		t_material temp_material;
// 		if (scene_intersect(game, &shadow_ray, &shadow_pt, &shadow_N, &temp_material) 
// 			&& (ft_vec3_norm(ft_vec3_substract(shadow_pt, shadow_ray.orig)) < light_distance))
// 			continue;
// 		diffuse_light_intensity += lights[i].intensity 
// 			* max(0.0f, ft_vec3_dot_multiply(ft_vec3_normalize(light_dir), ft_vec3_normalize(N)));
// 		specular_light_intensity += powf(max(0.f, ft_vec3_dot_multiply(ft_vec3_scalar_multiply(
// 			reflect(ft_vec3_scalar_multiply(light_dir, -1), N), -1), ray->dir)),
// 		 	material.specular_exponent)*lights[i].intensity;
// 	}
		
// 	// return ft_vec3_sum(ft_vec3_sum(ft_vec3_sum(ft_vec3_scalar_multiply(material.diffuse_color,\
// 	//  diffuse_light_intensity * material.albendo.x), \
// 	//  	 ft_vec3_scalar_multiply((t_vec3){1,1,1}, specular_light_intensity *  material.albendo.y)),\
// 	// 	 ft_vec3_scalar_multiply(reflect_color,  material.albendo.z)), ft_vec3_scalar_multiply(refract_color,  material.albendo.w));					//ft_vec3_scalar_multiply(&material.diffuse_color, diffuse_light_intensity);
// 	return ft_vec3_sum(ft_vec3_scalar_multiply(material.diffuse_color, diffuse_light_intensity * material.albendo.x), \
// 		ft_vec3_scalar_multiply((t_vec3){1,1,1}, specular_light_intensity *  material.albendo.y));
// }