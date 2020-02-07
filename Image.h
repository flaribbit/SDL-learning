#include "SDL2/SDL.h"

class Image
{
private:
    SDL_Surface *surface;
    SDL_Texture *texture;
public:
    Image();
    ~Image();
};
