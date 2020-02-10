#include "Font.h"

Font::Font()
{
}

Font::~Font()
{
    TTF_CloseFont(this->font);
    ReleaseAll();
}

void Font::CreateCache(const char *string){
    unsigned char *p=(unsigned char *)string;
    SDL_Color color={255,255,255,255};
    while(*p){
        uint32_t code;
        char c[5]={0};
        if(*p>=240){
            code=*(uint32_t*)p;
            for(int i=0;i<4;i++){
                c[i]=p[i];
            }
            c[4]=0;
            p+=4;
        }else if(*p>=224){
            code=p[2]<<16|p[1]<<8|*p;
            for(int i=0;i<3;i++){
                c[i]=p[i];
            }
            c[3]=0;
            p+=3;
        }else if(*p>=192){
            code=*(uint16_t*)p;
            c[0]=p[0];
            c[1]=p[1];
            c[2]=0;
            p+=2;
        }else{
            code=*p;
            c[0]=p[0];
            c[1]=0;
            p+=1;
        }
        auto item=this->Cache.find(code);
        if(item==this->Cache.end()){
            this->Cache[code]=new Image(TTF_RenderUTF8_Blended(this->font,c,color));
        }
    }
}

void Font::Init(){

}

void Font::NewFont(const char *ttf_file,int size){
    this->font=TTF_OpenFont(ttf_file,size);
}

void Font::Print(const char *string,int x,int y){
    CreateCache(string);
    unsigned char *p=(unsigned char *)string;
    while(*p){
        uint32_t code;
        if(*p>=240){
            code=*(uint32_t*)p;
            p+=4;
        }else if(*p>=224){
            code=p[2]<<16|p[1]<<8|*p;
            p+=3;
        }else if(*p>=192){
            code=*(uint16_t*)p;
            p+=2;
        }else{
            code=*p;
            p+=1;
        }
        Image *t=this->Cache[code];
        t->Draw(x,y);
        x+=t->GetWidth();
    }
}

void Font::Release(const char *c){
    unsigned char *p=(unsigned char *)c;
    while(*p){
        uint32_t code;
        if(*p>=240){
            code=*(uint32_t*)p;
            p+=4;
        }else if(*p>=224){
            code=p[2]<<16|p[1]<<8|*p;
            p+=3;
        }else if(*p>=192){
            code=*(uint16_t*)p;
            p+=2;
        }else{
            code=*p;
            p+=1;
        }
    }
}

void Font::ReleaseAll(){
    for(auto item:this->Cache){
        delete item.second;
    }
    this->Cache.clear();
}

int Font::GetCacheLength(){
    return this->Cache.size();
}
