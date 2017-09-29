#ifndef CONTAINER_H
#define CONTAINER_H

#include "Control.h"
#include "ControlContainer.h"
#include <U8glib.h>
    
class Container : public ControlContainer, public Control {
    public:
        Container(int x, int y, int width, int height):Control(x,y,width,height){};
        void draw(U8GLIB_SH1106_128X64 *g){
            Control::draw(g);
            ControlContainer::drawChildren(g);
        };
};

#endif