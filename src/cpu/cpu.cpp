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
    AF = new RegisterPair(A, F);
    BC = new RegisterPair(B, C);
    DE = new RegisterPair(D, E);
    HL = new RegisterPair(H, L);
    flags = new Flag(F);
}