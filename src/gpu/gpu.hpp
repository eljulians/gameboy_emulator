#pragma once

#include <SDL2/SDL.h>
#include <vector>
#include "lcd_control.hpp"
#include "tile.hpp"
#include "background.hpp"
#include "../mmu/mmu.hpp"

class GameBoy;

class GPU {
    public:
        GPU(MMU& mmu, LCDControl& lcdControl) :
            mmu(mmu),
            lcdControl(lcdControl),
            backgroundBuffer(lcdControl, mmu)
        {};
        void init_sdl();
        void update(uint8_t cycles);
    
    private:
        MMU& mmu;
        LCDControl& lcdControl;
        BackgroundBuffer backgroundBuffer;
        SDL_Window* window;
        SDL_Surface* surface;
};