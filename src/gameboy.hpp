#pragma once
#include <string>
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "gpu/lcd_control.hpp"
#include "mmu/mmu.hpp"
#include "mmu/cartridge.hpp"
#include "cpu/interrupts/interrupt_manager.hpp"
//#include "cpu/timer/timer.hpp"

class GameBoy {
    public:
 
        GameBoy() : 
            mmu(*this),
            cartridge(),
            //interruptManager(this->mmu, this->cpu),
            lcdControl(this->mmu, *this->cpu.interruptManager),
            gpu(this->mmu, this->lcdControl),
            cpu(*this, this->gpu)
            //timerManager(this->mmu, this->interruptManager.timer)
        {
            cartridge = createCartridge("roms/tetris.gb");
        };

        GameBoy(std::string romPath) :
            gpu(this->mmu, this->lcdControl),
            cpu(*this, this->gpu),
            mmu(*this),
            //cartridge(romPath),
            //interruptManager(this->mmu, this->cpu),
            lcdControl(this->mmu, *this->cpu.interruptManager)
            //timerManager(this->mmu, this->interruptManager.timer)
        {
            cartridge = createCartridge(romPath);
        };

        CPU cpu;
        MMU mmu;
        GPU gpu;
        AbstractCartridge* cartridge;
        //InterruptManager interruptManager;
        LCDControl lcdControl;
        //TimerManager timerManager;

        void mainLoop();
};