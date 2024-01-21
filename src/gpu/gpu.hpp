#pragma once

#include "lcd_control.hpp"

class GameBoy;

class GPU {
    public:
        GPU(GameBoy& gameBoy, LCDControl& lcdControl) : gameBoy(gameBoy), lcdControl(lcdControl) {};
        void update(uint8_t cycles);
    
    private:
        GameBoy& gameBoy;
        LCDControl& lcdControl;
};