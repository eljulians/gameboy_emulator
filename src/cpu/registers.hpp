#pragma once

#include <stdint.h>
#include "../mmu/mmu.hpp"

class Register_8bit {
    private:
        uint8_t value;

    public:
        uint8_t get();
        void set(uint8_t value);
        void increment();
        void decrement();
};

class Register_16bit {
    private:
        uint16_t value;
    
    public:
        void set(uint16_t newValue);
        uint16_t get();
        void increment();
        void decrement();
};

class RegisterPair {
    private:
        MMU& mmu;
        Register_8bit &high;
        Register_8bit &low;

    public:
        RegisterPair(MMU& mmu, Register_8bit &highAddr, Register_8bit &lowAddr) : mmu(mmu), high(highAddr), low(lowAddr) {};
        void set(uint16_t newValue);
        uint16_t get();
        void increment();
        void decrement(); 
        uint8_t getAddressValue();
        void setAddressValue(uint8_t value);
};

class Flag {
    private:
        Register_8bit &flag;

    public:
        Flag(Register_8bit &flagAddress) : flag(flagAddress) {};
        bool get_z();
        bool get_n();
        bool get_h();
        bool get_c();
        void set_z(bool newFlag);
        void set_n(bool newFlag);
        void set_h(bool newFlag);
        void set_c(bool newFlag);
};