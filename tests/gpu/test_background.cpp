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

        
        REQUIRE(backgroundBuffer.getTileIndexInLayout(0, 0) == 0);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(0, 7) == 0);

        REQUIRE(backgroundBuffer.getTileIndexInLayout(0, 8) == 1);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(0, 15) == 1);

        REQUIRE(backgroundBuffer.getTileIndexInLayout(7, 7) == 0);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(7, 8) == 1);
        

        // Bottom-leftmost (viewport)
        REQUIRE(backgroundBuffer.getTileIndexInLayout(136, 0) == 544);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(143, 7) == 544);


        REQUIRE(backgroundBuffer.getTileIndexInLayout(136, 8) == 545);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(135, 7) == 512); 

        // Bottom-rightmost (viewport)
        REQUIRE(backgroundBuffer.getTileIndexInLayout(136, 152) == 563);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(143, 159) == 563);

        // Bottom-rightmost (full background)
        REQUIRE(backgroundBuffer.getTileIndexInLayout(255, 255) == 1023);
    }

    SECTION("scroll") {
        mmu.write_8bit(SCROLL_X, 7);
        mmu.write_8bit(SCROLL_Y, 7);

        REQUIRE(backgroundBuffer.getTileIndexInLayout(0, 0) == 0);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(0, 1) == 1);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(1, 0) == 32);

        mmu.write_8bit(SCROLL_X, 8);
        mmu.write_8bit(SCROLL_Y, 8);

        REQUIRE(backgroundBuffer.getTileIndexInLayout(0, 0) == 33);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(0, 1) == 33);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(7, 0) == 33);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(8, 0) == 65);

        mmu.write_8bit(SCROLL_X, 8);
        mmu.write_8bit(SCROLL_Y, 7);

        REQUIRE(backgroundBuffer.getTileIndexInLayout(0, 0) == 1);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(1, 0) == 33);

        REQUIRE(backgroundBuffer.getTileIndexInLayout(8, 0) == 33);
        REQUIRE(backgroundBuffer.getTileIndexInLayout(9, 0) == 65);
    }
}