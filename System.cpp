#include "System.h"
SDL_Renderer *renderer;
SDL_Window *window;
unsigned int frames;

void Error(const char *message){
    puts(message);
    getchar();
}
