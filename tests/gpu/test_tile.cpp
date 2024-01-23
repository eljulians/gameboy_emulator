#define CATCH_CONFIG_MAIN

#include <stdint.h>
#include "../../lib/catch.hpp"
#include "../../src/gpu/tile.hpp"


TEST_CASE("createPixels", "[TileRow]") {
    uint8_t firstByte =  0b10110101;  // 0xB5
    uint8_t secondByte = 0b01100101;  // 0x65
    TileRow tileRow = TileRow(firstByte, secondByte);

    TilePixelVector expected{
        TilePixel(1, 0),
        TilePixel(0, 1),
        TilePixel(1, 1),
        TilePixel(1, 0),
        TilePixel(0, 0),
        TilePixel(1, 1),
        TilePixel(0, 0),
        TilePixel(1, 1),
    };

    REQUIRE(expected == tileRow.createPixels());
}