#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "System.h"
#pragma once

#define MIN(a,b) ((a)<(b)?(a):(b))
#define MAX(a,b) ((a)>(b)?(a):(b))
#define LIMIT(x,a,b) MIN(MAX(x,a),b);

class Image
{
private:
    SDL_Surface *raw;
    SDL_Surface *surface;
    SDL_Texture *texture;
public:
    Image(const char *filename);
    Image(SDL_Surface *surface);
    ~Image();
    void Draw(int x,int y);
    int GetWidth();
    int GetHeight();
    void SetTone(int r,int g,int b,int gray);
    void ApplyTone();
    SDL_Texture *GetTexture();
};
