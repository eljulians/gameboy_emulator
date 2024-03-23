#define CATCH_CONFIG_MAIN

#include <stdint.h>
#include <vector>
#include "../../lib/catch.hpp"
#include "../../src/gpu/tile.hpp"


TEST_CASE("getValue", "[TilePixel") {
    TilePixel tilePixel(true, false);

    REQUIRE(tilePixel.getValue() == 2);
}

TEST_CASE("createPixels", "[TileRow]") {
    uint8_t firstByte =  0b10110101;
    uint8_t secondByte = 0b01100101;
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

    REQUIRE(tileRow.createPixels() == expected);
}

TEST_CASE("createRows", "[Tile]") {
    std::vector<uint8_t> bytes{
        0b10110101,
        0b11100101,
        0b11100101,
        0b00110101,
        0b10000001,
        0b10100101,
        0b11110101,
        0b11111111,
        0b11110101,
        0b10000101,
        0b01001001,
        0b11011111,
        0b10000101,
        0b10111101,
        0b00111101,
        0b10110101,
    };
    Tile tile = Tile(bytes);

    TileRowVector expected{
        TileRow(0b10110101, 0b11100101),
        TileRow(0b11100101, 0b00110101),
        TileRow(0b10000001, 0b10100101),
        TileRow(0b11110101, 0b11111111),
        TileRow(0b11110101, 0b10000101),
        TileRow(0b01001001, 0b11011111),
        TileRow(0b10000101, 0b10111101),
        TileRow(0b00111101, 0b10110101),
    };

    REQUIRE(tile.createRows() == expected);
}