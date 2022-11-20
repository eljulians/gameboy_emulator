#pragma once

#include <stdint.h>
#include "registers.hpp"

class CPU;
enum class Condition;

class Jumps {
    private:
        CPU& cpu;

    public:
        Jumps(CPU& cpu) : cpu(cpu) {};

        int8_t jp_nn();
        int8_t jp_cc_nn(Condition condition);       
        int8_t jp_hl();

        int8_t jr_n();
        int8_t jr_cc_nn(Condition condition);

        int8_t call_nn();
        int8_t call_cc_nn(Condition condition);

        int8_t rst(uint8_t n);

        int8_t ret();
        int8_t ret_cc(Condition condition);
        int8_t reti();
};