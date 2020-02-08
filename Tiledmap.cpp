#include "Tiledmap.h"

Tiledmap::Tiledmap(){
    this->image=new Image("TileA5.png");
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
