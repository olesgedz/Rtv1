#ifndef RAY_H
# define RAY_H

# include "rt_cl_include.h"
# include "rt_float.h"

typedef	struct		s_ray
{
	RT_F4_API		origin;
	RT_F4_API		direction;
	RT_F			t;
}					t_ray;

#endif
