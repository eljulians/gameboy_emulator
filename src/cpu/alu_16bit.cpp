#include <stdint.h>
#include "registers.hpp"
#include "cpu.hpp"
#include "alu_16bit.hpp"

void ALU_16bit::setAdditionFlags(uint16_t a, uint16_t b) {
    flags.set_z(((a + b) & 0xFFFF) == 0);
    flags.set_n(0);
    flags.set_h((a & 0xFFF) + (b & 0xFFF) > 0xFFF);
    flags.set_c((a + b) > 0xFFFF);
}

void ALU_16bit::setSubtractionFlags(uint16_t a, uint16_t b) {

}

void ALU_16bit::add_hl_r16(RegisterPair register_) {
    uint16_t result = hl.get() + register_.get();

    setAdditionFlags(hl.get(), register_.get());
    hl.set(result);
}

void ALU_16bit::add_hl_sp(Register_16bit sp) {
    uint16_t result = hl.get() + sp.get();

    setAdditionFlags(hl.get(), sp.get());
    hl.set(result);
}

void ALU_16bit::add_sp_s8() {
    int8_t value = cpu.fetchSignedByte();
    uint16_t result = cpu.getSP() + value;

    flags.set_z(0);
    flags.set_n(0);
    flags.set_h(((cpu.getSP() ^ value ^ (result & 0xFFFF)) & 0x10) == 0x10);
    flags.set_c(((cpu.getSP() ^ value ^ (result & 0xFFFF)) & 0x100) == 0x100);

    cpu.setSP(result);
}

void ALU_16bit::inc_r16(RegisterPair register_) {
    register_.increment();
}

void ALU_16bit::inc_sp(Register_16bit sp) {
    sp.increment();
}

void ALU_16bit::dec_r16(RegisterPair register_) {
    register_.decrement();
}

void ALU_16bit::dec_sp(Register_16bit sp) {
    sp.decrement(); 
}