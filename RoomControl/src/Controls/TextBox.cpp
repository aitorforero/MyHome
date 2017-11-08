#include <string.h>
#include "TextBox.h"

TextBox::TextBox(int x, int y, int width, int height, int maxLength, ButtonBar *_buttonBar)
    : Control(x, y, width, height)
{
    this->_maxLength = maxLength;
    this->_value = new char[maxLength+1];
    this->_isEditing = false;
    this->_pos = 0;
    this->setValue("");
        
};

TextBox::~TextBox(){
    delete[] this->_value;
    while(characterRanges.count()>0) {
        IntRange* range = characterRanges.item(0);
        characterRanges.remove(range);
        delete range;
    }
};

void TextBox::setValue(const char* value){
    strncpy(this->_value, value, this->_maxLength );
};

void TextBox::getValue(char* value){
    strncpy(value, this->_value, this->_maxLength );
};

void TextBox::addCharacterRange(int min, int max){
    IntRange* newRange = new IntRange(min,max);
    characterRanges.add(newRange);
};

void TextBox::setFont(const u8g_fntpgm_uint8_t* font){
    this->_font = font;
};

void TextBox::drawMe( U8GLIB_SH1106_128X64 *g){ 
    Control::drawMe(g);
    
    int h = g->getFontAscent() - g->getFontDescent();
    int yPos;
    int xPos;
    int totWidth;
    int totHeight;
    getDrawingArea(xPos, yPos, totWidth, totHeight);

    char prev[this->_pos+1] = {0};
    char curr[2] = {0};
    char next[strlen(this->_value)-this->_pos] = {0};
    
    if(_pos>0){
        strncpy(prev, this->_value, _pos-1);
    }
    strncpy(curr, this->_value + _pos + 1 , 1);
    if(_pos <= this->_maxLength){
        strncpy(next, this->_value + _pos + 1, strlen(this->_value) - this->_pos - 1);
    }

    
    
    g->setFont(this->_font);
    g->setFontRefHeightAll();
    yPos += (totHeight - h) / 2 + g->getFontAscent();
    
    
    
    int prevWidth = g->getStrWidth(prev);
    int currWidth = g->getStrWidth(curr);
    int nextWidth = g->getStrWidth(next);

    
    g->setColorIndex(_foreColor); 
    g->drawStr(xPos, yPos, prev);
    //g->drawStr(xPos + prevWidth, yPos, curr);
    //g->drawStr(xPos + currWidth, yPos, next);
    
}

void TextBox::changePos( U8GLIB_SH1106_128X64 *g, int value){
    _pos +=value;
    this->draw(g);
};



void TextBox::doLeft(){
    this->changePos(-1);
};
void TextBox::doRight(){
    this->changePos(1);    
};

void TextBox::doSelect(){
    
};