#include "joypad.hpp"
#include "../common/bit_operations.hpp"


void Button::press() {
    pressed = true;
}

void Button::release() {
    pressed = false;
}

bool Button::isPressed() {
    return pressed;
}


void Joypad::setSelection(uint8_t ff00) {
    buttonsSelected = !testBit(ff00, 5);
    dpadSelected = !testBit(ff00, 4);
}

uint8_t Joypad::getState() {
    uint8_t state = 0xFF;


    if (dpadSelected) {
        state = resetBit(state, 4);

        if (up.isPressed()) {
            state = resetBit(state, 2);
        } else {
            state = setBit(state, 2);
        }
        if (down.isPressed()) {
            state  = resetBit(state, 3);
        } else {
            state  = setBit(state, 3);
        }
        if (left.isPressed()) {
            state = resetBit(state, 1);
        } else {
            state = setBit(state, 1);
        }
        if (right.isPressed()) {
            state = resetBit(state, 0);
        } else {
            state = setBit(state, 0);
        }
    }

    if (buttonsSelected) {
        state = resetBit(state, 5);
        if (a.isPressed()) {
            state = resetBit(state, 0);
        } else {
            state = setBit(state, 0);
        }
        if (b.isPressed()) {
            state = resetBit(state, 1);
        } else {
            state = setBit(state, 1);
        }
        if (start.isPressed()) {
            state = resetBit(state, 3);
        } else {
            state = setBit(state, 3);
        }
        if (select.isPressed()) {
            state = resetBit(state, 2);
        } else {
            state = setBit(state, 2);
        }
    }

    return state;
}