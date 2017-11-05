#ifndef CONTAINER_H
#define CONTAINER_H

#include "Control.h"
#include "ControlContainer.h"
#include <U8glib.h>
    
class Container : public ControlContainer, public Control {
    public:
        void addChild(Control* item) {
            item->setParent(this);
            ControlContainer::addChild(item);
            calculateLayout();
        };
    
        void removeChild(Control* item) {
            ControlContainer::removeChild(item);
            item->setParent(0);
            calculateLayout();
        };
    
        Container(int x, int y, int width, int height):Control(x,y,width,height){};
    
        void drawMe(U8GLIB_SH1106_128X64 *g){
           Control::drawMe(g);
           ControlContainer::drawChildren(g);
        };
};

#endif