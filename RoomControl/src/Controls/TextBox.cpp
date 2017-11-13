#include <string.h>
#include <IconCreate.h>
#include <IconDone.h>
#include "TextBox.h"

TextBox::TextBox(int x, int y, int width, int height, int maxLength, ButtonBar *buttonBar)
	: Control(x, y, width, height),
	  selectIcon(0,0, icon_done_width, icon_done_height, icon_done_bits),	
	  editIcon(0,0, icon_create_width, icon_create_height, icon_create_bits)
{
	this->_maxLength = maxLength;
	this->_value = new char[maxLength+1];
	this->_pos = 0;
	this->setValue("");
	this->_buttonBar = buttonBar;
	setEditing(false);
};

TextBox::~TextBox(){
	delete[] this->_value;
	while(characterRanges.count()>0) {
		IntRange* range = characterRanges.item(0);
		characterRanges.remove(range);
		delete range;
	}
};

void TextBox::setEditing(bool value)
{
	_isEditing = value;
	if(_isEditing)
	{
		_buttonBar->setCenterIcon(&selectIcon);
	}
	else
	{
		_buttonBar->setCenterIcon(&editIcon);
	}
}
		
	

void TextBox::setValue(const char* value){
	strncpy(this->_value, value, this->_maxLength );
	_pos = 0;
	curr[0] = value[0];
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



void TextBox::doLeft(U8GLIB_SH1106_128X64 *g){
	if(_isEditing)
	{
		// change letter
	}
	else
	{
		changePos(g, -1);
	}
};
void TextBox::doRight(U8GLIB_SH1106_128X64 *g){
	if(_isEditing)
	{
		// change letter
	}
	else
	{
		changePos(g, 1);
	}    
};

bool TextBox::doSelect(U8GLIB_SH1106_128X64 *g){
	setEditing(!_isEditing);
};