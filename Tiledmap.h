#include "Image.h"

class Tiledmap
{
private:
    Image *image;
    Image *animatetile;
    Image *autotile;
    int tilesize;
    int w,h;
    int size;
    int *layer;
    SDL_Rect *GetSmallTileRect(int index);
    SDL_Rect *GetSmallTileRect(int index, int frame);
public:
    Tiledmap();
    Tiledmap(const char *filename);
    void Draw(double cameraX,double cameraY);
    void AutoTileTest();
    ~Tiledmap();
};
