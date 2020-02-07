#include "System.h"
SDL_Renderer *renderer;
SDL_Window *window;
unsigned int frames;

void Error(char *message){
    puts(message);
    getchar();
}
