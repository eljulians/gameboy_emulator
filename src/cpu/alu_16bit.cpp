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

int8_t ALU_16bit::add_hl_r16(RegisterPair register_) {
    uint16_t result = hl.get() + register_.get();

    setAdditionFlags(hl.get(), register_.get());
    hl.set(result);

    return 8;
}

int8_t ALU_16bit::add_hl_sp() {
    uint16_t result = hl.get() + cpu.SP.get();

    setAdditionFlags(hl.get(), cpu.SP.get());
    hl.set(result);

    return 8;
}

int8_t ALU_16bit::add_sp_s8() {
    int8_t value = cpu.fetchSignedByte();
    int result = static_cast<int>(cpu.getSP() + value);

    flags.set_z(0);
    flags.set_n(0);
    flags.set_h(((cpu.getSP() ^ value ^ (result & 0xFFFF)) & 0x10) == 0x10);
    flags.set_c(((cpu.getSP() ^ value ^ (result & 0xFFFF)) & 0x100) == 0x100);

    cpu.setSP(static_cast<uint16_t>(result));

    return 16;
}

int8_t ALU_16bit::inc_r16(RegisterPair register_) {
    register_.increment();

    return 8;
}

int8_t ALU_16bit::inc_sp() {
    cpu.SP.increment();

    return 8;
}

int8_t ALU_16bit::dec_r16(RegisterPair register_) {
    register_.decrement();

    return 8;
}

int8_t ALU_16bit::dec_sp() {
    cpu.SP.decrement(); 

    return 8;
}