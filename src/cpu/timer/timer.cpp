#define FMT_HEADER_ONLY

#include <iostream>
#include "spdlog/spdlog.h"

#include "timer.hpp"
#include "../../mmu/mmu.hpp"
#include "../cpu.hpp"



INPUT_CLOCK_HZ TimerControl::getInputClockSelect() {
    int mask = 0b11;
    auto value = mmu.read_8bit(TIMER_CONTROL_ADDRESS) & mask;
    auto clock = INPUT_CLOCK_SELECT_CYCLES_MAP.at(value);

    spdlog::debug("TAC: {} cycles (mode: {})", clock, value);

    return clock;
}

bool TimerControl::isEnabled() {
    int mask = 0b100;

    auto isEnabled = mmu.read_8bit(TIMER_CONTROL_ADDRESS) && mask;
    spdlog::debug("TAC enabled: {}", isEnabled);

    return isEnabled;
}

int TimerModulo::getValue() {
    auto value = mmu.read_8bit(TIMER_MODULO_ADDRESS);
    spdlog::debug("TMA: 0x{0:x}", value);

    return value;
}

void TimerCounter::tick(int cycles) {
    // TODO: request interrupt on the next tick after overflow?
    if (!timerControl.isEnabled()) {
        spdlog::debug("Timer is disabled");
        return;
    }
    


    auto clockSelect = timerControl.getInputClockSelect();

    uint8_t counterValue = mmu.read_8bit(TIMER_COUNTER_ADDRESS);
    uint8_t previous = counterValue;

    spdlog::debug("TIMA: current cycles: {}", currentCycles);
    spdlog::debug("TIMA: increasing cycles by {}", cycles);
    spdlog::debug("TIMA: 0x{0:x}", counterValue);

    currentCycles += cycles;

    if (currentCycles >= clockSelect) {
        counterValue += 1;
        spdlog::debug("TIMA: incremented to {}", counterValue);

        currentCycles = currentCycles - clockSelect;
        mmu.write_8bit(TIMER_COUNTER_ADDRESS, counterValue & 0xFF);
    }

    bool overflow = (counterValue == 0 && previous != 0);

    if (overflow) {
        spdlog::debug("TIMA: overflow, resetting value to TMA and requesting interrupt");

        auto timerModuloValue = timerModulo.getValue();
        mmu.write_8bit(TIMER_COUNTER_ADDRESS, timerModuloValue);
        interrupt.flag();
    }
}

void Divider::tick(int cycles) {
    // TODO: every t-cycle or m-cycle (4 t-cycles)????
    //spdlog::debug("DIV: internal: 0x{0:x}", internalDivider);
    //spdlog::debug("DIV: cycles: {}", cycles);

    uint8_t divider = mmu.read_8bit(DIVIDER_ADDRESS);
    elapsedCycles += cycles;

    if (elapsedCycles >= (int)(16384/4)) {
        elapsedCycles = elapsedCycles - 16384;
        divider += 1;

        // Direct write; hardware resets DIV to 0 on other writes
        mmu.io.at(DIVIDER_ADDRESS - IO_START) = divider;
    }

    /*
    internalDivider += cycles;

    if (internalDivider > 0xFFFF) {
        internalDivider -= 0xFFFF;
        spdlog::debug("DIV: overflow");
    }

    spdlog::debug("DIV: new value: 0x{0:X}", internalDivider);

    int upperByte = internalDivider >> 8;

    // Direct write; hardware resets DIV to 0 on other writes
    mmu.io.at(DIVIDER_ADDRESS - IO_START) = upperByte;
    */
}

void TimerManager::tick(int cycles) {
    divider.tick(cycles);
    timerCounter.tick(cycles);
}