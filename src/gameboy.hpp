#pragma once
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "mmu/mmu.hpp"

class GameBoy {
    private:
        GPU gpu;
    public:
        CPU cpu;
        MMU mmu;
        GameBoy();
};