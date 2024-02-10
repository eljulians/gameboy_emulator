#pragma once

#include <map>
#include <stdint.h>
#include "../../interrupts/interrupt.hpp"

#define DIVIDER_ADDRESS 0xFF04 
#define TIMER_COUNTER_ADDRESS 0xFF05  // aka TIMA
#define TIMER_MODULO_ADDRESS 0xFF06   // aka TMA
#define TIMER_CONTROL_ADDRESS 0xFF07  // aka TAC

class MMU;
class CPU;

typedef int INPUT_CLOCK_HZ;

const std::map<int, INPUT_CLOCK_HZ> INPUT_CLOCK_SELECT_HZ_MAP {
    {0b00, 4096},
    {0b01, 262144},
    {0b10, 65536},
    {0b11, 16384},
};


class TimerControl {
    public:
        TimerControl(MMU& mmu) : mmu(mmu) {};
        INPUT_CLOCK_HZ getInputClockSelect();
        bool isEnabled();
    
    private:
        MMU& mmu;
};

class TimerCounter {
    public:
        TimerCounter(TimerControl& timerControl, Interrupt& interrupt) :
            timerControl(timerControl),
            interrupt(interrupt)
            {};
        void update(int cycles);

    private:
        TimerControl& timerControl;
        Interrupt& interrupt;
};



class TimerManager {
    public:
        TimerManager(
            MMU& mmu,
            CPU& cpu,
            Interrupt& interrupt
            //CPU& cpu,
            //uint8_t& dividerReference,
            //uint8_t& counterReference,
            //uint8_t& moduloReference
        ) :
            mmu(mmu),
            cpu(cpu),
            timerControl(mmu),
            timerCounter(timerControl, interrupt)
        {};
        void update(int cycles);

    private:
        MMU& mmu;
        CPU& cpu;
        TimerControl timerControl;
        TimerCounter timerCounter;
};