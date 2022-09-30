#include <iostream>
#include "alu_8bit.hpp"
#include "registers.hpp"
#include "cpu.hpp"


void ALU_8bit::add_a_r8(Register_8bit &register_) {
    uint8_t result = a.get() + register_.get();

    setAdditionFlags(a.get(), register_.get());
    a.set(result);
}

void ALU_8bit::add_a_hl() {
    uint8_t result = a.get() + hl.getAddressValue();

    setAdditionFlags(a.get(), hl.getAddressValue());
    a.set(result);
}

void ALU_8bit::add_a_n8() {
    uint8_t pcValue = cpu.fetchByte();
    uint8_t result = a.get() + pcValue;

    std::cout << "AAAAAAAAAAAAAA";
    std::cout << pcValue;
    setAdditionFlags(a.get(), pcValue);
    a.set(result);
}

void ALU_8bit::adc_a_r8(Register_8bit &register_) {
    uint8_t result = a.get() + register_.get() + flags.get_c();

    setAdditionFlags(a.get(), register_.get() + flags.get_c());
    a.set(result);
}

void ALU_8bit::adc_a_hl() {

}

void ALU_8bit::adc_a_n8() {

}

void ALU_8bit::setAdditionFlags(uint8_t a, uint8_t b) {
    flags.set_z(((a + b) & 0xFF) == 0x00);
    flags.set_n(0);
    flags.set_h((((a & 0xF) + (b & 0xF)) & 0x10) == 0x10);
    flags.set_c(b > 0xFF - a);
}