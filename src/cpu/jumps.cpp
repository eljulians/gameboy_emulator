#include <stdint.h>
#include "registers.hpp"
#include "cpu.hpp"
#include "jumps.hpp"


void Jumps::jp_nn() {
    cpu.PC.set(cpu.fetch2bytes());
}

void Jumps::jp_cc_nn(Condition condition) {
    if (cpu.getCondition(condition)) {
        jp_nn();
    }
}

void Jumps::jp_hl() {
    cpu.PC.set(cpu.HL->get());
}

void Jumps::jr_n() {
    uint16_t result = static_cast<uint16_t>(cpu.PC.get() + cpu.fetchSignedByte());
    cpu.PC.set(result);
}

void Jumps::jr_cc_nn(Condition condition) {
    if (cpu.getCondition(condition)) {
        jr_n();
    }
}

void Jumps::call_nn() {
    uint16_t jumpAddress = cpu.fetch2bytes();

    cpu.push_address_onto_stack(cpu.PC.get());
    cpu.PC.set(jumpAddress);
}

void Jumps::call_cc_nn(Condition condition) {
    if (cpu.getCondition(condition)) {
        call_nn();
    }
}

void Jumps::rst(uint8_t n) {
    cpu.push_address_onto_stack(cpu.PC.get());
    cpu.PC.set(n);
}

void Jumps::ret() {
    cpu.PC.set(cpu.pop_address_from_stack());    
}

void Jumps::ret_cc(Condition condition) {
    if (cpu.getCondition(condition)) {
        ret();
    }
}

void Jumps::reti() {

}