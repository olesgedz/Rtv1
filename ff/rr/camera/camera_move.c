#include "camera.h"

void 				camera_move
					(t_camera *camera,
					t_camera_direction direction,
					RT_F length)
{
	RT_F4_API		step;

	if (direction == left)
		step = f4_mul(camera->axis_x, -1.f);
	else if (direction == right)
		step = f4_mul(camera->axis_x, 1.f);
	else if (direction == up)
		step = f4_mul(camera->axis_y, 1.f);
	else if (direction == down)
		step = f4_mul(camera->axis_y, -1.f);
	else if (direction == forward)
		step = f4_mul(camera->axis_z, -1.f);
	else if (direction == backward)
		step = f4_mul(camera->axis_z, 1.f);
	else
		return ;
	step = f4_mul(step, length);
	camera->position = f4_add(camera->position, step);
}