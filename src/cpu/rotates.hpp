#pragma once

#include <stdint.h>
#include "registers.hpp"

class CPU;

class Rotates {
    private:
        CPU& cpu;
        uint8_t rotateLeft(uint8_t value, bool carry);
        uint8_t rotateRight(uint8_t value, bool carry);

    public:
        Rotates(CPU& cpu) : cpu(cpu) {};
        void rlca();
        void rla();

        void rrca();
        void rra();

        void rlc_r8(Register_8bit& register_);
        void rlc_hl();
        void rl_r8(Register_8bit& register_);
        void rl_hl();

        void rrc_r8(Register_8bit& register_);
        void rrc_hl();
        void rr_r8(Register_8bit& register_);
        void rr_hl();

        void sla_r8(Register_8bit& register_);
        void sla_hl();

        void sra_r8(Register_8bit& register_);
        void sra_hl();

        void srl_r8(Register_8bit& register_);
        void srl_hl();
};