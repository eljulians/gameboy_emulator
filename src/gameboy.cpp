#include "gameboy.hpp"
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "mmu/mmu.hpp"


void GameBoy::mainLoop() {
    uint8_t cycles;

    cartridge.loadRom();

    while(true) {
        cycles = cpu.controlUnit.execute();
    }

}