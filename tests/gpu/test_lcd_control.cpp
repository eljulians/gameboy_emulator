#define CATCH_CONFIG_MAIN

#include "../../lib/catch.hpp"

#include "../../src/mmu/mmu.hpp"
#include "../../src/gameboy.hpp"
#include "../../src/gpu/lcd_control.hpp"
#include "../../src/interrupts/interrupt_manager.hpp"

TEST_CASE("update") {
    GameBoy gameBoy = GameBoy();
    InterruptManager interruptManager = InterruptManager(gameBoy.mmu, gameBoy.cpu);
    LCDControl lcd = LCDControl(gameBoy.mmu, interruptManager);
    lcd.setScreenOn();

    SECTION("new scanline") {
        lcd.update(455);
        REQUIRE(lcd.getCurrentScanline() == 0);

        lcd.update(1);
        REQUIRE(lcd.getCurrentScanline() == 1);
    }

}

TEST_CASE("handleModeChange") {
    GameBoy gameBoy = GameBoy();
    InterruptManager interruptManager = InterruptManager(gameBoy.mmu, gameBoy.cpu);
    LCDControl lcd = LCDControl(gameBoy.mmu, interruptManager);
    lcd.setScreenOn();

    for (int i = 0; i < VISIBLE_SCANLINES * CYCLES_TO_DRAW_SCANLINE - 1; i++) {

    }
}

TEST_CASE("setCoincidence") {
    GameBoy gameBoy = GameBoy();
    MMU mmu = gameBoy.mmu;
    InterruptManager interruptManager = InterruptManager(mmu, gameBoy.cpu);
    LCDControl lcd = LCDControl(mmu, interruptManager);
    lcd.setScreenOn();

    SECTION("coincidence") {
        mmu.write_8bit(LCD_STATUS_ADDRESS, 0);
        mmu.write_8bit(LY_COMPARE_ADDRESS, 0);

        lcd.setCoincidence();

        REQUIRE(lcd.getStatus() == 0b100);
   }

   SECTION("no coincidence") {
        mmu.write_8bit(LCD_STATUS_ADDRESS, 0);
        mmu.write_8bit(LY_COMPARE_ADDRESS, 1);

        lcd.setCoincidence();

        REQUIRE(lcd.getStatus() == 0);
   }
}

TEST_CASE("isModeInterruptEnabled") {
    GameBoy gameBoy = GameBoy();
    MMU mmu = gameBoy.mmu;
    InterruptManager interruptManager = InterruptManager(mmu, gameBoy.cpu);
    LCDControl lcd = LCDControl(mmu, interruptManager);
    lcd.setScreenOn();

    SECTION("all disabled") {
        mmu.write_8bit(LCD_STATUS_ADDRESS, 0);

        REQUIRE(!lcd.isModeInterruptEnabled(LCDMode::HBlank));
        REQUIRE(!lcd.isModeInterruptEnabled(LCDMode::VBlank));
        REQUIRE(!lcd.isModeInterruptEnabled(LCDMode::OAMSearch));
    }

    SECTION("OAM") {
        mmu.write_8bit(LCD_STATUS_ADDRESS, 0b00100000);

        REQUIRE(!lcd.isModeInterruptEnabled(LCDMode::HBlank));
        REQUIRE(!lcd.isModeInterruptEnabled(LCDMode::VBlank));
        REQUIRE(lcd.isModeInterruptEnabled(LCDMode::OAMSearch));
    }

    SECTION("VBlank") {
        mmu.write_8bit(LCD_STATUS_ADDRESS, 0b00010000);

        REQUIRE(!lcd.isModeInterruptEnabled(LCDMode::HBlank));
        REQUIRE(lcd.isModeInterruptEnabled(LCDMode::VBlank));
        REQUIRE(!lcd.isModeInterruptEnabled(LCDMode::OAMSearch));
    }

    SECTION("HBlank") {
        mmu.write_8bit(LCD_STATUS_ADDRESS, 0b00001000);

        REQUIRE(lcd.isModeInterruptEnabled(LCDMode::HBlank));
        REQUIRE(!lcd.isModeInterruptEnabled(LCDMode::VBlank));
        REQUIRE(!lcd.isModeInterruptEnabled(LCDMode::OAMSearch));
    }

    SECTION("all enabled") {
        mmu.write_8bit(LCD_STATUS_ADDRESS, 0b00111000);

        REQUIRE(lcd.isModeInterruptEnabled(LCDMode::HBlank));
        REQUIRE(lcd.isModeInterruptEnabled(LCDMode::VBlank));
        REQUIRE(lcd.isModeInterruptEnabled(LCDMode::OAMSearch));
    }

}