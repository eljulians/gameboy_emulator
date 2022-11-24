#include <stdint.h>
#include "registers.hpp"
#include "cpu.hpp"
#include "rotates.hpp"


uint8_t Rotates::rotateLeft(uint8_t value, bool carry) {
    bool c = value & 0x80;

    uint8_t result = ((value << 1) + carry) & 0xFF;

    cpu.flags->set_z(result == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(0);
    cpu.flags->set_c(c);

    return result;
}

uint8_t Rotates::rotateRight(uint8_t value, bool carry) {
    bool c = value & 0x01;

    uint8_t result = ((value >> 1) + (carry << 7)) & 0xFF;

    cpu.flags->set_z(result == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(0);
    cpu.flags->set_c(c);

    return result;
}

int8_t Rotates::rlca() {
    cpu.A.set(rotateLeft(cpu.A.get(), cpu.A.get() & 0x80));

    return 4;
}

int8_t Rotates::rla() {
    cpu.A.set(rotateLeft(cpu.A.get(), cpu.flags->get_c()));

    return 4;
}

int8_t Rotates::rrca() {
    cpu.A.set(rotateRight(cpu.A.get(), cpu.A.get() & 0x01));

    return 4;
}

int8_t Rotates::rra() {
    cpu.A.set(rotateRight(cpu.A.get(), cpu.flags->get_c()));
    
    return 4;
}

void Rotates::rlc_r8(Register_8bit& register_) {
    register_.set(rotateLeft(register_.get(), register_.get() & 0x80));
}

void Rotates::rlc_hl() {
    cpu.HL->setAddressValue(rotateLeft(cpu.HL->getAddressValue(), cpu.HL->getAddressValue() & 0x80));
}

void Rotates::rl_r8(Register_8bit& register_) {
    register_.set(rotateLeft(register_.get(), cpu.flags->get_c()));
}

void Rotates::rl_hl() {
    cpu.HL->setAddressValue(rotateLeft(cpu.HL->getAddressValue(), cpu.flags->get_c()));
}

void Rotates::rrc_r8(Register_8bit& register_) {
    register_.set(rotateRight(register_.get(), register_.get() & 0x01));
}

void Rotates::rrc_hl() {
    cpu.HL->setAddressValue(rotateRight(cpu.HL->getAddressValue(), cpu.HL->getAddressValue() & 0x01));
}

void Rotates::rr_r8(Register_8bit& register_) {
    register_.set(rotateRight(register_.get(), cpu.flags->get_c()));
}

void Rotates::sla_r8(Register_8bit& register_) {
    register_.set(rotateLeft(register_.get(), 0));
}

void Rotates::sla_hl() {
    cpu.HL->setAddressValue(rotateLeft(cpu.HL->getAddressValue(), 0));
}

void Rotates::sra_r8(Register_8bit& register_) {
    uint8_t value = register_.get();
    bool c = value & 0x01;
    bool msc = value & 0x80;

    uint8_t result = ((value >> 1) & 0xFF) + (msc << 7);

    cpu.flags->set_z(result == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(0);
    cpu.flags->set_c(c);

    register_.set(result);
}

void Rotates::sra_hl() {
    uint8_t value = cpu.HL->getAddressValue();
    bool c = value & 0x01;
    bool msc = value & 0x80;

    uint8_t result = ((value >> 1) & 0xFF) + (msc << 7);

    cpu.flags->set_z(result == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(0);
    cpu.flags->set_c(c);

    cpu.HL->setAddressValue(result);
}

void Rotates::srl_r8(Register_8bit& register_) {
    register_.set(rotateRight(register_.get(), 0));
}

void Rotates::srl_hl() {
    cpu.HL->setAddressValue(rotateRight(cpu.HL->getAddressValue(), 0));
}