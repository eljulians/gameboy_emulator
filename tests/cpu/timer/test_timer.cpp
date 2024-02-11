#define CATCH_CONFIG_MAIN
#include <iostream>
#include <stdint.h>

#include "../../../lib/catch.hpp"
#include "../../../src/cpu/registers.hpp"
#include "../../../src/cpu/alu_8bit.hpp"
#include "../../../src/mmu/mmu.hpp"
#include "../../../src/cpu/cpu.hpp"
#include "../../../src/cpu/timer/timer.hpp"
#include "../../../src/gameboy.hpp"
#include "../../../src/interrupts/interrupt_manager.hpp"
#include "../../../src/interrupts/interrupt.hpp"
#include <map>


TEST_CASE("TimerControl::getInputClockSelect") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    MMU mmu = gameBoy.mmu;
    //InterruptManager interruptManager = InterruptManager(mmu, cpu);
    TimerControl timerControl = TimerControl(mmu);

    std::map<int, INPUT_CLOCK_HZ> valueExpectedMap {
        {0xF0, INPUT_CLOCK_SELECT_CYCLES_MAP.at(0b00)},
        {0xF1, INPUT_CLOCK_SELECT_CYCLES_MAP.at(0b01)},
        {0xF2, INPUT_CLOCK_SELECT_CYCLES_MAP.at(0b10)},
        {0xF3, INPUT_CLOCK_SELECT_CYCLES_MAP.at(0b11)},
        {0xF4, INPUT_CLOCK_SELECT_CYCLES_MAP.at(0b00)},
        {0xF5, INPUT_CLOCK_SELECT_CYCLES_MAP.at(0b01)},
        {0xF6, INPUT_CLOCK_SELECT_CYCLES_MAP.at(0b10)},
        {0xF7, INPUT_CLOCK_SELECT_CYCLES_MAP.at(0b11)},
    };

    for (const auto &[timerControlValue, expected]: valueExpectedMap) {
        mmu.write_8bit(TIMER_CONTROL_ADDRESS, timerControlValue);
        REQUIRE(timerControl.getInputClockSelect() == expected);
    }
}

TEST_CASE("TimerControl::isEnabled") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    MMU mmu = gameBoy.mmu;
    //InterruptManager interruptManager = InterruptManager(mmu, cpu);
    TimerControl timerControl = TimerControl(mmu);

    mmu.write_8bit(TIMER_CONTROL_ADDRESS, 0b100);
    REQUIRE(timerControl.isEnabled() == true);

    mmu.write_8bit(TIMER_CONTROL_ADDRESS, 0);
    REQUIRE(!timerControl.isEnabled());
}


TEST_CASE("TimerCounter::tick") {
    GameBoy gameBoy = GameBoy();
    CPU cpu = gameBoy.cpu;
    MMU mmu = gameBoy.mmu;
    InterruptManager interruptManager = InterruptManager(mmu, cpu);
    Interrupt timerInterrupt = interruptManager.timer;
    TimerControl timerControl = TimerControl(mmu);
    TimerModulo timerModulo = TimerModulo(mmu);
    TimerCounter timerCounter = TimerCounter(mmu, timerControl, timerModulo, timerInterrupt);
    int timerModuloValue = 0xAA;

    // Set mode 0 and enabled - 4096Hz
    mmu.write_8bit(TIMER_CONTROL_ADDRESS, 0b100);

    // Set value to TMA that will be set to TIMA on overflow
    mmu.write_8bit(TIMER_MODULO_ADDRESS, timerModuloValue);

    // Initialize to almost overflow
    mmu.write_8bit(TIMER_COUNTER_ADDRESS, 0xFF);

    timerCounter.tick(1022);
    REQUIRE(mmu.read_8bit(TIMER_COUNTER_ADDRESS) == 0xFF);
    REQUIRE(!timerInterrupt.isFlagged());

    timerCounter.tick(1);
    REQUIRE(mmu.read_8bit(TIMER_COUNTER_ADDRESS) == 0xFF);
    REQUIRE(!timerInterrupt.isFlagged());
    
    timerCounter.tick(1);
    REQUIRE(mmu.read_8bit(TIMER_COUNTER_ADDRESS) == timerModulo.getValue());
    REQUIRE(timerInterrupt.isFlagged());
}