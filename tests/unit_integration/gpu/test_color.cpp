#define CATCH_CONFIG_MAIN

#include "../../lib/catch.hpp"

#include "../../src/mmu/mmu.hpp"
#include "../../src/gameboy.hpp"
#include "../../src/gpu/color.hpp"
#include "../../src/gpu/tile_v2.hpp"


TEST_CASE("getColor", "[BackgroundPalette]") {
    GameBoy gameBoy = GameBoy();
    MMU mmu = gameBoy.mmu;
    BackgroundPalette palette = BackgroundPalette(mmu);

    SECTION("black, white, dark gray, light gray") {
        mmu.write_8bit(TILE_WINDOW_PALETTE_ADDRESS, 0b11001001);

        REQUIRE(palette.getColor(TilePixelV2(0, 0)) == LIGHT_GRAY);
        REQUIRE(palette.getColor(TilePixelV2(0, 1)) == DARK_GRAY);
        REQUIRE(palette.getColor(TilePixelV2(1, 0)) == WHITE);
        REQUIRE(palette.getColor(TilePixelV2(1, 1)) == BLACK);
    }

    SECTION("light gray, white, black, dark gray") {
        mmu.write_8bit(TILE_WINDOW_PALETTE_ADDRESS, 0b01001110);

        REQUIRE(palette.getColor(TilePixelV2(0, 0)) == DARK_GRAY);
        REQUIRE(palette.getColor(TilePixelV2(0, 1)) == BLACK);
        REQUIRE(palette.getColor(TilePixelV2(1, 0)) == WHITE);
        REQUIRE(palette.getColor(TilePixelV2(1, 1)) == LIGHT_GRAY);
    }
}