#pragma once
#include "../gameboy.hpp"

class GPU {
    public:
        GPU(GameBoy& gameBoy);
    
    private:
        GameBoy& gameBoy;
};