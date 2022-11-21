#include <stdexcept>
#include <stdint.h>
#include "registers.hpp"
#include "cpu.hpp"
#include "jumps.hpp"


int8_t Jumps::jp_nn() {
    cpu.PC.set(cpu.fetch2bytes());

    return 12;
}

int8_t Jumps::jp_cc_nn(Condition condition) {
    if (cpu.getCondition(condition)) {
        jp_nn();
    }

    return 12;
}

int8_t Jumps::jp_hl() {
    cpu.PC.set(cpu.HL->get());

    return 4;
}

int8_t Jumps::jr_n() {
    int8_t offset = cpu.fetchSignedByte(); 
    uint16_t result = static_cast<uint16_t>(cpu.PC.get() + offset);
    cpu.PC.set(result);

    return 8;
}

int8_t Jumps::jr_cc_nn(Condition condition) {
    if (cpu.getCondition(condition)) {
        jr_n();
    }

    return 12;
}

int8_t Jumps::call_nn() {
    uint16_t jumpAddress = cpu.fetch2bytes();

    cpu.push_address_onto_stack(cpu.PC.get());
    cpu.PC.set(jumpAddress);

    return 12;
}

int8_t Jumps::call_cc_nn(Condition condition) {
    if (cpu.getCondition(condition)) {
        call_nn();
    }

    return 12;
}

int8_t Jumps::rst(uint8_t n) {
    cpu.push_address_onto_stack(cpu.PC.get());
    cpu.PC.set(n);

    return 32;
}

int8_t Jumps::ret() {
    cpu.PC.set(cpu.pop_address_from_stack());    

    return 8;
}

int8_t Jumps::ret_cc(Condition condition) {
    if (cpu.getCondition(condition)) {
        ret();
    }

    return 8;
}

int8_t Jumps::reti() {
    throw std::runtime_error("Operation RETI implemented");

    return 8;
}
