#ifndef ICON_H
#define ICO_H

#include "Control.h"
#include <U8glib.h>
    
class Icon : public Control {
    private:
        const u8g_pgm_uint8_t* _bitmap;
    
    public:
        Icon(int x, int y, int width, int height, const u8g_pgm_uint8_t *bitmap);
        void drawMe(U8GLIB_SH1106_128X64 *g);
};

#endif
