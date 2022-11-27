#include <iostream>
#include "cpu.hpp"
#include "registers.hpp"
#include "control_unit.hpp"
#include "../gameboy.hpp"

CPU::CPU(GameBoy& gameBoy) : gameBoy(gameBoy), controlUnit(*this) {
    A = Register_8bit();
    B = Register_8bit();
    C = Register_8bit();
    D = Register_8bit();
    E = Register_8bit();
    F = Register_8bit();
    H = Register_8bit();
    L = Register_8bit();
    AF = new RegisterPair(gameBoy.mmu, A, F);
    BC = new RegisterPair(gameBoy.mmu,B, C);
    DE = new RegisterPair(gameBoy.mmu,D, E);
    HL = new RegisterPair(gameBoy.mmu,H, L);
    flags = new Flag(F);

    AF->set(0x1180);
    BC->set(0x0000);
    DE->set(0xFF56);
    HL->set(0x000D);
    PC.set(0x0000);
    SP.set(0xFFFE);
    
    loads8bit = new Loads8bit(*this, gameBoy.mmu, (*HL));
    alu8bit = new ALU_8bit(*this, A, *HL, *flags);
    alu16bit = new ALU_16bit(*this, *HL, SP, *flags);
    jumps = new Jumps(*this);
    bit = new Bit(*this);
    rotates = new Rotates(*this);
}

void CPU::setPC(uint16_t pc) {
    PC.set(pc);
}

uint16_t CPU::getPC() {
    return PC.get();
}


void CPU::setSP(uint16_t sp) {
    SP.set(sp);
}

uint16_t CPU::getSP() {
    return SP.get();
}

Flag* CPU::getFlags() {
    return flags;
}

void CPU::incrementPC() {
    PC.set(getPC() + 1);
}

uint8_t CPU::fetchByte() {
    uint8_t value = gameBoy.mmu.read_8bit(getPC());
    incrementPC();

    return value;
}

int8_t CPU::fetchSignedByte() {
    return static_cast<int8_t>(fetchByte());
}

uint16_t CPU::fetch2bytes() {
    uint8_t highByte = fetchByte();
    uint8_t lowByte = fetchByte();

    return ((lowByte << 8) | highByte);
}

void CPU::push_onto_stack(uint8_t value) {
    SP.decrement();
    gameBoy.mmu.write_8bit(SP.get(), value);
}

void CPU::push_address_onto_stack(uint16_t address) {
    push_onto_stack(address >> 8); 
    push_onto_stack(address & 0xFF); 
}

uint8_t CPU::pop_from_stack() {
    uint8_t value = gameBoy.mmu.read_8bit(SP.get());
    SP.increment();

    return value;
}

uint16_t CPU::pop_address_from_stack() {
    uint8_t lowByte = pop_from_stack();
    uint8_t highByte = pop_from_stack();

    return ((highByte << 8) | lowByte);
}

bool CPU::getCondition(Condition condition) {
    switch(condition) {
        case Condition::Z:
            return flags->get_z();
        case Condition::NZ:
            return !flags->get_z();
        case Condition::C:
            return flags->get_c();
        case Condition::NC:
            return !flags->get_c();
    }
}

void CPU::enableInterrupts() {
    interruptEnabled = true;
}

void CPU::disableInterrupts() {
    interruptEnabled = false;
}

bool CPU::areInterruptsEnabled() {
    return interruptEnabled;
}
