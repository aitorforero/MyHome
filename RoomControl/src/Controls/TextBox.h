#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <vector>
#include <U8glib.h>
#include "Control.h"
#include "ButtonBar.h"
#include "Icon.h"


class IntRange {
    public:
        int min;
        int max;

        IntRange(int newMin, int newMax)
		{
            this->min = newMin;
            this->max = newMax;
        }
        
        bool contains(int character)
        {
  	      return !((min > character) || (max < character));
		}
       	
};

class TextBox : public Control {
    private:
        vector<IntRange*> characterRanges;
        int _maxLength;
        ButtonBar *_buttonBar;
        const u8g_fntpgm_uint8_t* _font;
        bool _isEditing;
        bool _isEdited;
        bool _isNewChar;
        int _pos;
        int _currentRange;
        void changeCharacter(int value);
        void changePos(U8GLIB_SH1106_128X64 *g, int value);
        Icon selectIcon;
        Icon editIcon;
        void setEditing(bool value);
        char curr[2] = {0};

        // drawing variables
        int xValue, yValue;
        int xCursor, yCursor, cursorWidth, cursorHeight;
        char *_value = nullptr;
        
        
            
    public:
        TextBox(int x, int y, int width, int height, int MaxLength, ButtonBar *buttonBar);
        ~TextBox();
    
        void setValue(const char* value);
        void getValue(char* value);
        void addCharacterRange(int min, int max);
        void setFont(const u8g_fntpgm_uint8_t* font);
        void drawMe(U8GLIB_SH1106_128X64 *g);
        void calculateLayout( U8GLIB_SH1106_128X64 *g);
        
        void doLeft( U8GLIB_SH1106_128X64 *g);
        void doRight( U8GLIB_SH1106_128X64 *g);
        bool doSelect( U8GLIB_SH1106_128X64 *g);
};


#endif