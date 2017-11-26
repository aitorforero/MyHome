#ifndef CONTROL_CONTAINER_H
#define CONTROL_CONTAINER_H

#include <vector>
#include <U8glib.h>
#include "Control.h"

using namespace std;

class ControlContainer 
{
    private:
        vector<Control*> _childControls;

    public:
        void addChild(Control* item) {
            _childControls.push_back(item);
        };
    
        void removeChild(Control* item) {
            typename vector<Control*>::iterator _childControlsIter;
			for (_childControlsIter = _childControls.begin() ; _childControlsIter != _childControls.end() ; _childControlsIter++ )  
			{   
				if(*_childControlsIter==item) 
				{
					_childControls.erase(_childControlsIter);
					break;
				}
			};
        };
    
        virtual void drawChildren(U8GLIB_SH1106_128X64 *g) 
        {
            typename vector<Control*>::iterator _childControlsIter;
			for (_childControlsIter = _childControls.begin() ; _childControlsIter != _childControls.end() ; _childControlsIter++ )  
            {
                (*_childControlsIter)->draw(g);
            }
        };
};

#endif