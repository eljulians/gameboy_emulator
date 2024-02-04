#include "misc_control.hpp"
#include "cpu.hpp"


int MiscControl::nop() {
    return 4;
}

int MiscControl::stop() {
    // TODO??
    return 4;
}

int MiscControl::halt() {
    // TODO??
    return 4;
}

int MiscControl::di() {
    cpu.disableInterrupts();
}

int MiscControl::ei() {
    cpu.enableInterrupts();
}