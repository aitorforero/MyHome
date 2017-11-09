#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <List.h>
#include <U8glib.h>
#include "Control.h"
#include "ButtonBar.h"

class IntRange {
    public:
        int min;
        int max;

        IntRange(int newMin, int newMax){
            this->min = newMin;
            this->max = newMax;
        }
};

class TextBox : public Control {
    private:
        List<IntRange*> characterRanges;
        int _maxLength;
        char *_value;
        ButtonBar *_buttonBar;
        const u8g_fntpgm_uint8_t* _font;
        bool _isEditing;
        int _pos;
        void changePos( U8GLIB_SH1106_128X64 *g,int value);
        
        
            
    public:
        TextBox(int x, int y, int width, int height, int MaxLength, ButtonBar *_buttonBar);
        ~TextBox();
    
        void setValue(const char* value);
        void getValue(char* value);
        void addCharacterRange(int min, int max);
        void setFont(const u8g_fntpgm_uint8_t* font);
        void drawMe(U8GLIB_SH1106_128X64 *g);
        
        void doLeft(U8GLIB_SH1106_128X64 *g);
        void doRight(U8GLIB_SH1106_128X64 *g);
        void doSelect(U8GLIB_SH1106_128X64 *g);
};


#endif