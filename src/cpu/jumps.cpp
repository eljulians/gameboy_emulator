#include <stdint.h>
#include "registers.hpp"
#include "cpu.hpp"
#include "jumps.hpp"


void Jumps::jp_nn() {
    cpu.PC.set(cpu.fetch2bytes());
}

void Jumps::jp_cc_nn() {

}

void Jumps::jp_hl() {
    cpu.PC.set(cpu.HL->get());
}

void Jumps::jr_n() {
    uint16_t result = static_cast<uint16_t>(cpu.PC.get() + cpu.fetchSignedByte());
    cpu.PC.set(result);
}

void Jumps::jr_cc_nn() {

}

void Jumps::call_nn() {
    uint16_t jumpAddress = cpu.fetch2bytes();

    cpu.push_address_onto_stack(cpu.PC.get());
    cpu.PC.set(jumpAddress);
}

void Jumps::call_cc_nn() {

}

void Jumps::rst(uint8_t n) {

}

void Jumps::ret() {

}

void Jumps::ret_cc() {

}

void Jumps::reti() {

}