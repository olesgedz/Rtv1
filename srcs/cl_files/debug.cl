void print_ray(t_scene *scene, t_ray* ray)
{
	if (scene->x_coord == 50 && scene->y_coord == 50)
		printf("d %f\n", ray->t);
}

// void check_random(int work_item_id, int seed0, int seed1)
// {
// 	if(work_item_id == 0)
// 	{
// 		int inside_circle = 0;
// 		int N = 1000;
// 		for (int i = 0; i < N; i++)
// 		{
// 			float x = 2 * rand(seed0) - 1;
// 			float y = 2 * rand(seed1) -1;
// 			if (x* x + y * y < 1)
// 				inside_circle++;
// 		}
// 		printf("\n\n Pi = %f\n\n", 4*float(inside_circle)/N);
// 	}
// }