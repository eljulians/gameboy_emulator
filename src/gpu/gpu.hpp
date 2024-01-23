#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "lcd_control.hpp"

class GameBoy;

class GPU {
    public:
        GPU(GameBoy& gameBoy, LCDControl& lcdControl) : gameBoy(gameBoy), lcdControl(lcdControl) {};
        void init_sdl();
        void update(uint8_t cycles);
        void getFirstTileSet();
        void getSecondTileSet();

    
    private:
        GameBoy& gameBoy;
        LCDControl& lcdControl;
        SDL_Window* window;
        SDL_Surface* surface;
};