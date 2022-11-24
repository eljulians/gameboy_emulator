#include "gameboy.hpp"
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "mmu/mmu.hpp"


void GameBoy::mainLoop() {
    cartridge.loadRom();

    while(true) {
        cpu.controlUnit.execute();
    }

}