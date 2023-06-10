#pragma once

#include <stdint.h>
#include "registers.hpp"

class CPU;

class Bit {
    private:
        CPU& cpu;

    public:
        Bit(CPU& cpu) : cpu(cpu) {};
        int8_t bit(Register_8bit register_, uint8_t bit);
        int8_t bit_hl(uint8_t bit);

        int8_t set(Register_8bit& register_, uint8_t bit);
        int8_t set_hl(uint8_t bit);

        int8_t res(Register_8bit& register_, uint8_t bit);
        int8_t res_hl(uint8_t bit);
};