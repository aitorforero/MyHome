#include "Label.h"
#include "HorizontalAlign.h"


Label::Label(int x, int y, int width, int height, const char* text)
    : Container (x, y, width, height)
{
    this->setText(text);
};

void Label::calculateLayout(U8GLIB_SH1106_128X64 *g)
{
    DEBUG_PRINT("calculateLayout Text: " << _text )
	int totWidth;
    int totHeight;
    getDrawingArea(xPos, yPos, totWidth, totHeight);

   
    g->setFont(_font);
    g->setFontRefHeightAll();

    
    int h = g->getFontAscent() - g->getFontDescent();
    
    yPos += (totHeight - h)  / 2 + g->getFontAscent();

    int textWidth = g->getStrWidth(_text);
    switch(_horizontalAlign) {
        case HorizontalAlign::center:
            DEBUG_PRINT("center align")
            xPos += ((totWidth-textWidth) / 2);
            break;
        case HorizontalAlign::right:
            DEBUG_PRINT("right align")
            xPos += totWidth - textWidth;
            break;
        case HorizontalAlign::left:
            DEBUG_PRINT("left align")
            // Do nothing
            break;
    }

    DEBUG_PRINT("xPos" << xPos << " yPos " << yPos )
} 

void Label::drawMe( U8GLIB_SH1106_128X64 *g){ 
    Control::drawMe(g);
    
    g->setFont(_font);
    g->setFontRefHeightAll();
    g->setColorIndex(_foreColor); 
    g->drawStr(xPos, yPos, _text);
}

void Label::setText(const char* text){
    this->_text = text;
    layoutChanged = true;
}
void Label::setFont(const u8g_fntpgm_uint8_t* font){
    this->_font = font;
    layoutChanged = true;
}

void Label::setHorizontalAlign(HorizontalAlign horizontalAlign){
    this->_horizontalAlign = horizontalAlign;           
    layoutChanged = true;
}