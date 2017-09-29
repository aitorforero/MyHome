#include "Control.h"

Control::Control(int x, int y, int width, int height) {
    this->_x = x;
    this->_y = y;
    this->_width = width;
    this->_height = height;
    this->setPadding(2);
}

void Control::draw(U8GLIB_SH1106_128X64 *g){
      	drawMe(g); 
}

void Control::drawMe(U8GLIB_SH1106_128X64 *g){
      	g->setColorIndex(_backColor); 
        g->drawBox(_x,_y,_width,_height);
}




                   
void Control::setPosition(int x, int y){
    this->_x = x;
    this->_y = y;        
}
                   
void Control::setSize(int width, int height){
    this->_width = width;
    this->_height = height;    
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
}

void Control::getClientBounds(int& x, int& y, int& width, int& height) {
    x = this->_x + this->_leftPadding;
    y = this->_y + this->_topPadding;
    width = this->_width - x;
    height = this->_height - y;
}
         
             
                   
                  
                  
