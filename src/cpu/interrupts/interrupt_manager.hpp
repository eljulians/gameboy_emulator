#pragma once

#include <stdint.h>
#include <vector>

#include "interrupt.hpp"

class MMU;
class CPU;
class Interrupt;

typedef std::vector<Interrupt> InterruptVector;

class InterruptManager {
    public:
        InterruptManager(MMU& mmu, CPU& cpu) : 
            mmu(mmu),
            cpu(cpu),
            vblank(mmu, InterruptEnum::VBlank),
            lcdc(mmu, InterruptEnum::LCDC),
            timer(mmu, InterruptEnum::Timer),
            serial(mmu, InterruptEnum::SerialTransfer),
            keypad(mmu, InterruptEnum::Keypad)
        {};
        Interrupt vblank;
        Interrupt lcdc;
        Interrupt timer;
        Interrupt serial;
        Interrupt keypad;
        InterruptVector getInterrupts();
        bool handle();

    private:
        MMU& mmu;
        CPU& cpu;
        int8_t cycles = 0;
};