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

    // First tile first row
    mmu.write_8bit(0x8000, 0b10101010);
    mmu.write_8bit(0x8001, 0b01010101);

    // First tile second row
    mmu.write_8bit(0x8002, 0b11110000);
    mmu.write_8bit(0x8003, 0b00110011);

    // Second tile first row
    mmu.write_8bit(0x8010, 0b00110100);
    mmu.write_8bit(0x8011, 0b00001101);

    // First tile (second row of tiles; first line is scanline 8) first row
    // 256 pixels per line, 8 pixels per tile, 16 bytes per tile
    mmu.write_8bit(0x8200, 0b11011111);
    mmu.write_8bit(0x8201, 0b01001110);

    SECTION("no scroll") {
        // First tile first row
        REQUIRE(TileV2(mmu, 0x8000).getValue(0, 0, scroll) == TilePixelV2{1, 0});
        REQUIRE(TileV2(mmu, 0x8000).getValue(0, 1, scroll) == TilePixelV2{0, 1});

        // First tile second row
        REQUIRE(TileV2(mmu, 0x8000).getValue(1, 0, scroll) == TilePixelV2{1, 0});
        REQUIRE(TileV2(mmu, 0x8000).getValue(1, 2, scroll) == TilePixelV2{1, 1});
        REQUIRE(TileV2(mmu, 0x8000).getValue(1, 4, scroll) == TilePixelV2{0, 0});

        // Second tile first row
        REQUIRE(TileV2(mmu, 0x8010).getValue(0, 8, scroll) == TilePixelV2{0, 0});
        REQUIRE(TileV2(mmu, 0x8010).getValue(0, 12, scroll) == TilePixelV2{0, 1});
        REQUIRE(TileV2(mmu, 0x8010).getValue(0, 13, scroll) == TilePixelV2{1, 1});

        // First tile (second row of tiles; first line is scanline 8) first row
        REQUIRE(TileV2(mmu, 0x8200).getValue(8, 0, scroll) == TilePixelV2{1, 0});
        REQUIRE(TileV2(mmu, 0x8200).getValue(8, 1, scroll) == TilePixelV2{1, 1});
        REQUIRE(TileV2(mmu, 0x8200).getValue(8, 2, scroll) == TilePixelV2{0, 0});
    }

    SECTION("scroll") {
        REQUIRE(TileV2(mmu, 0x8000).getValue(0, 0, {1, 0}) == TilePixelV2{0, 1});
        REQUIRE(TileV2(mmu, 0x8000).getValue(0, 0, {6, 0}) == TilePixelV2{1, 0});
        REQUIRE(TileV2(mmu, 0x8000).getValue(0, 0, {7, 0}) == TilePixelV2{0, 1});

        // Actual tile address is already inferred by the background based on the scroll
        REQUIRE(TileV2(mmu, 0x8010).getValue(0, 0, {8, 0}) == TilePixelV2{0, 0});
        REQUIRE(TileV2(mmu, 0x8010).getValue(0, 0, {9, 0}) == TilePixelV2{0, 0});
        REQUIRE(TileV2(mmu, 0x8010).getValue(0, 0, {10, 0}) == TilePixelV2{1, 0});

        REQUIRE(TileV2(mmu, 0x8000).getValue(0, 0, {0, 1}) == TilePixelV2{1, 0});
        REQUIRE(TileV2(mmu, 0x8000).getValue(0, 0, {1, 1}) == TilePixelV2{1, 0});
        REQUIRE(TileV2(mmu, 0x8000).getValue(0, 0, {2, 1}) == TilePixelV2{1, 1});

        // First tile (second row of tiles; first line is scanline 8)
        REQUIRE(TileV2(mmu, 0x8200).getValue(8, 0, {1, 0}) == TilePixelV2{1, 1});
        REQUIRE(TileV2(mmu, 0x8200).getValue(8, 0, {2, 0}) == TilePixelV2{0, 0});
        REQUIRE(TileV2(mmu, 0x8200).getValue(8, 0, {3, 0}) == TilePixelV2{1, 0});
    }
}