#pragma once

#include <stdint.h>
#include "registers.hpp"

class CPU;

class Jumps {
    private:
        CPU& cpu;

    public:
        Jumps(CPU& cpu) : cpu(cpu) {};

        void jp_nn();
        void jp_cc_nn();       
        void jp_hl();

        void jr_n();
        void jr_cc_nn();

        void call_nn();
        void call_cc_nn();

        void rst(uint8_t n);

        void ret();
        void ret_cc();
        void reti();
};