#ifndef CAMERA_H
# define CAMERA_H

# include "rt_parameters.h"
# include "rt_float.h"

# include "f4.h"
# include "libft_standart.h"
# include "ray.h"

# include <stdlib.h>
# include <math.h>

typedef struct 		s_camera
{
	RT_F4_API		position;
	RT_F4_API		axis_x;
	RT_F4_API		axis_y;
	RT_F4_API		axis_z;
	RT_F4_API		forward;
	int				width;
	int				height;
}					t_camera;

t_camera			*camera_new(INT_REF width, INT_REF height);
void 				camera_delete(t_camera **camera);

typedef enum		e_camera_direction
{
	left,
	right,
	up,
	down,
	forward,
	backward
}					t_camera_direction;

void 				camera_move
					(t_camera *camera,
					t_camera_direction direction,
					RT_F length);

#endif
