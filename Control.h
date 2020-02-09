#include "SDL2/SDL.h"
#include "System.h"

class Control
{
private:
    bool key[8];
    bool okey[8];
public:
    typedef enum{
        KeyUp,
        KeyDown,
        KeyLeft,
        KeyRight,
        KeyA,
        KeyB,
        KeyX,
        KeyY,
    }Key;
    Control();
    ~Control();
    void Update();
    bool IsPress(Key key);
    bool IsDown(Key key);
};

extern Control controller;
