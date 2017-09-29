#ifndef LABEL_H
#define LABEL_H

#include "Container.h"
#include <U8glib.h>
    
class Label : public Container {
    private:
        const char* _text;
        const u8g_fntpgm_uint8_t* _font;
    
    public:
        Label(int x, int y, int width, int height, const char* text);
        void drawMe(U8GLIB_SH1106_128X64 *g);
        setText(const char* _text); 
        setFont(const u8g_fntpgm_uint8_t* font);
};

#endif
