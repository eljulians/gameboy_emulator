#define FMT_HEADER_ONLY

#include "spdlog/spdlog.h"

#include <iostream>
#include "gameboy.hpp"
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "mmu/mmu.hpp"
#include "interrupts/interrupt_manager.hpp"
#include "cpu/timer/timer.hpp"


void GameBoy::mainLoop() {
    int cycles;

    gpu.init_sdl();
    cartridge.loadRom();

    while(true) {
        /*
        spdlog::info("FF42 0x{0:x}", mmu.read_8bit(0xFF42));

        if (mmu.read_8bit(0xFF42) != 0) {
            spdlog::info("foo");
        }
        */
        bool interrupt = interruptManager.handle();
        cycles = cpu.controlUnit.execute();

        if (interrupt) {
            cycles += 20;
        }

        gpu.update(cycles);
        timerManager.tick(cycles);
    }

}