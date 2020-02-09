#include <stdio.h>
#include "SDL2/SDL_ttf.h"
#include "Sprite.h"
#include "Control.h"
#include "Tiledmap.h"

int WinMain(int argc, char *argv[])
{
    window=SDL_CreateWindow("demo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    Tiledmap map;
    int x=-100,y=-100;
    TTF_Init();
    TTF_Font *font=TTF_OpenFont("loli2.ttf",18);
    SDL_Color color={255,255,255,255};
    Image text=Image(TTF_RenderUTF8_Blended(font,"测试",color));
    for(frames=1;frames;frames++){
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        map.Draw(x,y);
        text.Draw(0,0);
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
    TTF_Quit();
    return 0;
}
