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

    spdlog::set_level(spdlog::level::debug);
    spdlog::set_level(spdlog::level::err);

    gpu.init_sdl();

    int screenNumber = 0;

    using Clock = std::chrono::system_clock;
    using Duration = Clock::duration;
    std::cout << Duration::period::num << " , " << Duration::period::den << '\n';

    while(true) {
        auto start = std::chrono::system_clock::now();

        if (screenNumber == 3) {
            //spdlog::set_level(spdlog::level::debug);
        }

        bool interrupt = cpu.interruptManager->handle();

        auto interruptStart = std::chrono::system_clock::now();
        if (cpu.halted) {
            // If CPU is halted, but some interrupt should be triggered, we un-halt, otherwise we'll
            // be stuck
            // TODO: refactor this crap for the mf halt bug, also because it's umperformant af
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
        cycles *= 4;
        auto controlUnitEnd = std::chrono::system_clock::now();
        auto controlUnit = (controlUnitEnd  - controlUnitStart).count();

        int joypadValue = mmu.read_8bit(0xFF00);
        //spdlog::info("FF00 (joypad): {:0X}", joypadValue);

        /*
        if (interrupt) {
            cycles = 5;
        }
        */

        //spdlog::debug("IE ($FFFF): {:0X}", mmu.read_8bit(0xFFFF));


        auto gpuStart = std::chrono::system_clock::now();
        auto end = std::chrono::system_clock::now();
        auto time = (end - start).count();

        gpu.update(cycles, time);
        auto gpuEnd = std::chrono::system_clock::now();
        auto gpuTime = (gpuEnd - gpuStart).count();

        auto timerStart = std::chrono::system_clock::now();
        cpu.timerManager->tick(cycles);
        auto timerEnd = std::chrono::system_clock::now();
        auto timerTime = (timerEnd - timerStart).count();


        auto joypadStart = std::chrono::system_clock::now();
        bool pressed = joypad.tick(cycles);
        auto joypadEnd = std::chrono::system_clock::now();
        auto joypadTime = (joypadEnd - joypadStart).count();

        if (pressed) {
            screenNumber++;
            std::cout << "pressed" << std::endl;
        }

        if (screenNumber==2) {
           // spdlog::set_level(spdlog::level::info);
        }

        //std::cout << std::hex << joypadValue << std::endl;


        auto lcdc = mmu.read_8bit(0xff40);
        auto stat = mmu.read_8bit(0xff41);
        auto ly = mmu.read_8bit(0xff44);
        auto lyc = mmu.read_8bit(0xff45);

        spdlog::debug("AF 0x{0:x}", cpu.AF->get());
        spdlog::debug("BC 0x{0:x}", cpu.BC->get());
        spdlog::debug("DE 0x{0:x}", cpu.DE->get());
        spdlog::debug("HL 0x{0:x}", cpu.HL->get());
        spdlog::debug("PC 0x{0:x}", cpu.PC.get());
        spdlog::debug("SP 0x{0:x}", cpu.SP.get());
        spdlog::debug("Z {}", cpu.flags->get_z());
        spdlog::debug("N {}", cpu.flags->get_n());
        spdlog::debug("H {}", cpu.flags->get_h());
        spdlog::debug("C {}", cpu.flags->get_c());

        spdlog::debug("LCDC: 0x{0:X}", lcdc);
        spdlog::debug("STAT: 0x{0:X}", stat );
        spdlog::debug("LY: 0x{0:X}", ly );
        spdlog::debug("LYC: 0x{0:X}", lyc );

        spdlog::debug("====================");

        auto ffe1 = mmu.read_8bit(0xffe1);
        //spdlog::critical("$FFE1: {:0X}", ffe1);

        /*
        spdlog::info("Whole cycle time: {}", time);
        spdlog::info("Interrupt time: {}", interruptTime);
        spdlog::info("Control unit time: {}", controlUnit);
        spdlog::info("Timer time: {}", timerTime);
        spdlog::info("Joypad time: {}", joypadTime);
        spdlog::info("GPU time: {}", gpuTime);
        spdlog::info("======================");
        */
    }
}