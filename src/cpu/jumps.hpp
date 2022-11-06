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

        void jp_nn();
        void jp_cc_nn(Condition condition);       
        void jp_hl();

        void jr_n();
        void jr_cc_nn(Condition condition);

        void call_nn();
        void call_cc_nn(Condition condition);

        void rst(uint8_t n);

        void ret();
        void ret_cc(Condition condition);
        void reti();
};