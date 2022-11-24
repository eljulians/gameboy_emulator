#pragma once
#include <string>
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "mmu/mmu.hpp"
#include "mmu/cartridge.hpp"

class GameBoy {
    private:
        GPU gpu;

    public:
        GameBoy() : cpu(*this), gpu(*this), mmu(*this), cartridge("") {};
        GameBoy(std::string romPath) : cpu(*this), gpu(*this), mmu(*this), cartridge(romPath) {};
        CPU cpu;
        MMU mmu;
        CartridgeROMOnly cartridge;
        void mainLoop();
};