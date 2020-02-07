#include "Image.h"

class Tiledmap
{
private:
    Image *image;
    unsigned int tilesize;
    unsigned int w,h;
public:
    Tiledmap(const char *filename);
    void Draw(double cameraX,double cameraY);
    ~Tiledmap();
};
