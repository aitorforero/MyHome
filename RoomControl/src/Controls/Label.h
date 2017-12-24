#ifndef LABEL_H
#define LABEL_H

#include "Container.h"
#include "HorizontalAlign.h"
#include <U8glib.h>
    
class Label : public Container {
    private:
        const char* _text;
        const u8g_fntpgm_uint8_t* _font;
        HorizontalAlign _horizontalAlign;
        void calculateLayout(U8GLIB_SH1106_128X64 *g);
        int yPos;
        int xPos;

    public:
        Label(int x, int y, int width, int height, const char* text);
        void drawMe( U8GLIB_SH1106_128X64 *g);
        void setText(const char* text); 
        void setFont(const u8g_fntpgm_uint8_t* font);
        void setHorizontalAlign(HorizontalAlign horizontalAlign);
};

#endif
