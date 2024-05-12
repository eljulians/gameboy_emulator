#pragma once

#include <stdint.h>

#define _2_BYTE_OPCODE_PREFIX 0xCB

class CPU;
class MMU;

class ControlUnit {
    private:
        CPU& cpu;
        MMU& mmu;
        uint16_t fetch2ByteOpcode();

    public:
        ControlUnit(CPU& cpu, MMU& mmu) : cpu(cpu), mmu(mmu) {};
        uint16_t fetch();
        void decode(uint16_t opcode);
        uint8_t execute();
};