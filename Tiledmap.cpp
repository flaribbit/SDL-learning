#include "Tiledmap.h"

// https://blog.csdn.net/gouki04/article/details/7107088
unsigned char AutoTileTab[48][4]={
    18,17,14,13,//0
    2,17,14,13,//1
    18,3,14,13,//2
    2,3,14,13,//3
    18,17,14,7,//4
    2,17,14,7,//5
    18,3,14,7,//6
    2,3,14,7,//7
    18,17,6,13,//8
    2,17,6,13,//9
    18,3,6,13,//10
    2,3,6,13,//11
    18,17,6,7,//12
    2,17,6,7,//13
    18,3,6,7,//14
    2,3,6,7,//15

    16,17,12,13,//16
    16,3,12,13,//17
    16,17,12,7,//18
    16,3,12,7,//19

    10,9,14,13,//20
    10,9,14,7,//21
    10,9,6,13,//22
    10,9,6,7,//23

    18,19,14,15,//24
    18,19,6,15,//25
    2,19,14,15,//26
    2,19,6,15,//27

    18,17,22,21,//28
    2,17,22,21,//29
    18,3,22,21,//30
    2,3,22,21,//31

    16,19,12,15,//32
    10,9,22,21,//33
    8,9,12,13,//34
    8,9,12,7,//35
    10,11,14,15,//36
    10,11,6,15,//37
    18,19,22,23,//38
    2,19,22,23,//39
    16,17,20,21,//40
    16,3,20,21,//41

    8,11,12,15,//42
    8,9,20,21,//43
    16,19,20,23,//44
    10,11,22,23,//45
    0,1,4,5,//46
    8,11,20,23,//47
};

Tiledmap::Tiledmap(){
    this->image=new Image("TileA5.png");
    this->autotile=new Image("TileA2.png");
    this->w=16;
    this->h=16;
    this->size=this->w*this->h;
    this->tilesize=32;
    this->layer=new int[this->size];
    for(int i=0;i<this->w*this->h;i++){
        this->layer[i]=i%128;
    }
}

Tiledmap::Tiledmap(const char *filename){
    delete []this->layer;
}

Tiledmap::~Tiledmap(){
    delete this->image;
}

inline void GetTile(SDL_Rect &src,int tilesize,int width,int index){
    int y=index/width,x=index-y*width;
    src.x=x*tilesize;
    src.y=y*tilesize;
}

void Tiledmap::Draw(double cameraX,double cameraY){
    int mapX=(int)cameraX,mapY=(int)cameraY;
    int displayX=SCREEN_WIDTH/this->tilesize+1,displayY=SCREEN_HEIGHT/this->tilesize+1;
    int startX=mapX/this->tilesize,startY=mapY/this->tilesize;
    int offsetX=startX*this->tilesize-mapX,offsetY=startY*this->tilesize-mapY;
    SDL_Rect src={0,0,this->tilesize,this->tilesize},dst=src;
    int tilesetW=this->image->GetWidth()/this->tilesize;
    SDL_Texture *texture=this->image->GetTexture();
    dst.y=offsetY;
    for(int iy=startY;iy<startY+displayY;iy++,dst.y+=this->tilesize){
        if(iy>=0&&iy<this->h){
            int index=iy*this->w+startX;
            dst.x=offsetX;
            for(int ix=startX;ix<startX+displayX;ix++,dst.x+=this->tilesize,index++){
                if(ix>=0&&ix<this->w){
                    unsigned int tileID=this->layer[index];
                    GetTile(src,this->tilesize,tilesetW,tileID);
                    SDL_RenderCopy(renderer,texture,&src,&dst);
                }
            }
        }
    }
}

SDL_Rect *Tiledmap::GetSmallTileRect(int index){
    return GetSmallTileRect(index,0);
}

SDL_Rect *Tiledmap::GetSmallTileRect(int index, int frame){
    static SDL_Rect rect={0,0,16,16};
    rect.x=64*frame+index%4*16;
    rect.y=index/4*16;
    return &rect;
}

void Tiledmap::AutoTileTest(){
    SDL_Texture *texture=this->autotile->GetTexture();
    SDL_Rect dst={0,0,16,16};
    for(int i=0;i<48;i++){
        SDL_Rect *src=GetSmallTileRect(AutoTileTab[i][0],0);
        dst.x=i%8*32;
        dst.y=i/8*32;
        SDL_RenderCopy(renderer,texture,src,&dst);
        dst.x+=16;
        src=GetSmallTileRect(AutoTileTab[i][1],0);
        SDL_RenderCopy(renderer,texture,src,&dst);
        dst.y+=16;
        dst.x-=16;
        src=GetSmallTileRect(AutoTileTab[i][2],0);
        SDL_RenderCopy(renderer,texture,src,&dst);
        dst.x+=16;
        src=GetSmallTileRect(AutoTileTab[i][3],0);
        SDL_RenderCopy(renderer,texture,src,&dst);
    }
}
