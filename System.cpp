#include "System.h"
SDL_Renderer *renderer;
SDL_Window *window;
int frames;

void Error(const char *message){
    puts(message);
    getchar();
}
