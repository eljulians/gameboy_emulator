#pragma once

#include <stdint.h>

#define _2_BYTE_OPCODE_PREFIX 0xCB

class CPU;

class ControlUnit {
    private:
        CPU& cpu;
        uint16_t fetch2ByteOpcode();

    public:
        ControlUnit(CPU& cpu) : cpu(cpu) {};
        uint16_t fetch();
        void decode(uint16_t opcode);
        uint8_t execute();
};