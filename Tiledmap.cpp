#include "Tiledmap.h"

Tiledmap::Tiledmap(){
    this->image=new Image("TileA5.png");
    this->w=32;
    this->h=24;
    this->layer=new unsigned int[this->w*this->h];
}

Tiledmap::Tiledmap(const char *filename){
    delete []this->layer;
}

Tiledmap::~Tiledmap(){
    delete this->image;
}

void GetTile(SDL_Rect &src,int tilesize,int width,int index){
    int y=index/width,x=index-y*width;
    src.x=x*tilesize;
    src.y=y*tilesize;
}

void Tiledmap::Draw(double cameraX,double cameraY){
    int mapX=(int)cameraX,mapY=(int)cameraY;
    int displayX=SCREEN_WIDTH/this->tilesize+1,displayY=SCREEN_HEIGHT/this->tilesize+1;
    int indexX=mapX/this->tilesize,indexY=mapY/this->tilesize;
    int offsetX=indexX*this->tilesize-mapX,offsetY=indexY*this->tilesize-mapY;
    SDL_Rect src={0,0,this->tilesize,this->tilesize},dst=src;
    int tilesetW=this->image->GetWidth();
    SDL_Texture *texture=this->image->GetTexture();
    for(int iy=0;iy<displayY;iy++){
        int index=(iy+indexY)*this->w+indexX;
        dst.x=offsetX;
        dst.y=offsetY+this->tilesize*iy;
        for(int ix=0;ix<displayX;ix++,dst.x++){
            unsigned int tileID=this->layer[index];
            GetTile(src,this->tilesize,tilesetW,tileID);
            SDL_RenderCopy(renderer,texture,&src,&dst);
        }
    }
}
