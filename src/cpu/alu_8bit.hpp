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
        void setSubtractionFlags(uint8_t a, uint8_t b);

    public:
        ALU_8bit(CPU& cpu, Register_8bit &aAddress, RegisterPair &hl, Flag &flagsAddress)
            : cpu(cpu), a(aAddress), hl(hl), flags(flagsAddress) {};
        void add_a_r8(Register_8bit &register_);
        void add_a_hl();
        void add_a_n8();

        void adc_a_r8(Register_8bit &register_);
        void adc_a_hl();
        void adc_a_n8();

        int8_t sub_a_r8(Register_8bit &register_);
        int8_t sub_a_hl();
        int8_t sub_a_n8();

        int8_t sbc_a_r8(Register_8bit &register_);
        int8_t sbc_a_hl();
        int8_t sbc_a_n8();

        int8_t and_a_r8(Register_8bit &register_);
        int8_t and_a_hl();
        int8_t and_a_n8();

        int8_t or_a_r8(Register_8bit &register_);
        int8_t or_a_hl();
        int8_t or_a_n8();

        int8_t xor_a_r8(Register_8bit &register_);
        int8_t xor_a_hl();
        int8_t xor_a_n8();

        int8_t cp_a_r8(Register_8bit &register_);
        int8_t cp_a_hl();
        int8_t cp_a_n8();

        int8_t inc_r8(Register_8bit &register_);
        int8_t inc_hl();

        int8_t dec_r8(Register_8bit &register_);
        int8_t dec_hl();
};