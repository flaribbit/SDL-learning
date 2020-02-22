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
    void DrawAutoTile(int x,int y,int index);
public:
    void RefreshAutoTile(int i,int j);
    Tiledmap();
    Tiledmap(const char *filename);
    int GetTileId(int i,int j);
    void SetTileId(int i,int j,int id);
    void Draw(double cameraX,double cameraY);
    void AutoTileTest();
    ~Tiledmap();
};
