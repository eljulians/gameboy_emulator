#pragma once

#include <stdint.h>
#include "registers.hpp"

class CPU;

class Rotates {
    private:
        CPU& cpu;

    public:
        Rotates(CPU& cpu) : cpu(cpu) {};
        void rlca();
        void rla();

        void rrca();
        void rra();
};