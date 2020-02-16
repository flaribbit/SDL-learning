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
unsigned char ConvertChar(unsigned char* p, wchar_t* ucs2char)
{
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

void Font::CreateCache(const char *string){
    unsigned char *p=(unsigned char *)string;
    SDL_Color color={255,255,255,255};
    wchar_t code[2]={0,0};
    while(*p){
        unsigned char codelen=ConvertChar(p,code);
        auto item=this->Cache.find(*code);
        if(item==this->Cache.end()){
            this->Cache[*code]=new Image(TTF_RenderUNICODE_Blended(this->font,(const uint16_t*)code,color));
        }
        p+=codelen?codelen:1;
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
    wchar_t code[2]={0,0};
    while(*p){
        unsigned char codelen=ConvertChar(p,code);
        Image *t=this->Cache[*code];
        t->Draw(x,y);
        x+=t->GetWidth();
        p+=codelen?codelen:1;
    }
}

void Font::Release(const char *c){
    unsigned char *p=(unsigned char *)c;
    wchar_t code[2]={0,0};
    while(*p){
        unsigned char codelen=ConvertChar(p,code);
        auto item=this->Cache.find(*code);
        if(item!=this->Cache.end()){
            delete item->second;
            this->Cache.erase(item->first);
        }
        p+=codelen?codelen:1;
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
