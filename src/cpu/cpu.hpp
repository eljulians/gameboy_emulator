#pragma once
#include "registers.hpp"
#include "alu_8bit.hpp"

class GameBoy;

class CPU {
    public:
        CPU(GameBoy& gameBoy);
        uint8_t fetchByte();
        uint16_t fetch2bytes();
        uint16_t getPC();
        void setPC(uint16_t pc);
        void incrementPC();
        void push_onto_stack(uint8_t value);
        uint8_t pop_from_stack();

    private:
        Register_8bit A, B, C, D, E, F, H, L;
        RegisterPair *AF, *BC, *DE, *HL;
        Register_16bit PC, SP;
        Flag *flags;
        GameBoy& gameBoy;

    friend class Loads8bit;
};