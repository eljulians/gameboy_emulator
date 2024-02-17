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
    REQUIRE(backgroundBuffer.getTileAddress(1) == DATA_SELECT_MODE_1 + TILE_SIZE);
    REQUIRE(backgroundBuffer.getTileAddress(2) == DATA_SELECT_MODE_1 + TILE_SIZE*2);

    // LCD Control bit 4->0: signed, $8800-$97FF
    mmu.write_8bit(LCD_CONTROL_ADDRESS, 0);
    REQUIRE(backgroundBuffer.getTileAddress(0x80) == DATA_SELECT_MODE_0);  // i.e. unsigned 128, signed -128 
    REQUIRE(backgroundBuffer.getTileAddress(0x81) == DATA_SELECT_MODE_0 + TILE_SIZE);  // i.e. unsigned 129, signed -127
    REQUIRE(backgroundBuffer.getTileAddress(0x82) == DATA_SELECT_MODE_0 + TILE_SIZE*2);  // i.e. unsigned 130, signed -126
    REQUIRE(backgroundBuffer.getTileAddress(0) == 0x9000);
}