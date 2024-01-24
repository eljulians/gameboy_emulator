#pragma once

#include <stdint.h>
#include <vector>

#define PIXELS_IN_ROW 8
#define ROWS_IN_TILE 8

enum class Color {
    WHITE,
    LIGHT_GRAY,
    DARK_GRAY,
    BLACK,
};

class TilePixel {
    // Each pixel 2 bits
    public:
        bool firstBit;
        bool secondBit;

        TilePixel(bool firstBit, bool secondBit) : firstBit(firstBit), secondBit(secondBit) {};

        bool operator==(const TilePixel &other) const {
            return firstBit == other.firstBit && secondBit == other.secondBit;
        }

        int getValue();
};

typedef std::vector<TilePixel> TilePixelVector;

class TileRow {
    // 8 pixels; each pixel 2 bits
    public:
        uint8_t firstByte;
        uint8_t secondByte;
        TilePixelVector pixels;

        TileRow(uint8_t firstByte, uint8_t secondByte) : firstByte(firstByte), secondByte(secondByte) {
            pixels.reserve(PIXELS_IN_ROW);
        };

        bool operator==(const TileRow &other) const {
            return firstByte == other.firstByte && secondByte == other.secondByte;
        }

        TilePixelVector createPixels();
};

typedef std::vector<TileRow> TileRowVector;

class Tile {
    // 8x8 pixels; each pixel 2 bits; 16 bytes in total
    public:
        std::vector<uint8_t> bytes;
        TileRowVector rows;

        Tile(std::vector<uint8_t> bytes) : bytes(bytes) {
            rows.reserve(ROWS_IN_TILE);
        };
        TileRowVector createRows();
};

typedef std::vector<Tile> TileVector;
