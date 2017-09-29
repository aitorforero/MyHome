#include "Label.h"

Label::Label(int x, int y, int width, int height, const char* text) : Container (x, y, width, height) {
    this->_text = text;
};

void Label::drawMe(U8GLIB_SH1106_128X64 *g){
    g->setFont(_font);
    g->setFontRefHeightAll();
    int h = g->getFontAscent()-g->getFontDescent();
    int yPos;
    int xPos;
    int totWidth;
    int totHeight;
    getClientBounds(xPos, yPos, totWidth, totHeight);
    yPos += (totHeight - h) / 2 + g->getFontAscent();
    g->setColorIndex(_foreColor); 
    g->drawStr(xPos, yPos, _text);
}
