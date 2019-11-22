#include "libsdl.h"
#include "libft.h"

int  main ()
{
    t_sdl sdl;
    ft_init_window(&sdl, 600, 600);
           SDL_Event e;
    int quit = 0;
    while(!quit)
    {
          while( SDL_PollEvent( &e ) != 0 )
                {
                    //User requests quit
                    if( e.type == SDL_QUIT )
                    {
                        quit = 1;
                    }
                }
                  
    ft_put_pixel(sdl.surface, &(t_point){50, 50}, 0xFF0000);
    ft_surface_present(&sdl, sdl.surface);
    SDL_Delay(50);
    }
}
