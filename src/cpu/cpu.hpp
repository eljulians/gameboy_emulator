#pragma once
#include "registers.hpp"
#include "../gameboy.hpp"

class CPU {
    public:
        CPU(GameBoy& gameBoy);

    private:
        Register_8bit A, B, C, D, E, F, H, L;
        RegisterPair *AF, *BC, *DE, *HL;
        Register_16bit PC, SP;
        Flag *flags;
        GameBoy& gameBoy;
};