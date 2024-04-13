#pragma once

#include <stdint.h>

/*
Joypad is mapped to $FF00
*/



class Button {
    public:
        Button(int selectionBit, int bit) : selectionBit(selectionBit), bit(bit) {};
        void press();
        void release();
        bool isPressed();
    
    private:
        bool pressed = false;
        int selectionBit;
        int bit;
};

class Joypad {
    public:
        Joypad()
            : up(Button(4, 2)),
            down(Button(4, 3)),
            left(Button(4, 1)),
            right(Button(4, 0)),
            a(Button(5, 0)),
            b(Button(5, 1)),
            start(Button(5, 3)),
            select(Button(5, 2))
        {};

        void setSelection(uint8_t ff00);
        uint8_t getState();
        void handlePressed();

        Button a;
        Button b;
        Button start;
        Button select;

        Button up;
        Button down;
        Button left;
        Button right;

    private:
        bool buttonsSelected = false;
        bool dpadSelected = false;
};