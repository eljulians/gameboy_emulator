#pragma once


class CPU;

class MiscControl {
    private:
        CPU& cpu;

    public:
        MiscControl(CPU& cpu) : cpu(cpu) {};

        int nop();
        int stop();
        int halt();
        int di();
        int ei(); 
};