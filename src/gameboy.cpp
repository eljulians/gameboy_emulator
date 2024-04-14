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

        if (SDL_PollEvent(&event)) {
            // TODO select button
            switch (event.type) {
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            joypad.left.press();
                            break;
                        case SDLK_RIGHT:
                            joypad.right.press();
                            break;
                        case SDLK_UP:
                            joypad.up.press();
                            break;
                        case SDLK_DOWN:
                            joypad.down.press();
                            break;
                        case SDLK_RETURN:
                        case SDLK_KP_ENTER:
                            joypad.start.press();
                            break;
                        case SDLK_a:
                            joypad.b.press();
                            break;
                        case SDLK_s:
                            joypad.a.press();
                            break;
                    }
                    break;

                case SDL_KEYUP:
                    switch (event.key.keysym.sym) {
                        case SDLK_LEFT:
                            joypad.left.release();
                            break;
                        case SDLK_RIGHT:
                            joypad.right.release();
                            break;
                        case SDLK_UP:
                            joypad.up.release();
                            break;
                        case SDLK_DOWN:
                            joypad.down.release();
                            break;
                        case SDLK_RETURN:
                        case SDLK_KP_ENTER:
                            joypad.start.release();
                            break;
                        case SDLK_a:
                            joypad.b.release();
                            break;
                        case SDLK_s:
                            joypad.a.release();
                            break;
                    }
                    break;

                default:
                    break;
            }
        }

    }

}