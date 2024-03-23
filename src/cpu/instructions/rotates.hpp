#pragma once

#include <stdint.h>
#include "../registers.hpp"

class CPU;

class Rotates {
    private:
        CPU& cpu;
        uint8_t rotateLeft(uint8_t value, bool carry);
        uint8_t rotateRight(uint8_t value, bool carry);

    public:
        Rotates(CPU& cpu) : cpu(cpu) {};
        int8_t rlca();
        int8_t rla();

        int8_t rrca();
        int8_t rra();

        int8_t rlc_r8(Register_8bit& register_);
        int8_t rlc_hl();
        int8_t rl_r8(Register_8bit& register_);
        int8_t rl_hl();

        int8_t rrc_r8(Register_8bit& register_);
        int8_t rrc_hl();
        int8_t rr_r8(Register_8bit& register_);
        int8_t rr_hl();

        int8_t sla_r8(Register_8bit& register_);
        int8_t sla_hl();

        int8_t sra_r8(Register_8bit& register_);
        int8_t sra_hl();

        int8_t srl_r8(Register_8bit& register_);
        int8_t srl_hl();

        int8_t swap_r8(Register_8bit& register_);
        int8_t swap_hl();
};