#include "Image.h"

class Sprite
{
private:
    Image *image;
    SDL_Rect *frame;
    int frames;
    double x,y;
    double ox,oy;
public:
    Sprite();
    ~Sprite();
};
