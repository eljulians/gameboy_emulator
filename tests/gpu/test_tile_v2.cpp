#define CATCH_CONFIG_MAIN

#include "../../lib/catch.hpp"

#include "../../src/mmu/mmu.hpp"
#include "../../src/gameboy.hpp"
#include "../../src/gpu/tile_v2.hpp"


TEST_CASE("getValue") {
    GameBoy gameBoy = GameBoy();
    MMU mmu = gameBoy.mmu;

    Scroll scroll = {0, 0};

    // LCD Control bit 4->1: unsigned, $8000-$8FFF
    mmu.write_8bit(LCD_CONTROL_ADDRESS, 1<<4);

    SECTION("no scroll") {
        // First tile first row
        mmu.write_8bit(0x8000, 0b10101010);
        mmu.write_8bit(0x8001, 0b01010101);

        // First tile second row
        mmu.write_8bit(0x8002, 0b11110000);
        mmu.write_8bit(0x8003, 0b00110011);

        // Second tile first row
        mmu.write_8bit(0x8010, 0b00110100);
        mmu.write_8bit(0x8011, 0b00001101);

        // First tile
        REQUIRE(TileV2(mmu, 0x8000).getValue(0, 0, scroll) == TilePixelV2{1, 0});
        REQUIRE(TileV2(mmu, 0x8000).getValue(0, 1, scroll) == TilePixelV2{0, 1});
        REQUIRE(TileV2(mmu, 0x8000).getValue(1, 0, scroll) == TilePixelV2{1, 0});
        REQUIRE(TileV2(mmu, 0x8000).getValue(1, 2, scroll) == TilePixelV2{1, 1});
        REQUIRE(TileV2(mmu, 0x8000).getValue(1, 4, scroll) == TilePixelV2{0, 0});

        // Second tile
        REQUIRE(TileV2(mmu, 0x8010).getValue(0, 0, scroll) == TilePixelV2{0, 0});
        REQUIRE(TileV2(mmu, 0x8010).getValue(0, 4, scroll) == TilePixelV2{0, 1});
        REQUIRE(TileV2(mmu, 0x8010).getValue(0, 5, scroll) == TilePixelV2{1, 1});
    }

    SECTION("scroll") {
        REQUIRE(0);
    }
}