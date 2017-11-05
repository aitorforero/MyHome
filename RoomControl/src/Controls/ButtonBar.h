#ifndef BUTTONBAR_H
#define BUTTONBAR_H

#include "Container.h"
#include "Icon.h"
#include <U8glib.h>
    
class ButtonBar : public Container {
    private:
        Icon* _leftIcon;
        Icon* _centerIcon;
        Icon* _rigthIcon;
    
        

    
    public:
        ButtonBar(int x, int y, int width, int height);
        void setLeftIcon(Icon *icon); 
        void setCenterIcon(Icon *icon);
        void setRightIcon(Icon *icon);
        void calculateLayout();
};

#endif
