#define FMT_HEADER_ONLY

#include "spdlog/spdlog.h"

#include "timer.hpp"
#include "../../mmu/mmu.hpp"
#include "../cpu.hpp"



INPUT_CLOCK_HZ TimerControl::getInputClockSelect() {
    int mask = 0b11;
    auto value = mmu.read_8bit(TIMER_CONTROL_ADDRESS) & mask;
    auto clock = INPUT_CLOCK_SELECT_CYCLES_MAP.at(value);

    spdlog::info("TAC: {} cycles (mode: {})", clock, value);

    return clock;
}

bool TimerControl::isEnabled() {
    int mask = 0b100;

    auto isEnabled = mmu.read_8bit(TIMER_CONTROL_ADDRESS) && mask;
    spdlog::info("TAC enabled: {}", isEnabled);

    return isEnabled;
}

int TimerModulo::getValue() {
    auto value = mmu.read_8bit(TIMER_MODULO_ADDRESS);
    spdlog::info("TMA: 0x{0:x}", value);

    return value;
}

void TimerCounter::tick(int cycles) {
    // TODO: request interrupt on the next tick after overflow?
    auto clockSelect = timerControl.getInputClockSelect();
    auto counterValue = mmu.read_8bit(TIMER_COUNTER_ADDRESS);

    spdlog::info("TIMA: current cycles: {}", currentCycles);
    spdlog::info("TIMA: increasing cycles by {}", cycles);
    spdlog::info("TIMA: 0x{0:x}", counterValue);

    currentCycles += cycles;

    if (currentCycles >= clockSelect) {
        spdlog::info("TIMA: incrementing");

        counterValue += 1;
        currentCycles = currentCycles - clockSelect;
        mmu.write_8bit(TIMER_COUNTER_ADDRESS, counterValue & 0xFF);
    }

    if (counterValue > 0xFF) {
        spdlog::info("TIMA: overflow, resetting value to TMA and requesting interrupt");

        auto timerModuloValue = timerModulo.getValue();
        mmu.write_8bit(TIMER_COUNTER_ADDRESS, timerModuloValue);
        interrupt.flag();
    }
}

void Divider::tick(int cycles) {
    // TODO: every t-cycle or m-cycle (4 t-cycles)????
    spdlog::info("DIV: internal: 0x{0:x}", internalDivider);
    spdlog::info("DIV: cycles: {}", cycles);

    internalDivider += cycles;

    if (internalDivider > 0xFFFF) {
        internalDivider -= 0xFFFF;
        spdlog::info("DIV: overflow");
    }

    spdlog::info("DIV: new value: 0x{0:X}", internalDivider);

    int upperByte = internalDivider >> 8;

    // Direct write; hardware resets DIV to 0 on other writes
    mmu.io.at(DIVIDER_ADDRESS - IO_START) = upperByte;
}

void TimerManager::tick(int cycles) {
    divider.tick(cycles);
    timerCounter.tick(cycles);
    
}