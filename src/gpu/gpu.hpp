#pragma once

#include "background.hpp"
#include "sprite.hpp"

class GameBoy;
class LCDControl;
//class BackgroundBuffer;
class MMU;
class SDL_Renderer;
class SDL_Window;
class SpriteClient;

class GPU {
    public:
        GPU(MMU& mmu, LCDControl& lcdControl) :
            mmu(mmu),
            lcdControl(lcdControl),
            backgroundBuffer(lcdControl, mmu),
            spriteClient(lcdControl, mmu)
        {};
        void init_sdl();
        void update(uint8_t cycles);
    
    private:
        MMU& mmu;
        LCDControl& lcdControl;
        BackgroundBuffer backgroundBuffer;
        SpriteClient spriteClient;
        SDL_Renderer *renderer;
        SDL_Window *window;
        int lastDrawnScanline = -1;
};