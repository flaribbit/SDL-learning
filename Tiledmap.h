#include "Image.h"

class Tiledmap
{
private:
    Image *image;
    unsigned int tilesize;
    unsigned int w,h;
    unsigned int *layer;
public:
    Tiledmap();
    Tiledmap(const char *filename);
    void Draw(double cameraX,double cameraY);
    ~Tiledmap();
};
