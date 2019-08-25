#ifndef OBJECT_H
# define OBJECT_H

# include "rt_parameters.h"
# include "material.h"

typedef enum		e_object_type
{
	object_light_point,
	object_light_direct,
	object_sphere,
	object_plane
}					t_object_type;

typedef struct		s_object
{
	int				id;
	t_object_type	type;
	t_material		material;
	char			data[OBJECT_DATA_CAPACITY];
}					t_object;

#endif
