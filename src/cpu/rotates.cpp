#include <stdint.h>
#include "registers.hpp"
#include "cpu.hpp"
#include "rotates.hpp"


void Rotates::rotateLeft(Register_8bit& register_, bool carry) {
    bool c = register_.get() & 0x80;

    uint8_t result = ((register_.get() << 1) + carry) & 0xFF;
    register_.set(result);

    cpu.flags->set_z(register_.get() == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(0);
    cpu.flags->set_c(c);
}

void Rotates::rotateRight(Register_8bit& register_, bool carry) {
    bool c = register_.get() & 0x01;

    uint8_t result = ((register_.get() >> 1) + (carry << 7)) & 0xFF;
    register_.set(result);

    cpu.flags->set_z(register_.get() == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(0);
    cpu.flags->set_c(c);
}

void Rotates::rlca() {
    rotateLeft(cpu.A, 0);
}

void Rotates::rla() {
    rotateLeft(cpu.A, cpu.flags->get_c());
}

void Rotates::rrca() {
    rotateRight(cpu.A, 0);
}

void Rotates::rra() {
    rotateRight(cpu.A, cpu.flags->get_c());
}

void Rotates::rlc_r8(Register_8bit& register_) {
    rotateLeft(register_, 0);
}

void Rotates::rlc_hl() {

}

void Rotates::rl_r8(Register_8bit& register_) {

}

void Rotates::rl_hl() {

}