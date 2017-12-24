#ifndef CONTROL_H
#define CONTROL_H

#include <U8glib.h>

    
class Control {
   
    public:
        Control(int x, int y, int width, int height);
        void draw(U8GLIB_SH1106_128X64 *g);
        void setPosition(int x, int y);
        void setSize(int width, int height);
        void setForeColor(int value);
        void setBackColor(int value);   
        void setPadding(int value);   
        void setParent(Control* parent);
        void setPadding(int leftPadding, int topPadding, int rightPadding, int bottomPadding);  
        int getWidth();
        int getHeight();
        int getX();
        int getY();
        void setName(const char * Name);
        const char * getName();
    
    protected:
        int _x;
        int _y;
        int _width;
        int _height;
        int _foreColor;
        int _backColor;
        int _leftPadding;
        int _rightPadding;
        int _topPadding;
        int _bottomPadding;
        bool layoutChanged;
        void getDrawingArea(int& x, int& y, int& width, int& height);
        const char * _Name;
       
        Control* parent;
    
        virtual void drawMe(U8GLIB_SH1106_128X64 *g);
        virtual void calculateLayout();
        
};

#endif