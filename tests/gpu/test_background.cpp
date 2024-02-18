#define CATCH_CONFIG_MAIN

#include "../../lib/catch.hpp"

#include "../../src/mmu/mmu.hpp"
#include "../../src/gameboy.hpp"
#include "../../src/interrupts/interrupt_manager.hpp"
#include "../../src/gpu/lcd_control.hpp"
#include "../../src/gpu/background.hpp"


TEST_CASE("getTileAddress") {
    GameBoy gameBoy = GameBoy();
    MMU mmu = gameBoy.mmu;
    LCDControl lcdControl = LCDControl(mmu, gameBoy.interruptManager);
    BackgroundBuffer backgroundBuffer = BackgroundBuffer(lcdControl, mmu);


    // LCD Control bit 4->1: unsigned, $8000-$8FFF
    mmu.write_8bit(LCD_CONTROL_ADDRESS, 1<<4);
    REQUIRE(backgroundBuffer.getTileAddress(0) == DATA_SELECT_MODE_1);
    REQUIRE(backgroundBuffer.getTileAddress(1) == DATA_SELECT_MODE_1 + TILE_SIZE_BYTES);
    REQUIRE(backgroundBuffer.getTileAddress(2) == DATA_SELECT_MODE_1 + TILE_SIZE_BYTES*2);

    // LCD Control bit 4->0: signed, $8800-$97FF
    mmu.write_8bit(LCD_CONTROL_ADDRESS, 0);
    REQUIRE(backgroundBuffer.getTileAddress(0x80) == DATA_SELECT_MODE_0);  // i.e. unsigned 128, signed -128 
    REQUIRE(backgroundBuffer.getTileAddress(0x81) == DATA_SELECT_MODE_0 + TILE_SIZE_BYTES);  // i.e. unsigned 129, signed -127
    REQUIRE(backgroundBuffer.getTileAddress(0x82) == DATA_SELECT_MODE_0 + TILE_SIZE_BYTES*2);  // i.e. unsigned 130, signed -126
    REQUIRE(backgroundBuffer.getTileAddress(0) == 0x9000);
}

TEST_CASE("getTileId") {
    GameBoy gameBoy = GameBoy();
    MMU mmu = gameBoy.mmu;
    LCDControl lcdControl = LCDControl(mmu, gameBoy.interruptManager);
    BackgroundBuffer backgroundBuffer = BackgroundBuffer(lcdControl, mmu);

    SECTION("no scroll") {
        mmu.write_8bit(SCROLL_X, 0);
        mmu.write_8bit(SCROLL_Y, 0);

        REQUIRE(backgroundBuffer.getTileId(0, 0) == 0);
        REQUIRE(backgroundBuffer.getTileId(0, 7) == 0);

        REQUIRE(backgroundBuffer.getTileId(0, 8) == 1);
        REQUIRE(backgroundBuffer.getTileId(0, 15) == 1);

        REQUIRE(backgroundBuffer.getTileId(7, 7) == 0);
        REQUIRE(backgroundBuffer.getTileId(7, 8) == 1);

        // Bottom-leftmost
        REQUIRE(backgroundBuffer.getTileId(136, 0) == 340);
        REQUIRE(backgroundBuffer.getTileId(143, 7) == 340);

        REQUIRE(backgroundBuffer.getTileId(136, 8) == 341);
        REQUIRE(backgroundBuffer.getTileId(135, 7) == 320);

        // Bottom-rightmost
        REQUIRE(backgroundBuffer.getTileId(136, 152) == 359);
        REQUIRE(backgroundBuffer.getTileId(143, 159) == 359);
    }

    SECTION("scroll") {
        mmu.write_8bit(SCROLL_X, 7);
        mmu.write_8bit(SCROLL_Y, 7);

        REQUIRE(backgroundBuffer.getTileId(0, 0) == 0);
        REQUIRE(backgroundBuffer.getTileId(0, 1) == 1);
        REQUIRE(backgroundBuffer.getTileId(1, 0) == 20);

        mmu.write_8bit(SCROLL_X, 8);
        mmu.write_8bit(SCROLL_Y, 8);

        REQUIRE(backgroundBuffer.getTileId(0, 0) == 21);
        REQUIRE(backgroundBuffer.getTileId(0, 1) == 21);
        REQUIRE(backgroundBuffer.getTileId(7, 0) == 21);
        REQUIRE(backgroundBuffer.getTileId(8, 0) == 41);

        mmu.write_8bit(SCROLL_X, 8);
        mmu.write_8bit(SCROLL_Y, 7);

        REQUIRE(backgroundBuffer.getTileId(0, 0) == 1);
        REQUIRE(backgroundBuffer.getTileId(1, 0) == 21);
    }
}