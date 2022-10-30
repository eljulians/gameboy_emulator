#pragma once

#include <stdint.h>
#include "registers.hpp"

class CPU;

class Rotates {
    private:
        CPU& cpu;
        void rotateLeft(Register_8bit& register_, bool carry);
        void rotateRight(Register_8bit& register_, bool carry);

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
};