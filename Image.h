#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "System.h"

class Image
{
private:
    SDL_Surface *surface;
    SDL_Texture *texture;
public:
    Image(const char *filename);
    ~Image();
    void Draw(int x,int y);
    int GetWidth();
    int GetHeight();
    SDL_Texture *GetTexture();
};
