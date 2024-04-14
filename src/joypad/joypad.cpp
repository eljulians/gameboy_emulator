#include <SDL2/SDL.h>

#include "joypad.hpp"
#include "../common/bit_operations.hpp"


void _Button::press() {
    pressed = true;
}

void _Button::release() {
    pressed = false;
}

bool _Button::isPressed() {
    return pressed;
}

int _Button::getBitPosition() {
    return static_cast<int>(bit);
}

void _Button::updateJoypadState(uint8_t& joypadState) {
    if (isPressed()) {
        joypadState = resetBit(joypadState, getBitPosition());
    } else {
        joypadState = setBit(joypadState, getBitPosition());
    }
}


void Joypad::setSelection(uint8_t ff00) {
    buttonsSelected = !testBit(ff00, BUTTON_SELECTED_BIT);
    dpadSelected = !testBit(ff00, DIRECTION_BUTTON_SELECTED_BIT);
}

uint8_t Joypad::getState() {
    uint8_t state = 0xFF;

    if (dpadSelected) {
        state = resetBit(state, DIRECTION_BUTTON_SELECTED_BIT);
        up.updateJoypadState(state);
        down.updateJoypadState(state);
        left.updateJoypadState(state);
        right.updateJoypadState(state);
    }

    if (buttonsSelected) {
        state = resetBit(state, BUTTON_SELECTED_BIT);
        a.updateJoypadState(state);
        b.updateJoypadState(state);
        start.updateJoypadState(state);
        select.updateJoypadState(state);
    }

    return state;
}


void Joypad::handlePressed() {
    SDL_Event event;

    if (SDL_PollEvent(&event)) {
        // TODO select button
        switch (event.type) {
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        left.press();
                        break;
                    case SDLK_RIGHT:
                        right.press();
                        break;
                    case SDLK_UP:
                        up.press();
                        break;
                    case SDLK_DOWN:
                        down.press();
                        break;
                    case SDLK_RETURN:
                    case SDLK_KP_ENTER:
                        start.press();
                        break;
                    case SDLK_a:
                        b.press();
                        break;
                    case SDLK_s:
                        a.press();
                        break;
                }
                break;

            case SDL_KEYUP:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        left.release();
                        break;
                    case SDLK_RIGHT:
                        right.release();
                        break;
                    case SDLK_UP:
                        up.release();
                        break;
                    case SDLK_DOWN:
                        down.release();
                        break;
                    case SDLK_RETURN:
                    case SDLK_KP_ENTER:
                        start.release();
                        break;
                    case SDLK_a:
                        b.release();
                        break;
                    case SDLK_s:
                        a.release();
                        break;
                }
                break;

            default:
                break;
        }
    }
}