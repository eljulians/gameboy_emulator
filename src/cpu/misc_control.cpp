#include "misc_control.hpp"
#include "cpu.hpp"


int MiscControl::nop() {
    return 4;
}

int MiscControl::stop() {
    // 2-byte opcode whose second byte is ignored...
    return 4;
}

int MiscControl::halt() {
    if (cpu.areInterruptsEnabled()) {
        cpu.halted = true;
    }

    return 4;
}

int MiscControl::di() {
    cpu.disableInterrupts();

    return 4;
}

int MiscControl::ei() {
    cpu.enableInterrupts();

    return 4;
}