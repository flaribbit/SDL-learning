#include "Image.h"

Image::Image(char *filename){
    this->surface=IMG_Load(filename);
    if(!this->surface){
        Error((char*)"Error loading image file.");
        return;
    }
    this->texture=SDL_CreateTextureFromSurface(renderer,this->surface);
    if(!this->texture){
        Error((char*)"Error creating texture.");
        return;
    }
}

Image::~Image()
{
    SDL_DestroyTexture(this->texture);
    SDL_free(this->surface);
}

void Image::Draw(int x,int y){
    SDL_Rect dst={x,y,this->surface->w,this->surface->h};
    SDL_RenderCopy(renderer,this->texture,NULL,&dst);
}
