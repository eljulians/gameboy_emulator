#define FMT_HEADER_ONLY

#include <SDL2/SDL.h>
#include "spdlog/spdlog.h"
#include <chrono>

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

    //spdlog::set_level(spdlog::level::critical);

    gpu.init_sdl();

    int screenNumber = 0;

    while(true) {
        auto start = std::chrono::system_clock::now();

        if (screenNumber == 3) {
            //spdlog::set_level(spdlog::level::debug);
        }

        bool interrupt = cpu.interruptManager->handle();

        auto interruptStart = std::chrono::system_clock::now();
        if (cpu.halted) {
            // TODO: refactor this crap for the mf halt bug
            for (Interrupt interrupt: cpu.interruptManager->getInterrupts()) {
                if (interrupt.isEnabled() && interrupt.isFlagged()) {
                    cpu.halted = false;
                    break;
                }

            }
        }
        auto interruptEnd = std::chrono::system_clock::now();
        auto interruptTime = (interruptEnd  - interruptStart).count();


        auto controlUnitStart = std::chrono::system_clock::now();
        if (!cpu.halted) {
            // TODO return m-states already instead
            cycles = (int)cpu.controlUnit.execute() / 4;
        } else {
            cycles = 1;
        }
        auto controlUnitEnd = std::chrono::system_clock::now();
        auto controlUnit = (controlUnitEnd  - controlUnitStart).count();

        /*
        if (interrupt) {
            cycles = 5;
        }
        */


        auto gpuStart = std::chrono::system_clock::now();
        gpu.update(cycles);
        auto gpuEnd = std::chrono::system_clock::now();
        auto gpuTime = (gpuEnd - gpuStart).count();

        auto timerStart = std::chrono::system_clock::now();
        cpu.timerManager->tick(cycles);
        auto timerEnd = std::chrono::system_clock::now();
        auto timerTime = (timerEnd - timerStart).count();


        auto joypadStart = std::chrono::system_clock::now();
        joypad.tick(cycles);
        auto joypadEnd = std::chrono::system_clock::now();
        auto joypadTime = (joypadEnd - joypadStart).count();

        auto end = std::chrono::system_clock::now();
        auto time = (end - start).count();

        spdlog::info("Halted: {}", cpu.halted);
        spdlog::info("Whole cycle time: {}", time);
        spdlog::info("Interrupt time: {}", interruptTime);
        spdlog::info("Control unit time: {}", controlUnit);
        spdlog::info("GPU time: {}", gpuTime);
        spdlog::info("Timer time: {}", timerTime);
        spdlog::info("Joypad time: {}", joypadTime);
        spdlog::info("======================");
    }

}