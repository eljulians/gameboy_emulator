#include <stdint.h>
#include "registers.hpp"
#include "cpu.hpp"
#include "bit.hpp"

int8_t Bit::bit(Register_8bit register_, uint8_t bit) {
    cpu.flags->set_z(((register_.get() >> bit) & 0x01) == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(1);

    return 8;
}

int8_t Bit::bit_hl(uint8_t bit) {
    cpu.flags->set_z(((cpu.HL->getAddressValue() >> bit) & 0x01) == 0x00);
    cpu.flags->set_n(0);
    cpu.flags->set_h(1);

    return 16;
}

int8_t Bit::set(Register_8bit& register_, uint8_t bit) {
    uint8_t mask = 1 << bit;
    register_.set(register_.get() | mask);

    return 8;
}

int8_t Bit::set_hl(uint8_t bit) {
    uint8_t mask = 1 << bit;
    cpu.HL->setAddressValue(cpu.HL->getAddressValue() | mask);

    return 16;
}

int8_t Bit::res(Register_8bit& register_, uint8_t bit) {
    uint8_t mask = 0xFF ^ (1 << bit);    
    register_.set(register_.get() & mask);

    return 8;
}

int8_t Bit::res_hl(uint8_t bit) {
    uint8_t mask = 0xFF ^ (1 << bit);    
    cpu.HL->setAddressValue(cpu.HL->getAddressValue() & mask);

    return 16;
}