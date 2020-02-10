#include <stdio.h>
#include "SDL2/SDL_ttf.h"
#include "Sprite.h"
#include "Control.h"
#include "Tiledmap.h"
#include "Font.h"

int WinMain(int argc, char *argv[])
{
    window=SDL_CreateWindow("demo",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
    renderer=SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);
    Tiledmap map;
    int x=-100,y=-100;
    TTF_Init();
    Font f;
    f.NewFont("loli2.ttf",18);
    for(frames=1;frames;frames++){
        char buf[100];
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        map.Draw(x,y);
        f.Print("设想一下：灯光微暗情人四目相对，他轻搂着她纤细柔软的腰肢，头微微右倾靠近她的脸，情不自禁地闭上眼睛",0,0);
        for(int i=0;i<100;i++){
            f.Print(itoa(frames,buf,10),0,20*i);
        }
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
        if(frames%60==0){
            printf("size=%d\n",f.GetCacheLength());
        }
        SDL_RenderPresent(renderer);
        SDL_Delay(1000/60);
    }
    TTF_Quit();
    return 0;
}
