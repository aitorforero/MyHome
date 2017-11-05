#ifndef TWOBUTTONSEVENTHANDLER_H
#define TWOBUTTONSEVENTHANDLER_H

#include <EventArgs.h>

class TwoButtonsEventHandler {
    public:
        virtual void onLeftButtonClick(EventArgs* e) {};
        virtual void onRightButtonClick(EventArgs* e) {};;
        virtual void onLeftButtonDown(EventArgs* e) {};
        virtual void onRightButtonDown(EventArgs* e) {};
        virtual void onLeftButtonUp(EventArgs* e) {};
        virtual void onRightButtonUp(EventArgs* e) {};
        virtual void onTwoButtonsClick(EventArgs* e) {};
};

#endif
