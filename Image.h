#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "System.h"
#pragma once
class Image
{
private:
    SDL_Surface *surface;
    SDL_Texture *texture;
public:
    Image(const char *filename);
    Image(SDL_Surface *surface);
    ~Image();
    void Draw(int x,int y);
    int GetWidth();
    int GetHeight();
    SDL_Texture *GetTexture();
};
