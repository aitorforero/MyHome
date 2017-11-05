#include "Label.h"
#include "HorizontalAlign.h"


Label::Label(int x, int y, int width, int height, const char* text)
    : Container (x, y, width, height)
{
    this->_text = text;
};

void Label::drawMe( U8GLIB_SH1106_128X64 *g){ 
    Control::drawMe(g);

    int yPos;
    int xPos;
    int totWidth;
    int totHeight;
    getDrawingArea(xPos, yPos, totWidth, totHeight);

    int xPosOrg = xPos;
    int yPosOrg = yPos;
    
    g->setFont(_font);
    g->setFontRefHeightAll();

    
    int h = g->getFontAscent() - g->getFontDescent();
    
    yPos += (totHeight - h)  / 2 + g->getFontAscent();

    int textWidth = g->getStrWidth(_text);
    switch(_horizontalAlign) {
        case center:
            xPos = xPos + ((totWidth-textWidth) / 2);
            break;
        case right:
            xPos = xPos + totWidth - textWidth;
            break;
        case left:
            // Do nothing
            break;
    }

    
    g->setColorIndex(_foreColor); 
    g->drawStr(xPos, yPos, _text);
    
}

void Label::setText(const char* text){
    this->_text = text;
}
void Label::setFont(const u8g_fntpgm_uint8_t* font){
    this->_font = font;
}

void Label::setHorizontalAlign(HorizontalAlign horizontalAlign){
    this->_horizontalAlign = horizontalAlign;           
}