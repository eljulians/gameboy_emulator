#pragma once

#include <stdint.h>
#include "interrupt.hpp"

class MMU;
class CPU;

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
        void handle(int8_t currentCycles);

    private:
        MMU& mmu;
        CPU& cpu;
        int8_t cycles = 0;
};