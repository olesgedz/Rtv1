#include "rtv1.h"


/*
 +- 0. low sample count if need to move figure 
    1. start other opencl thread ?
    2. find intersection with first object on the way
    3. return object's index to main processor thread
    4. start moving this object
    5. unclick when done with moving
  + 6. return sample count
*/

void process_left_click(int x, int y, t_gpu *gpu)
{
    gpu->active_mouse_move = !gpu->active_mouse_move;
    printf("\nmouse intersect with %i\n\n", get_mouse_intersection(gpu, x, y));
    if (gpu->active_mouse_move)
    {
        printf("clicked left pos = (%i, %i)\n", x, y);
    }
    else
    {
        printf("unclicked left pos = (%i, %i)\n", x, y);
    }
    
}