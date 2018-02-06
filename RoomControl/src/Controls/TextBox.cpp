#include <ArduinoSTL.h>
#include <DebugUtils.h>
#include <string.h>
#include <IconCreate.h>
#include <IconDone.h>
#include <IconBackSpace.h>
#include <IconDel.h>
#include <IconInsert.h>
#include <IconCancel.h>
#include <IconSave.h>
#include <IconSelect.h>
#include "TextBox.h"

TextBox::TextBox(int x, int y, int width, int height, int maxLength, ButtonBar *buttonBar)
	: Control(x, y, width, height),
	  okIcon(0,0, icon_done_width, icon_done_height, icon_done_bits),	
	  selectIcon(0,0, icon_select_width, icon_select_height, icon_select_bits),	
	  editIcon(0,0, icon_create_width, icon_create_height, icon_create_bits),
	  backSpaceIcon(0,0, icon_backspace_width, icon_backspace_height, icon_backspace_bits),
      delIcon(0,0, icon_del_width, icon_del_height, icon_del_bits),
      insertIcon(0,0, icon_insert_width, icon_insert_height, icon_insert_bits),
      cancelIcon(0,0, icon_cancel_width, icon_cancel_height, icon_cancel_bits),
      saveIcon(0,0, icon_save_width, icon_save_height, icon_save_bits)
{
	_maxLength = maxLength;
	_value = new char[maxLength+1];
	_pos = 0;
	_currentRange = 0;
	_buttonBar = buttonBar;
	_isNewChar = false;
	setValue("");
	setState(Selecting);
	layoutChanged = true;
	DEBUG_PRINT("Build")
};

TextBox::~TextBox(){
	if (_value) delete[] _value;
	while(!characterRanges.empty()) {
		IntRange* range = characterRanges.back();
		characterRanges.pop_back();
		delete range;
	}
};

