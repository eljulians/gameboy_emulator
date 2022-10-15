#pragma once

#include <stdint.h>
#include "registers.hpp"

class CPU;

class ALU_16bit {
    private:
        CPU& cpu;
        RegisterPair& hl;
        Register_16bit& sp;
        Flag& flags;
        void setAdditionFlags(uint16_t a, uint16_t b);
        void setSubtractionFlags(uint16_t a, uint16_t b);

    public:
        ALU_16bit(CPU& cpu, RegisterPair& hl, Register_16bit& sp, Flag& flags)
            : cpu(cpu), hl(hl), sp(sp), flags(flags) {};
        void add_hl_r16(RegisterPair register_);
        void add_hl_sp(Register_16bit sp);
        void add_sp_s8();

        void inc_r16(RegisterPair register_);
        void inc_sp(Register_16bit sp);

        void dec_r16(RegisterPair register_);
        void dec_sp(Register_16bit sp);
};