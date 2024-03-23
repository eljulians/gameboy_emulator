#include <iostream>
#include "misc_control.hpp"
#include "../cpu.hpp"


int MiscControl::nop() {
    return 4;
}

int MiscControl::stop() {
    // 2-byte opcode whose second byte is ignored...
    return 4;
}

int MiscControl::halt() {
    bool haltBug = false;
    if (!cpu.areInterruptsEnabled()) {
        bool haltBug = true;
        for (Interrupt interrupt: cpu.interruptManager->getInterrupts()) {
            haltBug &= (interrupt.isFlagged() & interrupt.isFlagged() == 0);
        }
    }

    if (!haltBug) {
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