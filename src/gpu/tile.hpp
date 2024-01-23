#pragma once

#include <stdint.h>
#include <vector>

#define PIXELS_IN_ROW 8

enum class Color {
    WHITE,
    LIGHT_GRAY,
    DARK_GRAY,
    BLACK,
};

class TilePixel {
    // Each pixel 2 bits
    public:
        TilePixel(bool firstBit, bool secondBit) : firstBit(firstBit), secondBit(secondBit) {};
        bool firstBit;
        bool secondBit;
        bool operator==(const TilePixel &other) const {
            return firstBit == other.firstBit && secondBit == other.secondBit;
        }
};

typedef std::vector<TilePixel> TilePixelVector;

class TileRow {
    // 8 pixels; each pixel 2 bits
    public:
        TileRow(uint8_t firstByte, uint8_t secondByte) : firstByte(firstByte), secondByte(secondByte) {};
        TilePixelVector createPixels();

    private:
        uint8_t firstByte;
        uint8_t secondByte;
        TilePixelVector pixels;
};

typedef std::vector<TileRow> TileRowVector;

class Tile {
    // 8x8 pixels; each pixel 2 bits
};

typedef std::vector<Tile> TileVector;
