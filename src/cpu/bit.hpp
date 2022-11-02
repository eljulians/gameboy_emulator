#pragma once

#include <stdint.h>
#include "registers.hpp"

class CPU;

class Bit {
    private:
        CPU& cpu;

    public:
        Bit(CPU& cpu) : cpu(cpu) {};
        void bit(Register_8bit register_, uint8_t bit);
        void bit_hl(uint8_t bit);

        void set(Register_8bit& register_, uint8_t bit);
        void set_hl(uint8_t bit);

        void res(Register_8bit& register_, uint8_t bit);
        void res_hl(uint8_t bit);
};