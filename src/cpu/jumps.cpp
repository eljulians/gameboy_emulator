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
    uint16_t nextInstructionAddress = cpu.PC.get() + 2;

    cpu.push_onto_stack(static_cast<uint8_t>(nextInstructionAddress & 0xFF));
    cpu.push_onto_stack(static_cast<uint8_t>(nextInstructionAddress >> 8));
    cpu.PC.set(cpu.fetch2bytes());
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