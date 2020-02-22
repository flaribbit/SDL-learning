#include "Control.h"

Control controller;

Control::Control()
{
    for(int i=0;i<8;i++){
        this->key[i]=false;
        this->okey[i]=true;
    }
}

Control::~Control()
{
}

void Control::Update(){
    SDL_Event event;
    for(int i=0;i<10;i++){
        this->okey[i]=this->key[i];
    }
    while(SDL_PollEvent(&event)){
        switch(event.type){
        case SDL_QUIT:
            frames=-1;
            break;
        case SDL_KEYDOWN:
            switch(event.key.keysym.sym){
                case SDLK_w:this->key[KeyUp]=true;break;
                case SDLK_s:this->key[KeyDown]=true;break;
                case SDLK_a:this->key[KeyLeft]=true;break;
                case SDLK_d:this->key[KeyRight]=true;break;
                case SDLK_j:this->key[KeyA]=true;break;
                case SDLK_k:this->key[KeyB]=true;break;
                case SDLK_u:this->key[KeyX]=true;break;
                case SDLK_i:this->key[KeyY]=true;break;
            }
            break;
        case SDL_KEYUP:
            switch(event.key.keysym.sym){
                case SDLK_w:this->key[KeyUp]=false;break;
                case SDLK_s:this->key[KeyDown]=false;break;
                case SDLK_a:this->key[KeyLeft]=false;break;
                case SDLK_d:this->key[KeyRight]=false;break;
                case SDLK_j:this->key[KeyA]=false;break;
                case SDLK_k:this->key[KeyB]=false;break;
                case SDLK_u:this->key[KeyX]=false;break;
                case SDLK_i:this->key[KeyY]=false;break;
            }
            break;
        case SDL_MOUSEMOTION:
            mouseX=event.motion.x;
            mouseY=event.motion.y;
            break;
        case SDL_MOUSEBUTTONDOWN:
            switch(event.button.button){
                case SDL_BUTTON_LEFT:this->key[KeyMouseL]=true;break;
                case SDL_BUTTON_RIGHT:this->key[KeyMouseR]=true;break;
            }
            break;
        case SDL_MOUSEBUTTONUP:
            switch(event.button.button){
                case SDL_BUTTON_LEFT:this->key[KeyMouseL]=false;break;
                case SDL_BUTTON_RIGHT:this->key[KeyMouseR]=false;break;
            }
            break;
        }
    }
}

bool Control::IsPress(Key key){
    return this->key[key] && !this->okey[key];
}

bool Control::IsDown(Key key){
    return this->key[key];
}
