#include "Image.h"
#define INDEX_AUTOTILE 16384

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
    void RefreshAutoTile(int i,int j);
public:
    Tiledmap();
    Tiledmap(const char *filename);
    int GetTileId(int i,int j);
    void Draw(double cameraX,double cameraY);
    void AutoTileTest();
    ~Tiledmap();
};
