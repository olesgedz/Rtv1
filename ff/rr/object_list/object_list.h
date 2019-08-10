#ifndef OBJECT_DATA_H
# define OBJECT_DATA_H

# include "rt_cl_include.h"
# include "rt_float.h"

typedef struct		s_object_sphere
{
	RT_F4_API		position;
	RT_F			radius;
}					t_object_sphere;

typedef struct		s_object_plane
{
	RT_F4_API		position;
	RT_F4_API		normal;
}					t_object_plane;

#endif
