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
    SDL_Event event;

    while(true) {

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

        while (SDL_PollEvent(&event)) {
            //auto joypad = mmu.read_8bit(0xFF00);
            uint8_t joypad = 0xFF;
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            spdlog::info("left");
                            joypad = resetBit(joypad, 4);
                            joypad = resetBit(joypad, 1);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_RIGHT:
                            spdlog::info("right");
                            joypad = resetBit(joypad, 4);
                            joypad = resetBit(joypad, 0);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_UP:
                            joypad = resetBit(joypad, 4);
                            joypad = resetBit(joypad, 2);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_DOWN:
                            spdlog::info("down");
                            joypad = resetBit(joypad, 4);
                            joypad = resetBit(joypad, 3);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_RETURN:
                        case SDLK_KP_ENTER:
                            spdlog::info("press return/enter");
                            joypad = resetBit(joypad, 5);
                            joypad = resetBit(joypad, 3);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_a:
                            spdlog::info("press a");
                            joypad = resetBit(joypad, 5);
                            joypad = resetBit(joypad, 1);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_s:
                            spdlog::info("press s");
                            joypad = resetBit(joypad, 5);
                            joypad = resetBit(joypad, 0);
                            mmu.io.at(0) = joypad;
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            spdlog::info("left");
                            joypad = setBit(joypad, 4);
                            joypad = setBit(joypad, 1);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_RIGHT:
                            spdlog::info("right");
                            joypad = setBit(joypad, 4);
                            joypad = setBit(joypad, 0);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_UP:
                            spdlog::info("up");
                            joypad = setBit(joypad, 4);
                            joypad = setBit(joypad, 2);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_DOWN:
                            spdlog::info("down");
                            joypad = resetBit(joypad, 4);
                            joypad = resetBit(joypad, 3);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_RETURN:
                        case SDLK_KP_ENTER:
                            spdlog::info("release return/enter");
                            joypad = setBit(joypad, 5);
                            joypad = setBit(joypad, 3);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_a:
                            spdlog::info("release a (mapped to b)");
                            joypad = setBit(joypad, 5);
                            joypad = setBit(joypad, 1);
                            mmu.io.at(0) = joypad;
                            break;
                        case SDLK_s:
                            spdlog::info("release s (mapped to a)");
                            joypad = setBit(joypad, 5);
                            joypad = setBit(joypad, 0);
                            mmu.io.at(0) = joypad;
                            break;
                        //mmu.write_8bit(0xFF00, joypad);
                    }
                    break;

                default:
                    break;
            }
        }

    }

}