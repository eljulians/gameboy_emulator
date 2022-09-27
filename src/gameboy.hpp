#pragma once
#include "cpu/cpu.hpp"
#include "gpu/gpu.hpp"
#include "mmu/mmu.hpp"

class GameBoy {
    private:
        CPU cpu;
        GPU gpu;
        MMU mmu;
    public:
        GameBoy();
};