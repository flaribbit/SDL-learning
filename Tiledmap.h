#include "Image.h"

class Tiledmap
{
private:
    Image *image;
    int tilesize;
    int w,h;
    int size;
    int *layer;
public:
    Tiledmap();
    Tiledmap(const char *filename);
    void Draw(double cameraX,double cameraY);
    ~Tiledmap();
};
