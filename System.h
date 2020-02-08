#include "SDL2/SDL.h"
#include "stdio.h"
#include "stdlib.h"
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
extern SDL_Renderer *renderer;
extern SDL_Window *window;
extern unsigned int frames;
void Error(const char *message);
