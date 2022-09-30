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

    setAdditionFlags(a.get(), pcValue);
    a.set(result);
}

void ALU_8bit::adc_a_r8(Register_8bit &register_) {
    uint8_t result = a.get() + register_.get() + flags.get_c();

    setAdditionFlags(a.get(), register_.get() + flags.get_c());
    a.set(result);
}

void ALU_8bit::adc_a_hl() {
    uint8_t result = a.get() + hl.getAddressValue() + flags.get_c();

    setAdditionFlags(a.get(), hl.getAddressValue() + flags.get_c());
    a.set(result);
}

void ALU_8bit::adc_a_n8() {
    uint8_t pcValue = cpu.fetchByte();
    uint8_t result = a.get() + pcValue + flags.get_c();

    setAdditionFlags(a.get(), pcValue + flags.get_c());
    a.set(result);
}

void ALU_8bit::setAdditionFlags(uint8_t a, uint8_t b) {
    flags.set_z(((a + b) & 0xFF) == 0x00);
    flags.set_n(0);
    flags.set_h((((a & 0xF) + (b & 0xF)) & 0x10) == 0x10);
    flags.set_c(b > 0xFF - a);
}


int8_t ALU_8bit::sub_a_r8(Register_8bit &register_) {
    uint8_t result = static_cast<uint8_t>(a.get () - register_.get());

    setSubtractionFlags(a.get(), register_.get());
    a.set(result);

    return 4;
}

int8_t ALU_8bit::sub_a_hl(Register_8bit &register_) {
    return 8;
}

int8_t ALU_8bit::sub_a_n8(Register_8bit &register_) {
    return 8;
}

void ALU_8bit::setSubtractionFlags(uint8_t a, uint8_t b) {
    flags.set_z(((a - b) & 0xFF) == 0x00);
    flags.set_n(1);
    flags.set_h((a & 0x0F) - (b & 0x0F) < 0);
    flags.set_c(b > a);
}