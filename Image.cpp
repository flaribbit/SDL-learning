#include "Image.h"

Image::Image(const char *filename){
    this->surface=IMG_Load(filename);
    if(!this->surface){
        Error("Error loading image file.");
        return;
    }
    this->texture=SDL_CreateTextureFromSurface(renderer,this->surface);
    if(!this->texture){
        Error("Error creating texture.");
        return;
    }
}

Image::Image(SDL_Surface *surface){
    this->surface=surface;
    this->texture=SDL_CreateTextureFromSurface(renderer,this->surface);
    if(!this->texture){
        Error("Error creating texture.");
        return;
    }
}

Image::~Image()
{
    SDL_DestroyTexture(this->texture);
    SDL_FreeSurface(this->surface);
}

void Image::Draw(int x,int y){
    SDL_Rect dst={x,y,this->surface->w,this->surface->h};
    SDL_RenderCopy(renderer,this->texture,NULL,&dst);
}

int Image::GetWidth(){
    return this->surface->w;
}

int Image::GetHeight(){
    return this->surface->h;
}

SDL_Texture *Image::GetTexture(){
    return this->texture;
}
