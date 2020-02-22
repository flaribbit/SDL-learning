#include "SDL2/SDL.h"
#include "System.h"

class Control
{
private:
    bool key[10];
    bool okey[10];
public:
    int mouseX;
    int mouseY;
    typedef enum{
        KeyUp,
        KeyDown,
        KeyLeft,
        KeyRight,
        KeyA,
        KeyB,
        KeyX,
        KeyY,
        KeyMouseL,
        KeyMouseR,
    }Key;
    Control();
    ~Control();
    void Update();
    bool IsPress(Key key);
    bool IsDown(Key key);
};

extern Control controller;
