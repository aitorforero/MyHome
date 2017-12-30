#include <ArduinoSTL.h>
#include <DebugUtils.h>
#include <string.h>
#include <IconCreate.h>
#include <IconDone.h>
#include "TextBox.h"

TextBox::TextBox(int x, int y, int width, int height, int maxLength, ButtonBar *buttonBar)
	: Control(x, y, width, height),
	  selectIcon(0,0, icon_done_width, icon_done_height, icon_done_bits),	
	  editIcon(0,0, icon_create_width, icon_create_height, icon_create_bits)
{
	_maxLength = maxLength;
	_value = new char[maxLength+1];
	_pos = 0;
	_currentRange = 0;
	_buttonBar = buttonBar;
	_isNewChar = false;
	setValue("");
	setEditing(false);
	layoutChanged = true;
};

TextBox::~TextBox(){
	if (_value) delete[] _value;
	while(!characterRanges.empty()) {
		IntRange* range = characterRanges.back();
		characterRanges.pop_back();
		delete range;
	}
};

void TextBox::setEditing(bool value)
{
	_isEditing = value;
	if(_isEditing)
	{
	    DEBUG_PRINT("Editing state")
    	_buttonBar->setCenterIcon(&selectIcon);
		_isEdited = true;
	}
	else
	{
	    DEBUG_PRINT("Selecting state")
    	_buttonBar->setCenterIcon(&editIcon);
	}
	layoutChanged = true;
}
		
	

void TextBox::setValue(const char* value){
	strncpy(_value, value, this->_maxLength );
	_pos = 0;
	// changeCharacter(0);
	layoutChanged = true;
};

void TextBox::getValue(char* value){
	strncpy(value, _value, _maxLength );
};

void TextBox::addCharacterRange(int min, int max){
	IntRange* newRange = new IntRange(min,max);
	characterRanges.push_back(newRange);
};

void TextBox::setFont(const u8g_fntpgm_uint8_t* font){
	_font = font;
	layoutChanged = true;
};

void TextBox::calculateLayout( U8GLIB_SH1106_128X64 *g){ 
		DEBUG_PRINT("calculating Layout...")

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
		yPos += (totHeight - h)  / 2 + g->getFontAscent() + 1;

		xValue = xPos;
		yValue = yPos;

		char leftPart[_maxLength] = {0};
		char currentPart[2] = {0};
		
		strncpy(leftPart, _value, _pos);
		currentPart[0] = _value[_pos];
		DEBUG_PRINT("_pos: " << _pos );
		DEBUG_PRINT("_value: " << _value);
		DEBUG_PRINT("leftPart: " << leftPart);
		DEBUG_PRINT("Current: " << currentPart);
		xCursor = xPos - 1 + g->getStrWidth(leftPart);
		yCursor = yPosOrg;
		cursorWidth = g->getStrWidth(currentPart);
		cursorHeight = h;
		DEBUG_PRINT("cursorWidth: " << cursorWidth );
		DEBUG_PRINT("xCursor: " << xCursor);
}


void TextBox::drawMe( U8GLIB_SH1106_128X64 *g){ 
    Control::drawMe(g);

    g->setFont(_font);
    g->setFontRefHeightAll();
    g->setColorIndex(_foreColor); 
    g->drawStr(xValue, yValue, _value);   
    g->drawFrame(xCursor, yCursor,cursorWidth,cursorHeight);
}

void TextBox::changePos( U8GLIB_SH1106_128X64 *g, int value){
    // Controlar valor _pos Negativo !!!
	_pos+=value;
	DEBUG_PRINT("Nuevo valor de _pos = " << _pos)
	if(_pos<0)
	{
		DEBUG_PRINT("Salgo por abajo")
		_pos = 0;
	}
	else if(_pos >=_maxLength)
	{
		DEBUG_PRINT("Salgo por arriba")
		_pos--;
	}
	else
	{
    	int len = strlen(_value);
		if(_pos>len-1) 
        {
			DEBUG_PRINT("Añadir una mas")
		   _isEdited = false;
		   _isNewChar = true;
		   _currentRange = 0;
    	   _value[_pos] = characterRanges.at(_currentRange)->min;
    	   _value[_pos + 1] = 0;
        }
		else if(_pos==len-2 && _isNewChar && !_isEdited) 
        {
			DEBUG_PRINT("Quitar la ultima")
		   _isEdited = false;
		   _isNewChar = false;
    	   _value[_pos + 1] = 0;
        }

	
	} 

	layoutChanged = true;
};

void TextBox::changeCharacter( int value){
	_value[_pos] +=value;
	DEBUG_PRINT("Rango actual: " << _currentRange << " Minimo: " << characterRanges.at(_currentRange)->min << " Actual: " << _value[_pos] << " Maximo: " << characterRanges.at(_currentRange)->max )
	if(characterRanges.at(_currentRange)->max < _value[_pos])
	{
		DEBUG_PRINT("Me paso por arriba")
		if(_currentRange== (characterRanges.size() - 1))
		{
			DEBUG_PRINT("Primer rango")
			_currentRange = 0;
		}
		else
		{
			DEBUG_PRINT("Siguiente rango")
			_currentRange++;
		}
		_value[_pos] = characterRanges.at(_currentRange)->min;
		DEBUG_PRINT("Corregido: " << _currentRange << " Minimo: " << characterRanges.at(_currentRange)->min << " Actual: " << _value[_pos] << " Maximo: " << characterRanges.at(_currentRange)->max )
	}
	else if(characterRanges.at(_currentRange)->min > _value[_pos])
	{
		DEBUG_PRINT("Me paso por abajo")
		if(_currentRange == 0)
		{
			DEBUG_PRINT("Ultimo rango")
			_currentRange = characterRanges.size() - 1;
		}
		else
		{
			DEBUG_PRINT("Anterior rango")
			_currentRange++;
		}
		_value[_pos] = characterRanges.at(_currentRange)->max;
		DEBUG_PRINT("Corregido: " << _currentRange << " Minimo: " << characterRanges.at(_currentRange)->min << " Actual: " << _value[_pos] << " Maximo: " << characterRanges.at(_currentRange)->max )
	}

	layoutChanged = true;
};


    
void TextBox::doLeft( U8GLIB_SH1106_128X64 *g){
	DEBUG_PRINT("doLeft");
	
	if(_isEditing)
	{
	 	changeCharacter(-1);
    }
	else
	{
		changePos(g,-1);
	}
};
void TextBox::doRight( U8GLIB_SH1106_128X64 *g){

    DEBUG_PRINT("doRight");
    
    if(_isEditing)
	{
	    changeCharacter(1);
	}
	else
	{
	    changePos(g, 1);
	}    
};

bool TextBox::doSelect( U8GLIB_SH1106_128X64 *g){
	DEBUG_PRINT("doSelect");
    
    setEditing(!_isEditing);

	return !_isEditing;
};