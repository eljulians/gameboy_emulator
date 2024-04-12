#include <stdint.h>
#include <vector>

#include "color.hpp"
#include "tile.hpp"
#include "../mmu/mmu.hpp"

PixelColor BackgroundPalette::getColor(TilePixelV2 pixel) {
    uint8_t pattern = mmu.read_8bit(TILE_WINDOW_PALETTE_ADDRESS);
    int code = (pixel.firstBit << 1) + pixel.secondBit;
    int shift = code * 2;

    return ID_COLOR_MAP.at((pattern >> shift) & 0b11);
}

