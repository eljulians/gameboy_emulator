#include <SDL2/SDL.h>
#include <iostream>
#include <string>
#include <SDL2/SDL_thread.h>

#include "spdlog/spdlog.h"

#include "gameboy.hpp"


#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 140

int threadFunction(void* data) {
    std::cout << "Hello from thread";

    return 0;
}

int main(int argc, char *argv[]) {

    spdlog::set_level(spdlog::level::info);

    std::string romPath = argv[1];
    GameBoy gameBoy = GameBoy(romPath);

    // Divider, is this correct?
    gameBoy.mmu.write_8bit(0xFF04, 0x00);

    gameBoy.mmu.write_8bit(0xFF05, 0x00);
    gameBoy.mmu.write_8bit(0xFF06, 0x00);
    gameBoy.mmu.write_8bit(0xFF07, 0x00);
    gameBoy.mmu.write_8bit(0xFF10, 0x80);
    gameBoy.mmu.write_8bit(0xFF11, 0xBF);
    gameBoy.mmu.write_8bit(0xFF12, 0xF3);
    gameBoy.mmu.write_8bit(0xFF14, 0xBF);
    gameBoy.mmu.write_8bit(0xFF16, 0x3F);
    gameBoy.mmu.write_8bit(0xFF17, 0x00);
    gameBoy.mmu.write_8bit(0xFF19, 0xBF);
    gameBoy.mmu.write_8bit(0xFF1A, 0x7F);
    gameBoy.mmu.write_8bit(0xFF1B, 0xFF);
    gameBoy.mmu.write_8bit(0xFF1C, 0x9F);
    gameBoy.mmu.write_8bit(0xFF1E, 0xBF);
    gameBoy.mmu.write_8bit(0xFF20, 0xFF);
    gameBoy.mmu.write_8bit(0xFF21, 0x00);
    gameBoy.mmu.write_8bit(0xFF22, 0x00);
    gameBoy.mmu.write_8bit(0xFF23, 0xBF);
    gameBoy.mmu.write_8bit(0xFF24, 0x77);
    gameBoy.mmu.write_8bit(0xFF25, 0xF3);
    gameBoy.mmu.write_8bit(0xFF26, 0xF1);
    gameBoy.mmu.write_8bit(0xFF40, 0x91);
    //gameBoy.mmu.write_8bit(0xFF41, 0x85);

    // Which one is correct for LCDC and STAT??
    gameBoy.mmu.write_8bit(0xFF40, 0);
    gameBoy.mmu.write_8bit(0xFF41, 0);

    gameBoy.mmu.write_8bit(0xFF42, 0x00);
    gameBoy.mmu.write_8bit(0xFF43, 0x00);
    gameBoy.mmu.write_8bit(0xFF45, 0x00);
    gameBoy.mmu.write_8bit(0xFF47, 0xFC);
    gameBoy.mmu.write_8bit(0xFF48, 0xFF);
    gameBoy.mmu.write_8bit(0xFF49, 0xFF);
    gameBoy.mmu.write_8bit(0xFF4A, 0x00);
    gameBoy.mmu.write_8bit(0xFF4B, 0x00);
    gameBoy.mmu.write_8bit(0xFFFF, 0x00);

    // Manually stub joypad other e.g. Tetris can get mad
    gameBoy.mmu.io.at(0) = 0xFF;

    gameBoy.cpu.halted = false;
    gameBoy.cpu.disableInterrupts();

    gameBoy.mainLoop();
}