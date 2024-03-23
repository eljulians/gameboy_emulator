#pragma once
#include "registers.hpp"
#include "instructions/alu_8bit.hpp"
#include "instructions/alu_16bit.hpp"
#include "instructions/loads_8bit.hpp"
#include "instructions/jumps.hpp"
#include "control_unit.hpp"
#include "instructions/bit.hpp"
#include "instructions/rotates.hpp"
#include "instructions/misc_control.hpp"
#include "timer/timer.hpp"
#include "interrupts/interrupt_manager.hpp"
#include "interrupts/interrupt.hpp"
#include "../gpu/gpu.hpp"

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
        CPU(GameBoy& gameBoy, GPU& gpu);
        Register_8bit A, B, C, D, E, F, H, L;
        RegisterPair *AF, *BC, *DE, *HL;
        Register_16bit PC, SP;
        Flag *flags;
        ControlUnit controlUnit;
        Loads8bit *loads8bit;
        ALU_8bit *alu8bit;
        ALU_16bit *alu16bit;
        Jumps *jumps;
        Bit *bit;
        Rotates *rotates;
        MiscControl *miscControl;
        InterruptManager* interruptManager;
        TimerManager* timerManager;
        GPU& gpu;

        bool halted;

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
        void enableInterrupts();
        void disableInterrupts();
        bool areInterruptsEnabled();

    private:
        GameBoy& gameBoy;
        bool interruptEnabled;

    friend class Loads8bit;
    friend class ALU_16bit;
    friend class Rotates;
};