#ifndef BUTTONEVENTHANDLER_H
#define BUTTONEVENTHANDLER_H


class ButtonEventHandler {
    public:
        virtual void onLeftButtonClick(RoomControl* rc) = 0;
        virtual void onRightButtonClick(RoomControl* rc) = 0;
};

#endif
