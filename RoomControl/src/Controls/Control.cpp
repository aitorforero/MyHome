#include <Arduino.h>
#include <DebugUtils.h>
#include "Control.h"

Control::Control(int x, int y, int width, int height) {

    _x = x;
    _y = y;
    _width = width;
    _height = height;
    setPadding(2);
    parent = 0;
    _Name = nullptr;
    
    _backColor = 0;
    _foreColor = 1;
    layoutChanged = true;
}

void Control::setName(const char * Name)
{
    _Name = Name;
}

const char * Control::getName()
{
    return _Name;
}


void Control::draw(U8GLIB_SH1106_128X64 *g){
	if (layoutChanged) 
	{
        calculateLayout();
        layoutChanged = false; 
    }

    drawMe(g);
}

void Control::drawMe(U8GLIB_SH1106_128X64 *g){
    g->setColorIndex(_backColor); 
    g->drawBox(_x,_y,_width,_height);
}

void Control::setParent(Control* Parent){
    this->parent = Parent;
}

void Control::calculateLayout(){};


                   
void Control::setPosition(int x, int y){
    this->_x = x;
    this->_y = y; 
    this->calculateLayout();
}
                   
void Control::setSize(int width, int height){
    this->_width = width;
    this->_height = height;    
    this->calculateLayout();
}
                   
void Control::setForeColor(int value){
    this->_foreColor = value;
}
                   
void Control::setBackColor(int value){
    this->_backColor = value;
}

void Control::setPadding(int value){
    this->setPadding(value, value, value, value);
}

void Control::setPadding(int leftPadding, int topPadding, int rightPadding, int bottomPadding){
    this->_leftPadding = leftPadding;
    this->_topPadding = topPadding;
    this->_rightPadding = rightPadding;
    this->_bottomPadding = bottomPadding;
    this->calculateLayout();
}

void Control::getDrawingArea(int& x, int& y, int& width, int& height) {
    x = this->_x + this->_leftPadding;
    y = this->_y + this->_topPadding;
    if(this->parent != 0) {
        int yPos;
        int xPos;
        int totWidth;
        int totHeight;
        this->parent->getDrawingArea(xPos, yPos, totWidth, totHeight);

        x += xPos;
        y += yPos;
    }
    width = this->_width -  (this->_leftPadding + this->_rightPadding);
    height = this->_height - (this->_topPadding + this->_bottomPadding);
}

int Control::getWidth(){
    return _width;
};
int Control::getHeight(){
    return _height;
};

int Control::getX(){
    return _x;
};
int Control::getY(){
    return _y;
};