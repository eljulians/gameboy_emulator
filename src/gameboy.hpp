#pragma once
#include <string>
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "gpu/lcd_control.hpp"
#include "mmu/mmu.hpp"
#include "mmu/cartridge.hpp"
#include "interrupts/interrupt_manager.hpp"

class GameBoy {
    public:
        GameBoy() : 
            cpu(*this),
            mmu(*this),
            cartridge(""),
            interruptManager(this->mmu, this->cpu),
            lcdControl(this->mmu, this->interruptManager),
            gpu(*this, this->lcdControl)
        {
        };
        GameBoy(std::string romPath) :
            cpu(*this),
            gpu(*this, this->lcdControl),
            mmu(*this),
            cartridge(romPath),
            interruptManager(this->mmu, this->cpu),
            lcdControl(this->mmu, this->interruptManager)
        {
        };

        CPU cpu;
        MMU mmu;
        GPU gpu;
        CartridgeROMOnly cartridge;
        InterruptManager interruptManager;
        LCDControl lcdControl;
        void mainLoop();
};