#include "gameboy.hpp"
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "mmu/mmu.hpp"
#include "interrupts/interrupt_manager.hpp"


void GameBoy::mainLoop() {
    uint8_t cycles;

    gpu.init_sdl();
    cartridge.loadRom();

    while(true) {
        cycles = cpu.controlUnit.execute();
        gpu.update(cycles);
        interruptManager.handle();
    }

}