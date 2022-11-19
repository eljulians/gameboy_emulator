#pragma once
#include "registers.hpp"
#include "alu_8bit.hpp"
#include "loads_8bit.hpp"
#include "control_unit.hpp"

#define CONDITION_NZ 0
#define CONDITION_Z 1
#define CONDITION_NC 2
#define CONDITION_C 3

class GameBoy;
class ControlUnit;

enum class Condition {
    NZ,
    Z,
    NC,
    C,
};

class CPU {
    public:
        CPU(GameBoy& gameBoy);
        Register_8bit A, B, C, D, E, F, H, L;
        RegisterPair *AF, *BC, *DE, *HL;
        Register_16bit PC, SP;
        Flag *flags;
        Loads8bit *loads8bit;

        uint8_t fetchByte();
        int8_t fetchSignedByte();
        uint16_t fetch2bytes();
        uint16_t getPC();
        void setPC(uint16_t pc);
        void incrementPC();
        void push_onto_stack(uint8_t value);
        void push_address_onto_stack(uint16_t value);
        uint8_t pop_from_stack();
        uint16_t pop_address_from_stack();
        void setSP(uint16_t sp);
        uint16_t getSP();
        Flag* getFlags();
        bool getCondition(Condition condition);
        ControlUnit controlUnit;


    private:
        GameBoy& gameBoy;

    friend class Loads8bit;
    friend class ALU_16bit;
    friend class Rotates;
};