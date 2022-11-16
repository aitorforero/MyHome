#include "Container.h"
#include "ButtonBar.h"


ButtonBar::ButtonBar(int x, int y, int width, int height) : Container (x, y, width, height) {
    _leftIcon = 0;
    _centerIcon = 0;
    _rigthIcon = 0;
};



void ButtonBar::setLeftIcon(Icon *icon) {
    if (this->_leftIcon != 0) {
        removeChild(this->_leftIcon);
    }
    this->_leftIcon = icon;
    if (this->_leftIcon != 0) {
        addChild(this->_leftIcon);
    }
} 

void ButtonBar::setCenterIcon(Icon *icon) {
    if (this->_centerIcon != 0) {
        removeChild(this->_centerIcon);
    }
    this->_centerIcon = icon;
    if (this->_centerIcon != 0) {
        addChild(this->_centerIcon);
    }
} 

void ButtonBar::setRightIcon(Icon *icon) {
    if (this->_rigthIcon != 0) {
        removeChild(this->_rigthIcon);
    }
    this->_rigthIcon = icon;
    if (this->_rigthIcon != 0) {
        addChild(this->_rigthIcon);
    }
} 

void ButtonBar::calculateLayout(U8GLIB_SH1106_128X64 *g){
    int yPos;
    int xPos;
    int totWidth;
    int totHeight;
    getDrawingArea(xPos, yPos, totWidth, totHeight);

    
    if (this->_leftIcon != 0) {
        this->_leftIcon->setPosition(xPos, yPos);
    }
    
    if (this->_centerIcon != 0) {
        this->_centerIcon->setPosition(xPos + (totWidth - this->_centerIcon->getWidth()) / 2, yPos);
    }
    
    if (this->_rigthIcon != 0) {
        this->_rigthIcon->setPosition(xPos + (totWidth - this->_rigthIcon->getWidth()), yPos);
    }
}

