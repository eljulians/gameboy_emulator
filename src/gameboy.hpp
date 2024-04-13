#pragma once

#include <string>
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "gpu/lcd_control.hpp"
#include "mmu/mmu.hpp"
#include "mmu/cartridge.hpp"
#include "cpu/interrupts/interrupt_manager.hpp"
#include "joypad/joypad.hpp"
//#include "cpu/timer/timer.hpp"

class GameBoy {
    public:
 
        GameBoy() : 
            joypad(),
            mmu(*this, joypad),
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
            mmu(*this, joypad),
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
        Joypad joypad;
        AbstractCartridge* cartridge;
        //InterruptManager interruptManager;
        LCDControl lcdControl;
        //TimerManager timerManager;

        void mainLoop();
};