/*
https://gbdev.io/pandocs/Timer_and_Divider_Registers.html
*/

#pragma once

#include <map>
#include <stdint.h>
#include "../../interrupts/interrupt.hpp"

#define CLOCK_HZ 4190000  // 4,19 MHz

#define DIVIDER_ADDRESS 0xFF04 
#define TIMER_COUNTER_ADDRESS 0xFF05  // aka TIMA
#define TIMER_MODULO_ADDRESS 0xFF06   // aka TMA
#define TIMER_CONTROL_ADDRESS 0xFF07  // aka TAC

/*
#define MODE_0_CYCLES 1024 // 4096 Hz
#define MODE_1_CYCLES 16 // 262144 Hz
#define MODE_2_CYCLES 64 // 65536 Hz
#define MODE_3_CYCLES 256 // 16384 Hz
*/

/*
#define MODE_0_CYCLES 4096 // 4096 Hz
#define MODE_1_CYCLES 262144 // 262144 Hz
#define MODE_2_CYCLES 65536 // 65536 Hz
#define MODE_3_CYCLES 16384 // 16384 Hz
*/

#define MODE_0_CYCLES 256
#define MODE_1_CYCLES 4
#define MODE_2_CYCLES 16
#define MODE_3_CYCLES 64

class MMU;
class CPU;

typedef int INPUT_CLOCK_HZ;

const std::map<int, INPUT_CLOCK_HZ> INPUT_CLOCK_SELECT_CYCLES_MAP {
    {0b00, MODE_0_CYCLES},
    {0b01, MODE_1_CYCLES},
    {0b10, MODE_2_CYCLES},
    {0b11, MODE_3_CYCLES},
};


class TimerControl {
    public:
        TimerControl(MMU& mmu) : mmu(mmu) {};
        INPUT_CLOCK_HZ getInputClockSelect();
        bool isEnabled();
    
    private:
        MMU& mmu;
};


class TimerModulo {
    // When TimerCounter (TIMA) overflows, this value is loaded
    public:
        TimerModulo(MMU& mmu) : mmu(mmu) {};
        int getValue();

    private:
        MMU& mmu;
};

class TimerCounter {
    // On overflow, reset to value specified by TMA and request interrupt
    public:
        TimerCounter(MMU& mmu, TimerControl& timerControl, TimerModulo& timerModulo, Interrupt& interrupt) :
            mmu(mmu),
            timerControl(timerControl),
            timerModulo(timerModulo),
            interrupt(interrupt),
            currentCycles(0)
            {};
        void tick(int cycles);

    private:
        MMU& mmu;
        TimerControl& timerControl;
        Interrupt& interrupt;
        TimerModulo& timerModulo;
        int currentCycles;
};

class Divider {
    // Internal divider is 16 bit, but only upper 8 bits are mapped to memory
    // On overflow, divider writes directly to the memory address, no MMU mapping,
    // since hardware resets DIV when writting on it
    public:
        Divider(MMU& mmu) : mmu(mmu), internalDivider(0), elapsedCycles(0) {};
        void tick(int cycles);
        void resetInternalDivider();

    private:
        MMU& mmu;
        int internalDivider;
        int elapsedCycles;
};

class TimerManager {
    public:
        TimerManager(
            MMU& mmu,
            Interrupt& interrupt
        ) :
            mmu(mmu),
            timerControl(mmu),
            timerModulo(mmu),
            timerCounter(mmu, timerControl, timerModulo, interrupt),
            divider(mmu)
        {};
        void tick(int cycles);

    private:
        MMU& mmu;
        TimerControl timerControl;
        TimerModulo timerModulo;
        TimerCounter timerCounter;
        Divider divider;
};