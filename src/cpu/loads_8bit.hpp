#pragma once

#include <stdint.h>
#include "registers.hpp"
#include "../mmu/mmu.hpp"

class CPU;

class Loads8bit {
    private:
        CPU& cpu;
        MMU& mmu;
        RegisterPair& hl;

    public:
        Loads8bit(CPU& cpu, MMU& mmu, RegisterPair& hl) : cpu(cpu), mmu(mmu), hl(hl) {};
        uint8_t load_r8_n8(Register_8bit& register_);
        uint8_t load_r8_r8(Register_8bit& to, Register_8bit& from);
        uint8_t load_r8_hl(Register_8bit& to);

        void load_a_r8(Register_8bit& register_);
        void load_a_r16(RegisterPair& register_);
        void load_a_n8();
        int8_t load_a_address();

        void load_r8_a(Register_8bit& register_);
        void load_r16_a(RegisterPair& register_);
        int8_t load_a16_a();

        void load_a_c();
        void load_c_a();

        void ld_a_hl_decrement();
        void ld_hl_a_decrement();
        void ld_a_hl_increment();
        void ld_hl_a_increment();

        int8_t ldh_n_a();
        int8_t ldh_a_n();

        void ld_r16_n16(RegisterPair register_);

        int8_t ld_sp_hl();
        int8_t ld_hl_sp_n();
        void ld_n16_sp();

        uint8_t push_r16(RegisterPair register_); 
        uint8_t pop_r16(RegisterPair register_); 

        int8_t ld_c_a();
        int8_t ld_a_c();
};