#include <stdint.h>
#include "registers.hpp"
#include "cpu.hpp"
#include "rotates.hpp"

void Rotates::rlca() {
    bool c = cpu.A.get() & 0x80;

    uint8_t result = (cpu.A.get() << 1) & 0xFF;
    cpu.A.set(result);

    cpu.flags->set_z(cpu.A.get() == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(0);
    cpu.flags->set_c(c);
}

void Rotates::rla() {
    bool c = cpu.A.get() & 0x80;

    uint8_t result = ((cpu.A.get() << 1) + cpu.flags->get_c()) & 0xFF;
    cpu.A.set(result);

    cpu.flags->set_z(cpu.A.get() == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(0);
    cpu.flags->set_c(c);
}

void Rotates::rrca() {
    bool c = cpu.A.get() & 0x01;

    uint8_t result = (cpu.A.get() >> 1) & 0xFF;
    cpu.A.set(result);

    cpu.flags->set_z(cpu.A.get() == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(0);
    cpu.flags->set_c(c);
}

void Rotates::rra() {
    bool c = cpu.A.get() & 0x01;

    uint8_t result = ((cpu.A.get() >> 1) + (cpu.flags->get_c() << 7)) & 0xFF;
    cpu.A.set(result);

    cpu.flags->set_z(cpu.A.get() == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(0);
    cpu.flags->set_c(c);
}