void TextBox::setState(TextBoxState state)
{
	_state = state;
	switch(_state)
	{
		case Editing:
			DEBUG_PRINT("Editing state")
    		_buttonBar->setCenterIcon(&okIcon);
			_isEdited = true;
			break;
		case Selecting:
			DEBUG_PRINT("Selecting state")
			_buttonBar->setCenterIcon(&selectIcon);
			break;
		case BackSpacing:
			DEBUG_PRINT("BackSpacing state")
			_buttonBar->setCenterIcon(&backSpaceIcon);
			break;
		case Deleting:
			DEBUG_PRINT("Deleting state")
			_buttonBar->setCenterIcon(&delIcon);
			break;
		case Inserting:
			DEBUG_PRINT("Inserting state")
			_buttonBar->setCenterIcon(&insertIcon);
			break;
		case Canceling:
			DEBUG_PRINT("Canceling state")
			_buttonBar->setCenterIcon(&cancelIcon);
			break;
		case Edit:
			DEBUG_PRINT("Edit state")
			_buttonBar->setCenterIcon(&editIcon);
			break;
		case Select:
			DEBUG_PRINT("Select state")
			_buttonBar->setCenterIcon(&okIcon);
			break;
		default:
			DEBUG_PRINT("Saving state")
			_buttonBar->setCenterIcon(&saveIcon);
			break;
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

void TextBox::changePos(int value){
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

	char nextValue = _value[_pos];
	int nextRange = _currentRange;
	

	DEBUG_PRINT("Rango actual: " << _currentRange << " Minimo: " << characterRanges.at(_currentRange)->min << " Actual: " << nextValue<< " Maximo: " << characterRanges.at(_currentRange)->max )

	switch(_state)
	{
		case BackSpacing:
			DEBUG_PRINT("BackSpacing")
			if(value<0)
			{
				setState(Editing);
				DEBUG_PRINT("Ultimo rango")
				nextRange = characterRanges.size() - 1;
				nextValue = characterRanges.at(nextRange)->max;
			}
			else if(value>0)
			{
				setState(Deleting);
			}
			break;
		case Deleting:
			DEBUG_PRINT("Deleting")
			if(value<0)
			{
				setState(BackSpacing);
			}
			else if(value>0)
			{
				setState(Inserting);
			}
			break;
		case Inserting:
			DEBUG_PRINT("Inserting")
			if(value<0)
			{
				setState(Deleting);
			}
			else if(value>0)
			{
				setState(Canceling);
			}
			break;
		case Canceling:
			DEBUG_PRINT("Canceling")
			if(value<0)
			{
				setState(Inserting);
			}
			else if(value>0)
			{
				setState(Saving);
			}
			break;
		case Saving:
			DEBUG_PRINT("Saving")
			if(value<0)
			{
				setState(Canceling);
			}
			else if(value>0)
			{
				setState(Editing);
				DEBUG_PRINT("Primer rango")
				nextRange = 0;
				nextValue = characterRanges.at(nextRange)->min;
			}
			break;
		default:
			DEBUG_PRINT("default")
			nextValue = _value[_pos] < 255 ? _value[_pos] + value : 0;
			if(characterRanges.at(nextRange)->max < nextValue)
			{
				DEBUG_PRINT("Me paso por arriba")
				if(nextRange == (characterRanges.size() - 1))
				{
					nextValue = _value[_pos]; // set to the previous value
					setState(BackSpacing);
				}
				else
				{
					DEBUG_PRINT("Siguiente rango")
					nextRange++;
					nextValue = characterRanges.at(nextRange)->min;
				}
				
			}
			else if(characterRanges.at(nextRange)->min > nextValue)
			{
				DEBUG_PRINT("Me paso por abajo")
				if(nextRange == 0)
				{
					nextValue = _value[_pos]; // set to the previous value
					setState(Saving);
				}
				else
				{
					DEBUG_PRINT("Anterior rango")
					nextRange--;
					nextValue = characterRanges.at(nextRange)->max;
				}
			}
			
			break;
	}
	
	DEBUG_PRINT("Corregido: " << nextRange << " Minimo: " << characterRanges.at(nextRange)->min << " Actual: " << nextValue << " Maximo: " << characterRanges.at(nextRange)->max );
	
	_value[_pos] = nextValue;
			

	layoutChanged = true;
};

void TextBox::deletePos(int pos)
{
	int valueLength = strlen(_value);
	if ((pos >= 0) && (pos < valueLength))
	{
		for(int i = pos; i < (valueLength - 1); i++)
		{
			_value[i] = _value[i+1];	
		}

		_value[valueLength - 1] = 0;
	}

	changePos(pos - _pos);
}

void TextBox::insertAt(int pos)
{
	int valueLength = strlen(_value);
	if ((pos >= 0) && (pos < valueLength) && (valueLength < _maxLength))
	{
		for(int i = valueLength - 1; i > pos; i--)
		{
			_value[i-1] = _value[i];	
		}
        
        currentRange = 0;
		_value[valueLength - 1] = characterRanges.at(currentRange)->min;
	}

	changePos(pos - _pos);
};

void TextBox::save()
{
	_saved = true;
};
void TextBox::cancel()
{
	_saved = false;
};

    
void TextBox::doLeft( U8GLIB_SH1106_128X64 *g){
	DEBUG_PRINT("doLeft");
	
	switch(_state)
	{ 
		case Canceling:
			setState(Inserting);
			break;
		case Inserting:
			setState(BackSpacing);
			break;
		case BackSpacing:
			setState(Deleting);
			break;
		case Deleting:
			setState(Edit);
			break;
		case Edit:
			setState(Select);
			break;
		case Select:
			setState(Saving);
			break;
		case Saving:
			setState(Canceling);
			break;
		case Selecting:
			changePos(-1);
			break;
		default:
		    changeCharacter(-1);
			break;
	}
};

void TextBox::doRight( U8GLIB_SH1106_128X64 *g){

    DEBUG_PRINT("doRight");
    switch(_state)
	{
		case Canceling:
			setState(Saving);
			break;
		case Inserting:
			setState(Canceling);
			break;
		case BackSpacing:
			setState(Inserting);
			break;
		case Deleting:
			setState(BackSpacing);
			break;
		case Edit:
			setState(Deleting);
			break;
		case Select:
			setState(Edit);
			break;
		case Saving:
			setState(Select);
			break;
		case Selecting:
			changePos(1);
			break;
		default:
		    changeCharacter(1);
			break;
	};
};

bool TextBox::doSelect( U8GLIB_SH1106_128X64 *g){
	DEBUG_PRINT("doSelect");
    
    bool res = false;
    
    switch(_state)
	{
		case Canceling:
		    cancel();
		    res = true;
			break;
		case Inserting:
			insertAt(_pos);
			break;
		case BackSpacing:
		    deletePos(_pos - 1);
			break;
		case Deleting:
			deletePos(_pos);
			break;		
		case Edit:
			setState(Editing);
			break;
		case Select:
			setState(Selecting);
			break;
		case Saving:
			save();
			res = true;
			break;
	   case Selecting:
			setState(Edit);
			break;
		default:
			setState(Select);
			break;
    };
    
	return res;
};