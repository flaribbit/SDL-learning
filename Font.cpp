#include "Font.h"

Font::Font()
{
}

Font::~Font()
{
    TTF_CloseFont(this->font);
    ReleaseAll();
}

//Converter from: https://github.com/RoelofBerg/Utf8Ucs2Converter/blob/master/Utf8Ucs2Converter.cpp
unsigned char ConvertChar(const char* utf8char, wchar_t* ucs2char)
{
    const unsigned char *p=(const unsigned char*)utf8char;
    *ucs2char = L'?';
    if(0x80>p[0]){
        *ucs2char=(wchar_t)p[0];//1字节字符
        return 1;
    }else if(0xC0==(p[0]&0xE0)){
        if(0x80!=(p[1]&0xC0))
        {
            return 0;
        }
        *ucs2char=(wchar_t)((p[0]&0x1F)<<6 | (p[1]&0x3F));//2字节字符
        return 2;
    }else if(0xE0==(p[0]&0xF0)){
        if((0x80!=(p[1]&0xC0))|| (0x80!=(p[2]&0xC0)))
        {
            return 0;
        }
        *ucs2char=(wchar_t)((p[0]&0x0F)<<12 | (p[1]&0x3F)<<6 | (p[2]&0x3F));//3字节字符
        return 3;
    }else if(0xF0==(p[0]&0xF8)){
        return 0;//4字节容量不够
    }else{
        return 0;//错误字符
    }
}

uint32_t GetUTF8Char(unsigned char *&p,char *c){
    uint32_t code;
    while(*p>=128&&*p<192){
        p++;
    }
    if(*p>=240){
        code=*(uint32_t*)p;
        if(c){
            c[0]=p[0];
            c[1]=p[1];
            c[2]=p[2];
            c[2]=p[3];
            c[4]=0;
        }
        p+=4;
    }else if(*p>=224){
        code=p[2]<<16|p[1]<<8|*p;
        if(c){
            c[0]=p[0];
            c[1]=p[1];
            c[2]=p[2];
            c[3]=0;
        }
        p+=3;
    }else if(*p>=192){
        code=*(uint16_t*)p;
        if(c){
            c[0]=p[0];
            c[1]=p[1];
            c[2]=0;
        }
        p+=2;
    }else{
        code=*p;
        if(c){
            c[0]=p[0];
            c[1]=0;
        }
        p+=1;
    }
    return code;
}

void Font::CreateCache(const char *string){
    unsigned char *p=(unsigned char *)string;
    SDL_Color color={255,255,255,255};
    while(*p){
        char c[5]={0};
        uint32_t code=GetUTF8Char(p,c);
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
        uint32_t code=GetUTF8Char(p,0);
        Image *t=this->Cache[code];
        t->Draw(x,y);
        x+=t->GetWidth();
    }
}

void Font::Release(const char *c){
    unsigned char *p=(unsigned char *)c;
    while(*p){
        uint32_t code=GetUTF8Char(p,0);
        auto item=this->Cache.find(code);
        if(item!=this->Cache.end()){
            delete item->second;
            this->Cache.erase(item->first);
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
