#pragma once

#include <stdint.h>
#include <map>

/*
Joypad is mapped to $FF00
*/

#define BUTTON_SELECTED_BIT 5
#define DIRECTION_BUTTON_SELECTED_BIT 4
#define POLL_SDL_INPUT_EVERY_CYCLES -1

enum class ButtonBitEnum {
    A_Right,
    B_Left,
    Select_Up,
    Start_Down,
};

class _Button {
    public:
        _Button(int selectionBit, ButtonBitEnum bit) : selectionBit(selectionBit), bit(bit) {};
        void press();
        void release();
        bool isPressed();
        int getBitPosition();
        void updateJoypadState(uint8_t& joypadState);
    
    protected:
        bool pressed = false;
        int selectionBit;
        ButtonBitEnum bit;
};

class DirectionButton : public _Button {
    public:
        DirectionButton(ButtonBitEnum mappedBit) : _Button(DIRECTION_BUTTON_SELECTED_BIT, mappedBit) {}
};


// "Letter button" awuful name yeah
class LetterButton : public _Button {
    public:
        LetterButton(ButtonBitEnum mappedBit) : _Button(BUTTON_SELECTED_BIT, mappedBit) {}
};

class Joypad {
    public:
        Joypad()
            : up(DirectionButton(ButtonBitEnum::Select_Up)),
            down(DirectionButton(ButtonBitEnum::Start_Down)),
            left(DirectionButton(ButtonBitEnum::B_Left)),
            right(DirectionButton(ButtonBitEnum::A_Right)),

            a(LetterButton(ButtonBitEnum::A_Right)),
            b(LetterButton(ButtonBitEnum::B_Left)),
            start(LetterButton(ButtonBitEnum::Start_Down)),
            select(LetterButton(ButtonBitEnum::Select_Up))
        {};

        bool tick(int cycles);
        void setSelection(uint8_t ff00);
        uint8_t getState();

        LetterButton a;
        LetterButton b;
        LetterButton start;
        LetterButton select;

        DirectionButton up;
        DirectionButton down;
        DirectionButton left;
        DirectionButton right;

    private:
        int elapsedCycles = 0;
        bool buttonsSelected = false;
        bool dpadSelected = false;
};