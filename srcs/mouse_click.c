#include "rtv1.h"

void process_left_click(int x, int y, t_gpu *gpu)
{
    gpu->active_mouse_move = !gpu->active_mouse_move;
    if (gpu->active_mouse_move)
    {
        printf("clicked left pos = (%i, %i)\n", x, y);
    }
    else
    {
        /* code */
    }
    
}