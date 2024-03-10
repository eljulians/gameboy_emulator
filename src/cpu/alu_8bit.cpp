#include <iostream>
#include "alu_8bit.hpp"
#include "registers.hpp"
#include "cpu.hpp"


int8_t ALU_8bit::add_a_r8(Register_8bit &register_) {
    uint8_t result = a.get() + register_.get();

    setAdditionFlags(a.get(), register_.get(), 0);
    a.set(result);

    return 4;
}

int8_t ALU_8bit::add_a_hl() {
    uint8_t result = a.get() + hl.getAddressValue();

    setAdditionFlags(a.get(), hl.getAddressValue(), 0);
    a.set(result);

    return 8;
}

int8_t ALU_8bit::add_a_n8() {
    uint8_t pcValue = cpu.fetchByte();
    uint8_t result = a.get() + pcValue;

    setAdditionFlags(a.get(), pcValue, 0);
    a.set(result);

    return 8;
}

int8_t ALU_8bit::adc_a_r8(Register_8bit &register_) {
    uint8_t result = a.get() + register_.get() + flags.get_c();

    setAdditionFlags(a.get(), register_.get(), flags.get_c());
    a.set(result);

    return 4;
}

int8_t ALU_8bit::adc_a_hl() {
    uint8_t result = a.get() + hl.getAddressValue() + flags.get_c();

    setAdditionFlags(a.get(), hl.getAddressValue(), flags.get_c());
    a.set(result);

    return 8;
}

int8_t ALU_8bit::adc_a_n8() {
    uint8_t pcValue = cpu.fetchByte();
    uint8_t result = a.get() + pcValue + flags.get_c();

    setAdditionFlags(a.get(), pcValue, flags.get_c());
    a.set(result);

    return 8;
}



int8_t ALU_8bit::sub_a_r8(Register_8bit &register_) {
    uint8_t result = static_cast<uint8_t>(a.get () - register_.get());

    setSubtractionFlags(a.get(), register_.get(), 0);
    a.set(result);

    return 4;
}

int8_t ALU_8bit::sub_a_hl() {
    uint8_t result = static_cast<uint8_t>(a.get() - hl.getAddressValue());

    setSubtractionFlags(a.get(), hl.getAddressValue(), 0);
    a.set(result);

    return 8;
}

int8_t ALU_8bit::sub_a_n8() {
    uint8_t pcValue = cpu.fetchByte();
    uint8_t result = static_cast<uint8_t>(a.get() - pcValue);

    setSubtractionFlags(a.get(), pcValue, 0);
    a.set(result);

    return 8;
}


int8_t ALU_8bit::sbc_a_r8(Register_8bit &register_) {
    uint8_t result = static_cast<uint8_t>(a.get () - register_.get() - flags.get_c());

    setSubtractionFlags(a.get(), register_.get(), flags.get_c());
    a.set(result);

    return 4;
}

int8_t ALU_8bit::sbc_a_hl() {
    uint8_t result = static_cast<uint8_t>(a.get() - hl.getAddressValue() - flags.get_c());

    setSubtractionFlags(a.get(), hl.getAddressValue(), flags.get_c());
    a.set(result);

    return 8;
}

int8_t ALU_8bit::sbc_a_n8() {
    uint8_t pcValue = cpu.fetchByte();
    uint8_t result = static_cast<uint8_t>(a.get() - pcValue - flags.get_c());

    setSubtractionFlags(a.get(), pcValue, flags.get_c());
    a.set(result);

    return 8;
}

int8_t ALU_8bit::and_a_r8(Register_8bit &register_) {
    a.set(a.get() & register_.get());

    flags.set_z(a.get() == 0x00);
    flags.set_n(0);
    flags.set_h(1);
    flags.set_c(0);

    return 4;
}


int8_t ALU_8bit::and_a_hl() {
    a.set(a.get() & hl.getAddressValue());

    flags.set_z(a.get() == 0x00);
    flags.set_n(0);
    flags.set_h(1);
    flags.set_c(0);

    return 8;
}

int8_t ALU_8bit::and_a_n8() {
    a.set(a.get() & cpu.fetchByte());

    flags.set_z(a.get() == 0x00);
    flags.set_n(0);
    flags.set_h(1);
    flags.set_c(0);

    return 8;
}


