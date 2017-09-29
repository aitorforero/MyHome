#ifndef CONTROL_CONTAINER_H
#define CONTROL_CONTAINER_H

#include <List.h>
#include <U8glib.h>
#include "Control.h"

class ControlContainer {
    private:
        List<Control> _childControls;

    public:
       ControlContainer(){
       };
    
        List<Control>* getChildControls() {
            return &_childControls;
        };

        void drawChildren(U8GLIB_SH1106_128X64 *g) {
            for(int i = 0;i<this->_childControls.count();i++) {
                this->_childControls.item(i).draw(g);
            }
        };

        
};

#endif