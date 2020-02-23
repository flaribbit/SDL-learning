#include "Image.h"

Image::Image(const char *filename){
    this->raw=NULL;
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
    this->raw=NULL;
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

void Image::SetTone(int r,int g,int b,int gray){
    if(!this->raw){
        this->raw=SDL_ConvertSurface(this->surface,this->surface->format,SDL_SWSURFACE);
    }
    unsigned char (*raw)[4]=(unsigned char (*)[4])this->raw->pixels;
    unsigned char (*p)[4]=(unsigned char (*)[4])this->surface->pixels;
    for(int i=0;i<this->surface->w*this->surface->h;i++){
        unsigned char *pixel=*p++;
        unsigned char *pixel_raw=*raw++;
        pixel[0]=LIMIT(pixel_raw[0]+r,0,255);
        pixel[1]=LIMIT(pixel_raw[1]+g,0,255);
        pixel[2]=LIMIT(pixel_raw[2]+b,0,255);
        if(gray){
            int t=(pixel[0]*299+pixel[1]*587+pixel[2]*114)/1000;
            pixel[0]=((255-gray)*pixel[0]+gray*t)/255;
            pixel[1]=((255-gray)*pixel[1]+gray*t)/255;
            pixel[2]=((255-gray)*pixel[2]+gray*t)/255;
        }
    }
    SDL_DestroyTexture(this->texture);
    this->texture=SDL_CreateTextureFromSurface(renderer,this->surface);
}

void Image::ApplyTone(){
    if(this->raw){
        SDL_FreeSurface(this->raw);
    }
}

SDL_Texture *Image::GetTexture(){
    return this->texture;
}
