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
        int8_t add_hl_r16(RegisterPair register_);
        int8_t add_hl_sp();
        int8_t add_sp_s8();

        int8_t inc_r16(RegisterPair register_);
        int8_t inc_sp();

        int8_t dec_r16(RegisterPair register_);
        int8_t dec_sp();
};