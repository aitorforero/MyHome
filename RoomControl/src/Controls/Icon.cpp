#include "Icon.h"


Icon::Icon(int x, int y, int width, int height, const u8g_pgm_uint8_t *bitmap) : Control (x, y, width, height) {
    this->_bitmap = bitmap;
};

void Icon::drawMe( U8GLIB_SH1106_128X64 *g){
    Control::drawMe(g);
    
    g->setColorIndex(_foreColor); 
    g->drawXBMP(_x, _y, _width, _height, _bitmap);
}

void Icon::setBitmap(int width, int height, const u8g_pgm_uint8_t *bitmap){
    this->_bitmap = bitmap;
    this->setSize(width,height);
} 

