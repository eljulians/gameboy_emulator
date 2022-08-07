#include "cpu.hpp"

CPU::CPU() {
    AF = new RegisterPair(A, F);
    BC = new RegisterPair(B, C);
    DE = new RegisterPair(D, E);
    HL = new RegisterPair(H, L);
    flags = new Flag(F);
}