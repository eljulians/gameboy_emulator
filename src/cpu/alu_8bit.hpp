#pragma once

#include <stdint.h>
#include "registers.hpp"

class CPU;

class ALU_8bit {
    private:
        CPU& cpu;
        Register_8bit &a;
        RegisterPair &hl;
        Flag &flags;
        void setAdditionFlags(uint8_t a, uint8_t b);

    public:
        ALU_8bit(CPU& cpu, Register_8bit &aAddress, RegisterPair &hl, Flag &flagsAddress)
            : cpu(cpu), a(aAddress), hl(hl), flags(flagsAddress) {};
        void add_a_r8(Register_8bit &register_);
        void add_a_hl();
        void add_a_n8();
        void adc_a_r8(Register_8bit &register_);
        void adc_a_hl();
        void adc_a_n8();
};