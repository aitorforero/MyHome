#ifndef BUTTONEVENTHANDLER_H
#define BUTTONEVENTHANDLER_H

template <class t> class ButtonEventHandler {
    public:
        virtual void onLeftButtonClick(t* rc) = 0;
        virtual void onRightButtonClick(t* rc) = 0;
        virtual void onLeftButtonDown(t* rc) = 0;
        virtual void onRightButtonDown(t* rc) = 0;
        virtual void onLeftButtonUp(t* rc) = 0;
        virtual void onRightButtonUp(t* rc) = 0;
};

#endif
