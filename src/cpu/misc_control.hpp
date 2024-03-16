#pragma once

#include "../mmu/mmu.hpp"


class CPU;

class MiscControl {
    private:
        CPU& cpu;
        MMU& mmu;

    public:
        MiscControl(CPU& cpu, MMU& mmu) : cpu(cpu), mmu(mmu) {};

        int nop();
        int stop();
        int halt();
        int di();
        int ei(); 
};