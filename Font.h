#include "SDL2/SDL.h"
#include "SDL2/SDL_ttf.h"
#include "Image.h"
#include <map>

class Font
{
private:
    std::map<uint32_t,Image*>Cache;
    TTF_Font *font;
    void CreateCache(const char *string);
public:
    Font();
    ~Font();
    void Init();
    void NewFont(const char *ttf_file,int size);
    void Print(const char *string,int x,int y);
    void Release(const char *c);
    void ReleaseAll();
    int GetCacheLength();
};
