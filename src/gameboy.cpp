#define FMT_HEADER_ONLY

#include <SDL2/SDL.h>
#include "spdlog/spdlog.h"

#include <iostream>
#include "gameboy.hpp"
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "mmu/mmu.hpp"
#include "cpu/interrupts/interrupt_manager.hpp"
#include "cpu/timer/timer.hpp"
#include "common/bit_operations.hpp"



void GameBoy::mainLoop() {
    int cycles;

    gpu.init_sdl();

    int screenNumber = 0;

    while(true) {

        if (screenNumber == 3) {
            //spdlog::set_level(spdlog::level::debug);
        }

        bool interrupt = cpu.interruptManager->handle();

        if (cpu.halted) {
            // TODO: refactor this crap for the mf halt bug
            for (Interrupt interrupt: cpu.interruptManager->getInterrupts()) {
                if (interrupt.isEnabled() && interrupt.isFlagged()) {
                    cpu.halted = false;
                    break;
                }

            }
        }


        spdlog::debug("LY {}", mmu.read_8bit(0xFF44));

        if (!cpu.halted) {
            // TODO return m-states already instead
            cycles = (int)cpu.controlUnit.execute() / 4;
        } else {
            cycles = 1;
        }

        /*
        if (interrupt) {
            cycles = 5;
        }
        */

        gpu.update(cycles);
        cpu.timerManager->tick(cycles);
        joypad.handlePressed();
    }

}