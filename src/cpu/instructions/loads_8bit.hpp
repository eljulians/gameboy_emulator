#pragma once

#include <stdint.h>
#include "../registers.hpp"
#include "../../mmu/mmu.hpp"

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
        uint8_t load_hl_r8(Register_8bit& from);

        int8_t load_a_r16(RegisterPair& register_);
        int8_t load_a_address();

        int8_t load_r16_a(RegisterPair& register_);
        int8_t load_a16_a();

        void load_a_c();
        void load_c_a();

        int load_hl_d8();

        int8_t ld_hl_a_decrement();
        int8_t ld_a_hl_increment();
        int ld_a_hl_decrement();
        int8_t ld_hl_a_increment();

        int8_t ldh_n_a();
        int8_t ldh_a_n();

        int8_t ld_r16_n16(RegisterPair register_);

        int8_t ld_sp_hl();
        int8_t ld_hl_sp_n();
        int8_t ld_n16_sp();
        int8_t ld_sp_n16();

        uint8_t push_r16(RegisterPair register_); 
        uint8_t pop_r16(RegisterPair register_); 
        int pop_af(); 

        int8_t ld_c_a();
        int8_t ld_a_c();
};