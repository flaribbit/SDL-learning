#include <stdio.h>
#include "Sprite.h"
#include "Control.h"
#include "Tiledmap.h"

int WinMain(int argc, char *argv[])
{
    window=SDL_CreateWindow("demo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    Tiledmap map;
    int x=0,y=0;
    for(frames=1;frames;frames++){
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        map.Draw(x,y);
        controller.Update();
        if(controller.IsDown(Control::KeyLeft)){
            x--;
        }else if(controller.IsDown(Control::KeyRight)){
            x++;
        }
        if(controller.IsDown(Control::KeyUp)){
            y--;
        }else if(controller.IsDown(Control::KeyDown)){
            y++;
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }
    return 0;
}
