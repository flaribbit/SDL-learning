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

    int param[4]={0,0,0,0};
    int select=0;
    char buf[100];
    const char *strings[4][2]={
        "红=%d",">>红<<=%d",
        "绿=%d",">>绿<<=%d",
        "蓝=%d",">>蓝<<=%d",
        "灰=%d",">>灰<<=%d",
    };
    for(frames=1;frames;frames++){
        SDL_SetRenderDrawColor(renderer,0,0,0,255);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer,255,255,255,255);
        map.Draw(x,y);
        // f.Print("设想一下：灯光微暗情人四目相对，他轻搂着她纤细柔软的腰肢，头微微右倾靠近她的脸，情不自禁地闭上眼睛",0,0);

        int bx=controller.mouseX+x;
        int by=controller.mouseY+y;
        if(bx>0&&by>0){
            int nx=bx/32;
            int ny=by/32;
            int ix=nx*32-x;
            int iy=ny*32-y;
            SDL_Point rect[]={{ix,iy},{ix+32,iy},{ix+32,iy+32},{ix,iy+32},{ix,iy}};
            SDL_RenderDrawLines(renderer,rect,5);
            if(controller.IsDown(Control::KeyMouseL)){
                map.SetTileId(ny,nx,INDEX_AUTOTILE);
                for(int dy=-1;dy<=1;dy++){
                    for(int dx=-1;dx<=1;dx++){
                        int tileid=map.GetTileId(ny+dy,nx+dx);
                        if(tileid>=INDEX_AUTOTILE&&tileid>>6==map.GetTileId(ny,nx)>>6){
                            map.RefreshAutoTile(ny+dy,nx+dx);
                        }
                    }
                }
            }
            // f.Print((sprintf(buf,"mouse=%d,%d",bx,by),buf),0,0);
        }else{
            // f.Print((sprintf(buf,"mouse=%d,%d(超出地图范围)",bx,by),buf),0,0);
        }

        f.Print("色调设置(WS选择，AD调节，J重置)",0,0);
        for(int i=0;i<4;i++){
            f.Print((sprintf(buf,strings[i][select==i],param[i]),buf),0,(i+1)*20);
        }

        controller.Update();
        if(controller.IsDown(Control::KeyLeft)){
            if(select<3){
                param[select]=LIMIT(param[select]-1,-255,255);
            }else{
                param[select]=LIMIT(param[select]-1,0,255);
            }
            map.image->SetTone(param[0],param[1],param[2],param[3]);
        }else if(controller.IsDown(Control::KeyRight)){
            if(select<3){
                param[select]=LIMIT(param[select]+1,-255,255);
            }else{
                param[select]=LIMIT(param[select]+1,0,255);
            }
            map.image->SetTone(param[0],param[1],param[2],param[3]);
        }
        if(controller.IsPress(Control::KeyUp)){
            select=LIMIT(select-1,0,3);
        }else if(controller.IsPress(Control::KeyDown)){
            select=LIMIT(select+1,0,3);
        }
        if(controller.IsPress(Control::KeyA)){
            for(int i=0;i<4;i++){
                param[i]=0;
            }
            map.image->SetTone(param[0],param[1],param[2],param[3]);
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
