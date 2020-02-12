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
bool utf8CharToUcs2Char(const char* utf8Tok, wchar_t* ucs2Char, uint32_t* utf8TokLen)
{
    //We do math, that relies on unsigned data types
    const unsigned char* utf8TokUs = reinterpret_cast<const unsigned char*>(utf8Tok);

    //Initialize return values for 'return false' cases.
    *ucs2Char = L'?';
    *utf8TokLen = 1;

    //Decode
    if (0x80 > utf8TokUs[0])
    {
        //Tokensize: 1 byte
        *ucs2Char = static_cast<const wchar_t>(utf8TokUs[0]);
    }
    else if (0xC0 == (utf8TokUs[0] & 0xE0))
    {
        //Tokensize: 2 bytes
        if ( 0x80 != (utf8TokUs[1] & 0xC0) )
        {
            return false;
        }
        *utf8TokLen = 2;
        *ucs2Char = static_cast<const wchar_t>(
                  (utf8TokUs[0] & 0x1F) << 6
                | (utf8TokUs[1] & 0x3F)
            );
    }
    else if (0xE0 == (utf8TokUs[0] & 0xF0))
    {
        //Tokensize: 3 bytes
        if (   ( 0x80 != (utf8TokUs[1] & 0xC0) )
		    || ( 0x80 != (utf8TokUs[2] & 0xC0) )
		   )
        {
            return false;
        }
        *utf8TokLen = 3;
        *ucs2Char = static_cast<const wchar_t>(
                  (utf8TokUs[0] & 0x0F) << 12
                | (utf8TokUs[1] & 0x3F) << 6
                | (utf8TokUs[2] & 0x3F)
            );
    }
    else if (0xF0 == (utf8TokUs[0] & 0xF8))
    {
        //Tokensize: 4 bytes
        *utf8TokLen = 4;
        return false;                        //Character exceeds the UCS-2 range (UCS-4 would be necessary)
    }
    else if ((0xF8 == utf8TokUs[0] & 0xFC))
    {
        //Tokensize: 5 bytes
        *utf8TokLen = 5;
        return false;                        //Character exceeds the UCS-2 range (UCS-4 would be necessary)
    }
    else if (0xFC == (utf8TokUs[0] & 0xFE))
    {
        //Tokensize: 6 bytes
        *utf8TokLen = 6;
        return false;                        //Character exceeds the UCS-2 range (UCS-4 would be necessary)
    }
    else
    {
        return false;
    }
    return true;
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