void ALU_8bit::setAdditionFlags(uint8_t a, uint8_t b, bool carry) {
    uint8_t sum = a + b + carry;
    int noCarrySum = a ^ b;
    int carryInto = sum ^ noCarrySum;

    // here
    flags.set_z(sum == 0x00);
    flags.set_n(0);
    //flags.set_h((((a & 0xF) + (b & 0xF) + carry) & 0x10) == 0x10);
    flags.set_h(carryInto & 0x10);
    flags.set_c(b > (0xFF - a - carry));
}

void ALU_8bit::setSubtractionFlags(uint8_t a, uint8_t b, bool carry) {
    uint8_t result = a - b - carry;
    flags.set_z(result == 0x00);
    flags.set_n(1);
    flags.set_h((a & 0x0F) - (b & 0x0F) - carry < 0);
    flags.set_c(b > (a - carry));
}

int8_t ALU_8bit::or_a_r8(Register_8bit &register_) {
    a.set(a.get() | register_.get());

    flags.set_z(a.get() == 0x00);
    flags.set_n(0);
    flags.set_h(0);
    flags.set_c(0);

    return 4;
}

int8_t ALU_8bit::or_a_hl() {
    a.set(a.get() | hl.getAddressValue());

    flags.set_z(a.get() == 0x00);
    flags.set_n(0);
    flags.set_h(0);
    flags.set_c(0);

    return 8;
}

int8_t ALU_8bit::or_a_n8() {
    a.set(a.get() | cpu.fetchByte());

    flags.set_z(a.get() == 0x00);
    flags.set_n(0);
    flags.set_h(0);
    flags.set_c(0);

    return 8;
}

int8_t ALU_8bit::xor_a_r8(Register_8bit &register_) {
    a.set(a.get() ^ register_.get());

    flags.set_z(a.get() == 0x00);
    flags.set_n(0);
    flags.set_h(0);
    flags.set_c(0);

    return 4;
}
int8_t ALU_8bit::xor_a_hl() {
    a.set(a.get() ^ hl.getAddressValue());

    flags.set_z(a.get() == 0x00);
    flags.set_n(0);
    flags.set_h(0);
    flags.set_c(0);

    return 8;
}
int8_t ALU_8bit::xor_a_n8() {
    a.set(a.get() ^ cpu.fetchByte());

    flags.set_z(a.get() == 0x00);
    flags.set_n(0);
    flags.set_h(0);
    flags.set_c(0);

    return 8;
}

int8_t ALU_8bit::cp_a_r8(Register_8bit &register_) {
    uint8_t result = static_cast<uint8_t>(a.get () - register_.get());

    setSubtractionFlags(a.get(), register_.get(), 0);

    return 4;
}

int8_t ALU_8bit::cp_a_hl() {
    uint8_t result = static_cast<uint8_t>(a.get() - hl.getAddressValue());

    setSubtractionFlags(a.get(), hl.getAddressValue(), 0);

    return 8;
}

int8_t ALU_8bit::cp_a_n8() {
    uint8_t pcValue = cpu.fetchByte();
    uint8_t result = static_cast<uint8_t>(a.get() - pcValue);

    setSubtractionFlags(a.get(), pcValue, 0);

    return 8;
}


int8_t ALU_8bit::inc_r8(Register_8bit &register_) {
    uint8_t result = register_.get() + 0x01;
    bool original_c = flags.get_c();

    setAdditionFlags(register_.get(), 0x01, 0);
    flags.set_c(original_c);
    register_.set(result);

    return 4;
}

int8_t ALU_8bit::inc_hl() {
    uint8_t result = hl.getAddressValue() + 0x01;
    bool original_c = flags.get_c();

    setAdditionFlags(hl.getAddressValue(), 0x01, 0);
    flags.set_c(original_c);
    hl.setAddressValue(result);

    return 12;
}


int8_t ALU_8bit::dec_r8(Register_8bit &register_) {
    uint8_t result = static_cast<uint8_t>(register_.get() - 0x01);
    bool original_c = flags.get_c();

    setSubtractionFlags(register_.get(), 0x01, 0);
    flags.set_c(original_c);
    register_.set(result);

    return 4;
}

int8_t ALU_8bit::dec_hl() {
    uint8_t result = hl.getAddressValue() - 0x01;
    bool original_c = flags.get_c();

    setSubtractionFlags(hl.getAddressValue(), 0x01, 0);
    flags.set_c(original_c);
    hl.setAddressValue(result);

    return 12;
}
