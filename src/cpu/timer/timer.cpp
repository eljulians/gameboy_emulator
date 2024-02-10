#include "timer.hpp"
#include "../../mmu/mmu.hpp"
#include "../cpu.hpp"



INPUT_CLOCK_HZ TimerControl::getInputClockSelect() {
    int mask = 0b11;
    auto value = mmu.read_8bit(TIMER_CONTROL_ADDRESS);

    return INPUT_CLOCK_SELECT_HZ_MAP.at(value & mask);
}

bool TimerControl::isEnabled() {
    int mask = 0b100;

    return mmu.read_8bit(TIMER_CONTROL_ADDRESS) && mask;
}