#pragma once

#include <stdint.h>
#include "registers.hpp"

class ALU_8bit {
    private:
        Register_8bit &a;
        Flag &flags;
        void setAdditionFlags(uint8_t a, uint8_t b);

    public:
        ALU_8bit(Register_8bit &aAddress, Flag &flagsAddress) : a(aAddress), flags(flagsAddress) {};
        void add_a_r8(Register_8bit &register_);
        void add_a_hl(Register_16bit &hl);
        void add_a_n8(uint8_t value);
        void adc_a_r8(Register_8bit &register_);
        void adc_a_hl(Register_16bit &hl);
        void adc_a_n8(uint8_t value);
};