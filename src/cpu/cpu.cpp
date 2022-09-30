#include <iostream>
#include "cpu.hpp"
#include "registers.hpp"
#include "../gameboy.hpp"

CPU::CPU(GameBoy& gameBoy) : gameBoy(gameBoy) {
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
    PC.set(0x0100);
    SP.set(0x0000);
}

void CPU::setPC(uint16_t pc) {
    PC.set(pc);
}

uint16_t CPU::getPC() {
    return PC.get();
}

void CPU::incrementPC() {
    PC.set(getPC() + 1);
}

uint8_t CPU::fetchByte() {
    uint8_t value = gameBoy.mmu.read_8bit(getPC());
    incrementPC();

    return value;
}